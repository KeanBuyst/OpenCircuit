#pragma once

#include <cache.h>
#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>

#define MENU_WIDTH 200

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
    Vector2 aspect;
    // UI
    UI ui;

    Cache cache;
    void* dragged;
} State;

void NodesHandler(State* state);
void SceneInput(State* state);
void DrawMenu(State* state);