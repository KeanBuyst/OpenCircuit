#pragma once

#include <components.h>

typedef unsigned char byte;

typedef struct Node {
    Component* component;
    Vector2 position;
    // connected nodes
    struct Node* parent;
    struct Node* children[3];
    byte nodes;
} Node;

void DrawNodes(Node root);
