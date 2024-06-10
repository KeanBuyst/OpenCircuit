#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <circuit.h>
#include <stdio.h>

void NodesHandler(State* state){
    for (int i = 0; i < state->cache.size; i++){
        Node* node = CacheGet(&state->cache,i);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (CheckCollisionPointRec(GetMousePosition(),RelativeShape(state,node->component,node->position))){
                if (IsKeyDown(KEY_LEFT_SHIFT) && state->selected != NULL && node != state->selected){
                    Node* prev = state->selected;
                    if (prev->nodes == 5) {
                        state->ui.ui_error = TOO_MANY_CONNECTIONS;
                    } else {
                        for (int j = 0; j < prev->nodes; j++)
                            if (prev->children[j] == node) return;
                        prev->children[prev->nodes] = node;
                        prev->nodes++;
                    }
                } else {
                    if (node->component.selected) {
                        state->dragging = true;
                        state->dragged = node;
                    }
                    state->selected = node;
                    node->component.selected = true;
                }
            } else node->component.selected = false;
        }
        // draw wires to connect nodes
        DrawWires(state,node);
        DrawComponent(state,node->component,node->position);
    }
}

void SceneInput(State* state){
    if (IsKeyPressed(KEY_R))
    {
        bool* flip = &((Node*) state->dragged)->component.flipped;
        *flip = !*flip;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        state->lastMousePos = Vector2Add(GetMousePosition(),state->offset);
        state->dragging = true;
        return;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        state->dragging = false;
        if (state->dragged == NULL) return;
        Node* node = state->dragged;
        node->position = (Vector2) {
            (int) (node->position.x / GRID_SPACING) * GRID_SPACING + GRID_SPACING,
            (int) (node->position.y / GRID_SPACING) * GRID_SPACING + GRID_SPACING
        };
        state->dragged = NULL;
        return;
    }
    if (state->dragging)
    {
        Vector2 pos = GetMousePosition();
        if (state->dragged == NULL){
            if (Vector2Distance(state->lastMousePos,pos) > 1)
            {
                state->offset = Vector2Subtract(state->lastMousePos,pos);
            }
        }
        else {
            ((Node*) state->dragged)->position = Vector2Add(pos,state->offset);
        }
    }
}

void GuiCell(State* state,Component component){
    Rectangle rect = {0,state->ui.shift,MENU_WIDTH,50};
    DrawRectangleRec(rect,(Color) {220,220,255,255});
    DrawRectangleLinesEx(rect,1,GRAY);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(),rect)){
        Node node = {false,component,{state->menu_offset,state->ui.shift + 25},NULL,NULL,0};
        CacheAdd(&state->cache,&node);
        state->dragged = CacheGet(&state->cache,state->cache.size-1);
    }
    DrawComponentIcon(component,(Vector2) {MENU_WIDTH/2,state->ui.shift + 25});
    state->ui.shift += 50;
}

void DrawMenu(State* state){
    SetMouseScale(1/state->aspect.x,1/state->aspect.y);
    SetMouseOffset(state->menu_offset,0);
    GuiSetStyle(DEFAULT,BASE_COLOR_NORMAL,0xCCCCCCFF);
    if (GuiButton((Rectangle) {0,0,MENU_WIDTH,30},"Primary Components")){
        state->ui.primaryDrop = !state->ui.primaryDrop;
        state->ui.shift = 30;
    }
    if (state->ui.primaryDrop){
        Component resistor = CreateResistor(0);
        GuiCell(state,resistor);
        state->ui.shift = 30;
    }
    SetMouseScale(1,1);
    SetMouseOffset(0,0);
}

void DrawErrors(State* state){
    switch (state->ui.ui_error){
        case TOO_MANY_CONNECTIONS:
            GuiMessageBox((Rectangle) {0,0,400,300},"Error","Max connections for node reached","");
    }
}