#include "components.h"

#define DEFINE_MODEL(name, ...) \
    Vector2 name[] = { __VA_ARGS__ }; \
    const uint name##_SIZE = sizeof(name) / sizeof(name[0])

// Define the model
DEFINE_MODEL(M_RESISTOR,
    (Vector2){-60, 0},
    (Vector2){-35, 0},
    (Vector2){-30, -20},
    (Vector2){-20, 20},
    (Vector2){-10, -20},
    (Vector2){0, 20},
    (Vector2){10, -20},
    (Vector2){20, 20},
    (Vector2){30, -20},
    (Vector2){35, 0},
    (Vector2){60, 0}
);

void DrawComponent(Component component,Vector2 position){
    for (int i = 0; i < component.vertices_count - 1; i++){
        Vector2 p1 = component.vertices[i];
        Vector2 p2 = component.vertices[i+1];
        if (component.flipped)
        {
            // flip x and y
            p1 = (Vector2) {p1.y,p1.x};
            p2 = (Vector2) {p2.y,p2.x};
        }
        DrawLineEx(Vector2Add(p1,position),Vector2Add(p2,position),5,component.color);
    }
}