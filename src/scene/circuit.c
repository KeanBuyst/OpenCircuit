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


void DrawWires(State* state,Node* node){
    Vector2 pos = Vector2Subtract(GetEndPoint(node),state->offset);
    for (int j = 0; j < node->nodes; j++){
        Node* next = node->children[j];
        Vector2 pos1;
        Vector2 pos2;
        if (node->position.x < next->position.x){
            pos1 = Vector2Subtract(GetEndPoint(node),state->offset);
            if (!next->component.flipped) pos2 = Vector2Subtract(GetStartPoint(next),state->offset);
        } else {
            pos1 = Vector2Subtract(GetStartPoint(node),state->offset);
            if (!next->component.flipped) pos2 = Vector2Subtract(GetEndPoint(next),state->offset);
        }
        if (next->component.flipped)
        {
            if (node->position.y > next->position.y){
                pos2 = Vector2Subtract(GetEndPoint(next),state->offset);
            } else {
                pos2 = Vector2Subtract(GetStartPoint(next),state->offset);
            }
        }
        DrawLineEx(pos1,pos2,5,BLACK);
    }
}