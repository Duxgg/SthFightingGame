#include "player.h"
#include <iostream>
#define GROUN 400
Player::Player(SDL_Renderer *renderer, bool player2) : isPlayer2(player2),
                                                       position{300, GROUN, 84, 92}

{
    isPlayer2 = player2;
    frameNum = 0;
    lastFrameTime = 0;
    lastFrameTime2 = 0;
    action = "\0";

    // Set controls
    if (!player2)
    {
        runKey = SDL_SCANCODE_F;
        hitKey = SDL_SCANCODE_J;
        retreatKey = SDL_SCANCODE_A;
        crouchKey = SDL_SCANCODE_S;
        jumpKey = SDL_SCANCODE_W;
        attackBKey = SDL_SCANCODE_U;
    }
    else
    {
        runKey = SDL_SCANCODE_RIGHT;
        hitKey = SDL_SCANCODE_K;
        retreatKey = SDL_SCANCODE_LEFT;
        crouchKey = SDL_SCANCODE_DOWN;
        jumpKey = SDL_SCANCODE_UP;
        attackBKey = SDL_SCANCODE_I;
    }
}

Player::~Player()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

void Player::update(float curTick)
{
    const bool *keyboardState = SDL_GetKeyboardState(NULL);

    if (curTick > lastFrameTime + 30)
    {
        lastFrameTime = curTick;

        if (hit == true)
        {
            if (frameNum == 0)
                hp -= 5;
            if (frameNum < 3)
                frameNum++;
            else
            {
                hit = false;
                return;
            }
            portion = hitFrames;
            position = {position.x, GROUN, portion.w, portion.h};
            if (isPlayer2)
                position.x += 5;
            else
                position.x -= 5;
            return;
        }
        if (action == "J")
        {
            if (curTick > lastFrameTime2 + 100)
            {
                lastFrameTime2 = curTick;

                portion = attackFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                hitbox = {dstRect.x, dstRect.y, portion.w, portion.h};

                if (frameNum < 4)
                    frameNum++;
                else
                {
                    action = "\0";
                    hitbox = {0, 0, 0, 0};
                    return;
                }
            }
            return;
        }
        if (action == "AB")
        {
            if (curTick > lastFrameTime2 + 150)
            {
                lastFrameTime2 = curTick;

                portion = attackABFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                hitbox = {dstRect.x, dstRect.y, portion.w, portion.h};

                if (frameNum < 5)
                    frameNum++;
                else
                {
                    action = "\0";
                    hitbox = {0, 0, 0, 0};
                    return;
                }
            }
            return;
        }
        if (action == "FA")
        {
            if (curTick > lastFrameTime2 + 150)
            {
                lastFrameTime2 = curTick;

                portion = attackFAFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                hitbox = {dstRect.x, dstRect.y, portion.w, portion.h};
                if (isPlayer2)
                    position.x -= 20;
                else
                    position.x += 20;
                if (frameNum < 5)
                    frameNum++;
                else
                {
                    action = "\0";
                    hitbox = {0, 0, 0, 0};
                    return;
                }
            }
            return;
        }
        if (action == "B")
        {

            if (curTick > lastFrameTime2 + 100)
            {
                lastFrameTime2 = curTick;

                portion = attackBFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                hitbox = {dstRect.x, dstRect.y, portion.w, portion.h};

                if (frameNum < 4)
                    frameNum++;
                else
                {
                    action = "\0";
                    hitbox = {0, 0, 0, 0};
                    return;
                }
            }
            return;
        }
        if (action == "W")
        {
            if (curTick > lastFrameTime2 + 50)
            {
                lastFrameTime2 = curTick;

                if (keyboardState[retreatKey])
                {
                    if (isPlayer2)
                    {
                        position.x -= 20;
                    }
                    else
                    {

                        position.x -= 10;
                    }
                }
                else if (keyboardState[runKey])
                {
                    if (!isPlayer2)
                    {
                        position.x += 20;
                    }
                    else
                    {
                        position.x += 10;
                    }
                }

                portion = jumpFrames[frameNum];
                position = {position.x, position.y, portion.w, portion.h};
                if (keyboardState[hitKey] && frameNum == 4)
                {
                    portion = jumpAFrames[frameNum2];
                    position = {position.x, position.y, portion.w, portion.h};
                    if (frameNum2 < 4)
                    {
                        frameNum -= 1;
                        frameNum2++;
                    }
                }
                else if (frameNum <= 3)
                    position.y -= 25;
                else if (frameNum > 4 && frameNum <= 8 && position.y < GROUN)
                    position.y += 25;
                if (frameNum < 9)
                    frameNum++;
                else
                {
                    frameNum2 = 0;
                    action = "\0";
                    return;
                }
            }
            return;
        }
        if ((keyboardState[hitKey] && keyboardState[runKey] && !isPlayer2) || (keyboardState[hitKey] && keyboardState[retreatKey] && isPlayer2))
        {
            frameNum = 0;
            action = "FA";
            return;
        }
        if (keyboardState[retreatKey])
        {
            if (keyboardState[jumpKey])
            {
                frameNum = 0;
                action = "W";
            }
            if (isPlayer2)
            {
                frameNum = (frameNum + 1) % 4;
                position.x -= 20;
                portion = runFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                return;
            }
            else
            {
                frameNum = (frameNum + 1) % 6;
                position.x -= 10;
                portion = walkFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                return;
            }
        }

        if (keyboardState[runKey])
        {
            if (keyboardState[jumpKey])
            {
                frameNum = 0;
                action = "W";
            }
            if (!isPlayer2)
            {
                frameNum = (frameNum + 1) % 4;
                position.x += 20;
                portion = runFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                return;
            }
            else
            {
                frameNum = (frameNum + 1) % 6;
                position.x += 10;
                portion = walkFrames[frameNum];
                position = {position.x, GROUN, portion.w, portion.h};
                return;
            }
        }
        else
        {
            frameNum = 0;
        }

        if (keyboardState[crouchKey])
        {
            portion = crouch;
            return;
        }

        if (keyboardState[hitKey] && keyboardState[attackBKey])
        {
            action = "AB";
            return;
        }
        if (keyboardState[hitKey])
        {
            action = "J";
            return;
        }
        if (keyboardState[attackBKey])
        {
            action = "B";
            return;
        }

        if (keyboardState[jumpKey])
        {
            frameNum = 0;
            action = "W";
            return;
        }

        portion = stan;
        position.w = portion.w;
        position.h = portion.h;
    }
}

void Player::render(SDL_Renderer *renderer)
{
    SDL_FlipMode flip = isPlayer2 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    dstRect = position;
    if (isPlayer2)
    {
        dstRect.x = position.x - portion.w; // Adjust x for Player 2
    }
    dstRect.y = position.y - portion.h;
    SDL_RenderTextureRotated(renderer, texture, &portion, &dstRect, 0, NULL, flip);
}

// Initialize function to return Player entity
Entity Player::init(SDL_Renderer *renderer, bool isPlayer2)
{
    Player *player = new Player(renderer, isPlayer2);
    Entity entity = {
        .quit = []() {},
        .handleInput = [](SDL_Event *) {},
        .update = [](float curTick, float, float, void *data)
        { static_cast<Player *>(data)->update(curTick); },
        .render = [](SDL_Renderer *renderer, void *data)
        { static_cast<Player *>(data)->render(renderer); },
        .data = player};
    return entity;
}
