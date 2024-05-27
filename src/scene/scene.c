#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "scene.h"
#include <stdio.h>

void SceneInput(State* state){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        state->lastMousePos = Vector2Add(GetMousePosition(),state->offset);
        state->dragging = true;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        state->dragging = false;
    }
    if (state->dragging)
    {
        Vector2 pos = GetMousePosition();
        if (Vector2Distance(state->lastMousePos,pos) > 1)
        {
            state->offset = Vector2Subtract(state->lastMousePos,pos);
        }
    }
}

void DrawMenu(State* state){
    SetMouseOffset(state->menu_offset,0);
    if (GuiButton((Rectangle) {0,0,300,60},"Button")){
        printf("Pressed!\n");
    }
}