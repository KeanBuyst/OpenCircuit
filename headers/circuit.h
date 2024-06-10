#pragma once

#include <components.h>

#define WIRE 5

typedef unsigned char byte;

typedef struct Node {
    bool isWire;
    Component component;
    Vector2 position;
    // connected nodes
    struct Node* parent;
    struct Node* children[5];
    byte nodes;
} Node;

Vector2 GetStartPoint(Node* node);
Vector2 GetEndPoint(Node* node);
void DrawWires(State* state,Node* node);
