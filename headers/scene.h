#pragma once

#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>

#define MENU_WIDTH 300

typedef struct UI
{
    bool primaryDrop;
    int shift;
} UI;

typedef struct State
{
    bool dragging;
    Vector2 lastMousePos;
    // shifting
    Vector2 offset;
    int menu_offset;
    // UI
    UI ui;
} State;


void SceneInput(State* state);
void DrawMenu(State* state);