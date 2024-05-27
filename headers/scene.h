#pragma once

#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>

typedef struct State
{
    bool dragging;
    Vector2 lastMousePos;
    // shifting
    Vector2 offset;
    int menu_offset;
} State;

void SceneInput(State* state);
void DrawMenu(State* state);