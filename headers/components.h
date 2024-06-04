#ifndef MODELS_H
#define MODELS_H

#include <scene.h>

typedef unsigned int uint;

#define DECLARE_MODEL(name) \
    extern Vector2 name[]; \
    extern const uint name##_SIZE

// Declare the model
DECLARE_MODEL(M_RESISTOR);

typedef struct Component {
    // drawing data
    Vector2* vertices;
    uint vertices_count;
    bool flipped;
    bool selected;
    Color color;
    Rectangle shape;
    // constant
    uint resistance;
    // needs to be calculated
    uint voltage;
    uint current;
} Component;

//#define RESISTOR {.vertices = M_RESISTOR,.vertices_count = M_RESISTOR_SIZE,.flipped = false,.selected = false,.color = BLACK,.shape = GetShape(M_RESISTOR,M_RESISTOR_SIZE),.resistance = 0,.voltage = 0,.current = 0}

Component CreateResistor(uint resistance);
void DrawComponent(State* state,Component component,Vector2 position);
void DrawComponentIcon(Component component,Vector2 position);
Rectangle GetShape(Vector2* points,uint count);

#endif