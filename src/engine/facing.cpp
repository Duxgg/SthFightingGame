#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "./core/player.h"
#include <iostream>

class F2F
{
public:
    static bool Facing(const std::vector<Entity *> &entities)
    {
        for (size_t i = 0; i < entities.size(); i++)
        {
            Player *p1 = static_cast<Player *>(entities[i]->data); // Ensure we access the Player instance
            if (!p1)
                continue;

            for (size_t j = i + 1; j < entities.size(); j++)
            {
                Player *p2 = static_cast<Player *>(entities[j]->data);
                if (!p2)
                    continue;

                if (p1->isPlayer2 == false && p1->dstRect.x > p2->dstRect.x)
                {
                    p1->position.x += p1->portion.w;
                    p1->isPlayer2 = true;
                    p2->position.x -= p2->portion.w;
                    p2->isPlayer2 = false;
                    return true;
                }
                else if (p1->isPlayer2 == true && p1->dstRect.x < p2->dstRect.x)
                {
                    p2->position.x += p2->portion.w;
                    p2->isPlayer2 = true;
                    p1->position.x -= p1->portion.w;
                    p1->isPlayer2 = false;
                }
            }
        }
        return false;
    }
};