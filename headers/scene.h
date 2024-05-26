#pragma once

#include <circuit.h>

typedef struct State
{
    bool dragging;
    Vector2 lastMousePos;
    Camera2D camera;
} State;

void SceneInput(State* state);