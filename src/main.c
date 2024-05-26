#include <stdio.h>
#include <scene.h>

#define WIDTH 1280
#define HEIGHT 720

#define GRID_SPACING 40

void grid(int width,int height,int shiftX,int shiftY){
    for (int x = GRID_SPACING - shiftX; x < width; x += GRID_SPACING)
        DrawLine(x,0,x,height,LIGHTGRAY);
    for (int y = GRID_SPACING - shiftY; y < height; y += GRID_SPACING)
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

    Camera2D camera;
    Vector2 origin = {0,0};
    camera.target = origin;
    camera.offset = origin;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    State state;
    state.camera = camera;
    state.dragging = false;

    RenderTexture2D menu = LoadRenderTexture(300,HEIGHT);
    Rectangle source = {0,0,menu.texture.width,menu.texture.height};

    while (!WindowShouldClose())
    {
        int offset = GetRenderWidth() - 300;
        Rectangle dest = {offset,0,300,GetRenderHeight()};
        // do input
        SceneInput(&state);
        // draw menu
        BeginTextureMode(menu);
            ClearBackground(RAYWHITE);
            DrawLine(1,0,1,HEIGHT,BLACK);
        EndTextureMode();
        // draw grid
        BeginDrawing();
            ClearBackground(WHITE);
            grid(GetRenderWidth(),GetRenderHeight(),(int) (state.camera.offset.x) % GRID_SPACING,(int) (state.camera.offset.y) % GRID_SPACING);
            BeginMode2D(state.camera);
                DrawNodes(node);
                // draw components here
            EndMode2D();
            DrawTexturePro(menu.texture,source,dest,origin,0,WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(menu);

    CloseWindow();

    return 0;
}