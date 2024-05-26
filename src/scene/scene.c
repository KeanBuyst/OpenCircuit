#include "scene.h"
#include <stdio.h>

void SceneInput(State* state){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        state->lastMousePos = GetMousePosition();
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
            Vector2 shift = Vector2Subtract(state->lastMousePos,pos);
            state->camera.offset = Vector2Add(state->lastMousePos,shift);
        }
    }
}