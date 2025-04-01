#ifndef AXL_LOW_H
#define AXL_LOW_H

#include "./core/player.h"

class AxlLow : public Player
{
public:
    AxlLow(SDL_Renderer *renderer, bool player2);
    Entity init(SDL_Renderer *renderer, bool isPlayer2);
};

#endif