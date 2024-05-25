#include <stdio.h>
#include <raylib.h>

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
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "OpenCircuit");

    Camera2D camera = {0};
    Vector2 origin = {0,0};
    camera.target = origin;
    camera.offset = origin;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    RenderTexture2D menu = LoadRenderTexture(300,HEIGHT);
    Rectangle source = {0,0,menu.texture.width,menu.texture.height};

    while (!WindowShouldClose())
    {
        int offset = GetRenderWidth() - 300;
        Rectangle dest = {offset,0,300,GetRenderHeight()};
        // draw menu
        BeginTextureMode
        (menu);
            ClearBackground(RAYWHITE);
            DrawLine(1,0,1,HEIGHT,BLACK);
        EndTextureMode();
        // draw grid
        BeginDrawing();
            ClearBackground(WHITE);
            grid(GetRenderWidth(),GetRenderHeight(),(int) (camera.offset.x) % GRID_SPACING,(int) (camera.offset.y) % GRID_SPACING);
            BeginMode2D(camera);
                // draw components here
            EndMode2D();
            DrawTexturePro(menu.texture,source,dest,origin,0,WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(menu);

    CloseWindow();

    return 0;
}