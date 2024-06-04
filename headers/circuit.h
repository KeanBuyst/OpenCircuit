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
    struct Node* children[3];
    byte nodes;
} Node;

void DrawNodes(State* state,Node root);
