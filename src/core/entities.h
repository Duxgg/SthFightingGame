#pragma once
#include <SDL3/SDL.h>

#define MAX_ENTITY 100

typedef struct
{
    void (*quit)(void);
    void (*handleInput)(SDL_Event *);
    void (*update)(float, float, float, void *);
    void (*render)(SDL_Renderer *, void *);
    void *data;
} Entity;
