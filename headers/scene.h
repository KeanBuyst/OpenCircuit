#pragma once

#include <cache.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>

#define GRID_SPACING 40

#define MENU_WIDTH 200

typedef enum UI_ERROR {
    NONE,
    TOO_MANY_CONNECTIONS
} UI_ERROR;

typedef struct UI
{
    bool primaryDrop;
    UI_ERROR ui_error;
    int shift;
} UI;

typedef struct State
{
    bool dragging;
    Vector2 lastMousePos;
    // shifting
    Vector2 offset;
    int menu_offset;
    Vector2 aspect;
    // UI
    UI ui;

    Cache cache;
    void* dragged;
    void* selected;
} State;

void NodesHandler(State* state);
void SceneInput(State* state);
void DrawMenu(State* state);
void DrawErrors(State* state);