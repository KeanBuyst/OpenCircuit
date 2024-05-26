#ifndef MODELS_H
#define MODELS_H

#include <stdbool.h>
#include <raylib.h>
#include <raymath.h>

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
    Color color;
    // constant
    uint resistance;
    // needs to be calculated
    uint voltage;
    uint current;
} Component;

void DrawComponent(Component component,Vector2 position);

#endif