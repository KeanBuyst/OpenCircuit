#include "circuit.h"

#include <stdio.h>

Vector2 GetEndPoint(Node* node)
{
    if (node->component == NULL) return node->position;
    Vector2 vertex = node->component->vertices[node->component->vertices_count-1];
    if (node->component->flipped)
        vertex = (Vector2) {vertex.y,vertex.x};
    return Vector2Add(vertex,node->position);
}
Vector2 GetStartPoint(Node* node)
{
    if (node->component == NULL) return node->position;
    Vector2 vertex = node->component->vertices[0];
    if (node->component->flipped)
        vertex = (Vector2) {vertex.y,vertex.x};
    return Vector2Add(vertex,node->position);
}

void draw(Node* node){
    if (node->component == NULL){
        if (node->parent != NULL){
            DrawLineEx(GetEndPoint(node->parent),node->position,5,BLACK);
        }
    }
    else 
    {
        if (node->parent != NULL){
            DrawLineEx(GetEndPoint(node->parent),GetStartPoint(node),5,BLACK);
        }
        DrawComponent(*node->component,node->position);
    }
}

void doNode(Node* node){
    draw(node);
    for (int i = 0; i < node->nodes; i++){
        doNode(node->children[i]);
    }
}

void DrawNodes(Node root)
{
    doNode(&root);
}