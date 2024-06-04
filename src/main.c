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
    
    Component component = CreateResistor(1);

    Node node;
    node.component = component;
    node.nodes = 0;
    node.parent = NULL;
    node.position = (Vector2) {200,200};

    State state;
    state.dragging = false;
    state.offset = (Vector2) {0,0};
    state.ui = (UI) {0};
    state.cache = CacheInit(5,sizeof(Node));
    state.dragged = NULL;

    CacheAdd(&state.cache,&node);

    RenderTexture2D menu = LoadRenderTexture(MENU_WIDTH,HEIGHT);
    Rectangle source = {0,0,MENU_WIDTH,-menu.texture.height};

    while (!WindowShouldClose())
    {
        state.aspect.x = (float) GetRenderWidth() / WIDTH;
        state.aspect.y = (float) GetRenderHeight() / HEIGHT;
        state.menu_offset = -(GetRenderWidth() - MENU_WIDTH * state.aspect.x);
        Rectangle dest = {0,0,MENU_WIDTH * state.aspect.x,GetRenderHeight()};
        // do input
        SceneInput(&state);
        // draw menu
        BeginTextureMode(menu);
            ClearBackground(RAYWHITE);
            DrawLine(1,0,1,HEIGHT,BLACK);
            DrawMenu(&state);
        EndTextureMode();
        // draw grid
        BeginDrawing();
            ClearBackground(WHITE);
            grid(GetRenderWidth(),GetRenderHeight(),(int) (state.offset.x) % GRID_SPACING,(int) (state.offset.y) % GRID_SPACING);
            DrawTexturePro(menu.texture,source,dest,(Vector2) {state.menu_offset,0},0,WHITE);
            NodesHandler(&state); // drawing components
        EndDrawing();
    }

    UnloadRenderTexture(menu);
    CacheFree(&state.cache);

    CloseWindow();

    return 0;
}