#include <stdio.h>
#include <circuit.h>

#define WIDTH 1280
#define HEIGHT 720

#define GRID_SPACING 40

void grid(int width,int height,int shiftX,int shiftY){
    for (int x = -shiftX; x < width; x += GRID_SPACING)
        DrawLine(x,0,x,height,LIGHTGRAY);
    for (int y = -shiftY; y < height; y += GRID_SPACING)
        DrawLine(0,y,width,y,LIGHTGRAY);
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "OpenCircuit");
    

    Component component;
    component.color = BLACK;
    component.current = 0;
    component.resistance = 2;
    component.voltage = 0;
    component.flipped = false;
    component.vertices = M_RESISTOR;
    component.vertices_count = M_RESISTOR_SIZE;

    Node node;
    node.component = &component;
    node.nodes = 0;
    node.parent = NULL;
    node.position = (Vector2) {200,200};

    State state;
    state.dragging = false;
    state.offset = (Vector2) {0,0};

    RenderTexture2D menu = LoadRenderTexture(300,HEIGHT);
    Rectangle source = {0,0,menu.texture.width,-menu.texture.height};

    while (!WindowShouldClose())
    {
        state.menu_offset = -(GetRenderWidth() - 300);
        Rectangle dest = {0,0,300,GetRenderHeight()};
        // do input
        SceneInput(&state);
        // draw menu
        BeginTextureMode(menu);
            ClearBackground(RAYWHITE);
            DrawLine(1,0,1,HEIGHT,BLACK);
            DrawText("Testing",100,200,16,RED);
            DrawMenu(&state);
        EndTextureMode();
        // draw grid
        BeginDrawing();
            ClearBackground(WHITE);
            grid(GetRenderWidth(),GetRenderHeight(),(int) (state.offset.x) % GRID_SPACING,(int) (state.offset.y) % GRID_SPACING);
            DrawNodes(&state,node); // drawing components
            DrawTexturePro(menu.texture,source,dest,(Vector2) {state.menu_offset,0},0,WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(menu);

    CloseWindow();

    return 0;
}