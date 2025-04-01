#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "./core/player.h"
#include <iostream>

class CollisionChecker
{
public:
    static bool checkCollision(const std::vector<Entity *> &entities)
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

                if (SDL_HasRectIntersectionFloat(&p1->hitbox, &p2->dstRect))
                {

                    p2->hit = true;
                    return true;
                }
                else if (SDL_HasRectIntersectionFloat(&p2->hitbox, &p1->dstRect))
                {

                    p1->hit = true;
                    return true;
                }
            }
        }
        return false;
    }
};