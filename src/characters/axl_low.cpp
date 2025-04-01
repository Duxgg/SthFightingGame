#include "axl_low.h"

AxlLow::AxlLow(SDL_Renderer *renderer, bool player2)
    : Player(renderer, player2) // Call base class constructor
{
    runFrames = {
        {483, 152, 88, 92}, {483, 152, 88, 92}, {576, 152, 88, 92}, {576, 152, 88, 92}};

    attackFrames = {
        {0, 267, 69, 92}, {69, 267, 128, 92}, {197, 267, 118, 92}, {315, 267, 73, 92}, {0, 24, 84, 92}};

    attackBFrames = {
        {394, 267, 76, 92}, {470, 267, 162, 92}, {632, 267, 190, 92}, {821, 267, 163, 92}, {394, 267, 76, 92}};

    attackABFrames = {
        {1069, 281, 69, 77}, {1136, 281, 80, 77}, {1089, 121, 122, 157}, {1214, 221, 119, 137}, {1333, 275, 63, 83}, {0, 267, 69, 92}};
    attackFAFrames = {
        {0, 396, 97, 92}, {98, 363, 83, 144}, {181, 363, 115, 144}, {296, 395, 69, 90}, {296, 395, 69, 90}, {0, 267, 69, 92}};
    walkFrames = {
        {393, 150, 78, 92}, {317, 150, 78, 92}, {240, 150, 78, 92}, {157, 150, 78, 92}, {73, 150, 78, 92}, {2, 150, 78, 92}};

    jumpFrames = {
        {772, 150, 88, 92}, {772, 150, 88, 92}, {772, 150, 88, 92}, {772, 150, 88, 92}, {860, 165, 69, 77}, {923, 119, 57, 123}, {923, 119, 57, 123}, {923, 119, 57, 123}, {923, 119, 57, 123}, {0, 24, 84, 92}};
    jumpAFrames = {
        {2, 893, 117, 92}, {123, 893, 195, 115}, {123, 893, 195, 115}, {123, 893, 195, 115}, {2, 893, 117, 92}};
    const char *path = "C:/Users/dug26/OneDrive/Desktop/game/sthfighter/assets/axl_low2 (1).png";
    texture = IMG_LoadTexture(renderer, path);
}
Entity AxlLow::init(SDL_Renderer *renderer, bool isPlayer2)
{
    AxlLow *milia = new AxlLow(renderer, isPlayer2);
    Entity entity = {
        .quit = []() {},
        .handleInput = [](SDL_Event *) {},
        .update = [](float curTick, float, float, void *data)
        { static_cast<AxlLow *>(data)->update(curTick); },
        .render = [](SDL_Renderer *renderer, void *data)
        { static_cast<AxlLow *>(data)->render(renderer); },
        .data = milia};
    return entity;
}