#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "components.h"
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

void GuiCell(State* state,Component component){
    DrawRectangle(1,state->ui.shift,MENU_WIDTH,50,(Color) {220,220,255,255});
    DrawRectangleLines(1,state->ui.shift,MENU_WIDTH,50,GRAY);
    DrawComponentIcon(component,(Vector2) {MENU_WIDTH/2,state->ui.shift + 25});
    state->ui.shift += 50;
}

void DrawMenu(State* state){
    SetMouseOffset(state->menu_offset,0);
    if (GuiButton((Rectangle) {0,0,MENU_WIDTH,30},"Primary Components")){
        state->ui.primaryDrop = !state->ui.primaryDrop;
        state->ui.shift = 30;
    }
    if (state->ui.primaryDrop){
        Component resistor = RESISTOR;
        GuiCell(state,resistor);
        state->ui.shift = 30;
    }
}