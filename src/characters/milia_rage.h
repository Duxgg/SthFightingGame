#ifndef MILIA_RAGE_H
#define MILIA_RAGE_H

#include "./core/player.h"

class MiliaRage : public Player
{
public:
    MiliaRage(SDL_Renderer *renderer, bool player2);
    Entity init(SDL_Renderer *renderer, bool isPlayer2);
};

#endif