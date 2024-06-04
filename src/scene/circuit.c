#include "circuit.h"

#include <stdio.h>

Vector2 GetEndPoint(Node* node)
{
    if (node->isWire) return node->position;
    Vector2 vertex = node->component.vertices[node->component.vertices_count-1];
    if (node->component.flipped)
        vertex = (Vector2) {vertex.y,vertex.x};
    return Vector2Add(vertex,node->position);
}
Vector2 GetStartPoint(Node* node)
{
    if (node->isWire) return node->position;
    Vector2 vertex = node->component.vertices[0];
    if (node->component.flipped)
        vertex = (Vector2) {vertex.y,vertex.x};
    return Vector2Add(vertex,node->position);
}

void draw(State* state,Node* node){
    if (node->isWire){
        if (node->parent != NULL){
            Vector2 p1 = Vector2Add(GetEndPoint(node->parent),state->offset);
            Vector2 p2 = Vector2Add(node->position,state->offset);
            DrawLineEx(p1,p2,WIRE,BLACK);
        }
    }
    else 
    {
        if (node->parent != NULL){
            Vector2 p1 = Vector2Add(GetEndPoint(node->parent),state->offset);
            Vector2 p2 = Vector2Add(GetStartPoint(node),state->offset);
            DrawLineEx(p1,p2,WIRE,BLACK);
        }
        DrawComponent(state,node->component,node->position);
    }
}

void doNode(State* state,Node* node){
    draw(state,node);
    for (int i = 0; i < node->nodes; i++){
        doNode(state,node->children[i]);
    }
}

void DrawNodes(State* state,Node root)
{
    doNode(state,&root);
}