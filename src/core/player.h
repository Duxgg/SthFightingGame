#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <./core/entities.h>
#include <vector>

class Player
{
public:
    SDL_FRect portion = {0, 24, 84, 92};
    SDL_FRect position = {300, 250, 84, 92};
    SDL_FRect dstRect = position;
    SDL_Texture *texture;
    std::vector<SDL_FRect> walkFrames;
    std::vector<SDL_FRect> jumpFrames;
    std::vector<SDL_FRect> jumpAFrames;
    std::vector<SDL_FRect> runFrames;
    std::vector<SDL_FRect> attackFrames;
    std::vector<SDL_FRect> attackBFrames;
    std::vector<SDL_FRect> attackABFrames;
    std::vector<SDL_FRect> attackFAFrames;
    SDL_FRect hitbox;
    SDL_FRect stan = {0, 24, 84, 92};
    SDL_FRect hitFrames = {547, 2049, 75, 92};
    SDL_FRect crouch = {605, 24, 84, 92};
    bool isPlayer2;
    bool hit;
    SDL_Scancode runKey, hitKey, attackBKey, retreatKey, crouchKey, jumpKey;
    int frameNum, frameNum2 = 0;
    float lastFrameTime, lastFrameTime2;
    char *action;
    float hp = 100;
    Player(SDL_Renderer *renderer, bool player2);
    ~Player();
    void update(float curTick);
    void render(SDL_Renderer *renderer);
    static Entity init(SDL_Renderer *renderer, bool p2);
};
typedef struct
{
    float x, y;

} Pos;
typedef struct
{
    float x, y, w, h;

} Frame;
#endif // PLAYER_H
