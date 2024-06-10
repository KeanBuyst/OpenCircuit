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

Rectangle GetShape(Vector2* points,uint count){
    int minX = 0, maxX = 0;
    int minY = 0, maxY = 0;
    for (int i = 0; i < count; i++){
        Vector2 vec = points[i];
        if (vec.x > maxX) maxX = vec.x;
        if (vec.y > maxY) maxY = vec.y;
        if (vec.x < minX) minX = vec.x;
        if (vec.y < minY) minY = vec.y;
    }
    return (Rectangle) {minX,minY,maxX,maxY};
}

Component CreateResistor(uint resistance){
    return (Component) {
        M_RESISTOR,
        M_RESISTOR_SIZE,
        false,
        true,
        BLACK,
        GetShape(M_RESISTOR,M_RESISTOR_SIZE),
        resistance,0,0
    };
}

Rectangle RelativeShape(State* state,Component component,Vector2 position){
    Vector2 p1;
    Vector2 p2;
    if (component.flipped){
        p1.y = component.shape.x + position.y;
        p1.x = component.shape.y + position.x;
        p2.x = component.shape.height - component.shape.y;
        p2.y = component.shape.width - component.shape.x; 
    } else {
        p1.x = component.shape.x + position.x;
        p1.y = component.shape.y + position.y;
        p2.y = component.shape.height - component.shape.y;
        p2.x = component.shape.width - component.shape.x; 
    }
    p1 = Vector2Subtract(p1,state->offset);
    return (Rectangle) {p1.x,p1.y,p2.x,p2.y};
}

void DrawComponent(State* state,Component component,Vector2 position){
    if (component.selected){
        Rectangle rect = RelativeShape(state,component,position);
        DrawRectangleRec(rect,(Color) {230,230,255,100});
        DrawRectangleLinesEx(rect,1,BLUE);
    }
    for (int i = 0; i < component.vertices_count - 1; i++){
        
        Vector2 p1 = component.vertices[i];
        Vector2 p2 = component.vertices[i+1];
        if (component.flipped)
        {
            // flip x and y
            p1 = (Vector2) {p1.y,p1.x};
            p2 = (Vector2) {p2.y,p2.x};
        }
        DrawLineEx(
            Vector2Subtract(Vector2Add(p1,position),state->offset),
            Vector2Subtract(Vector2Add(p2,position),state->offset),
            5,component.color
        );
    }
}

void DrawComponentIcon(Component component,Vector2 position){
    Vector2 scale = {2,2};
    for (int i = 0; i < component.vertices_count - 1; i++){
        Vector2 p1 = Vector2Divide(component.vertices[i],scale);
        Vector2 p2 = Vector2Divide(component.vertices[i+1],scale);
        DrawLineEx(
            Vector2Add(p1,position),
            Vector2Add(p2,position),
            2,component.color
        );
    }
}