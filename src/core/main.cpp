#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_oldnames.h>
#include <./core/game.h>
#include <./core/menu.cpp>
#include <./core/choosechars.cpp>
#include <./engine/collision.cpp>
#include <./engine/facing.cpp>
#include <./characters/axl_low.h>
#include <./characters/milia_rage.h>
#include <./core/entities.h>
#define RENDER_ENTITIES(entities, entities_count, renderer) \
    for (int i = 0; i < entities_count; i++)                \
    {                                                       \
        entities[i].render(renderer, entities[i].data);     \
    }
#define HANDLE_EVENTS_ENTITIES(entities, entities_count, event) \
    for (int i = 0; i < entities_count; i++)                    \
    {                                                           \
        entities[i].handle_events(event);                       \
    }

#define QUIT_ENTITIES(entities, entities_count) \
    for (int i = 0; i < entities_count; i++)    \
    {                                           \
        entities[i].quit();                     \
    }

#define UPDATE_ENTITIES(entities, entities_count, cur, last, time) \
    for (int i = 0; i < entities_count; i++)                       \
    {                                                              \
        entities[i].update(cur, last, time, entities[i].data);     \
    }

Uint64 last_tick = 0;
Uint64 current_tick = 0;
float delta_time;

SDL_Window *window;
SDL_Renderer *renderer;
Menu *menu;
chooseChars *choseChars;
Entity entities[MAX_ENTITY];
int entity_count = 0;
int gameState = 0;

struct HPBar
{
    float x, y;
    float width, height;
    float currentHP;
    float maxHP = 100;
    SDL_Color color;
};
HPBar player1HPBar;
HPBar player2HPBar;
void drawHPBar(SDL_Renderer *ren, HPBar bar)
{
    SDL_FRect backgroundRect = {bar.x, bar.y, bar.width, bar.height};
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Black background
    SDL_RenderFillRect(ren, &backgroundRect);

    SDL_FRect hpRect = {bar.x, bar.y, (bar.currentHP / bar.maxHP * bar.width), bar.height};
    SDL_SetRenderDrawColor(ren, bar.color.r, bar.color.g, bar.color.b, bar.color.a);
    SDL_RenderFillRect(ren, &hpRect);
}
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    QUIT_ENTITIES(entities, entity_count);
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void update()
{
    if (gameState == 1)
    {
        choseChars->handleInput();
        gameState += choseChars->shouldGoToGameplay();
    }
    if (gameState == 0)
    {
        menu->handleInput();
        gameState += menu->shouldGoToGameplay();
        if (gameState == 1)
            choseChars = new chooseChars(renderer);
    }

    last_tick = current_tick;
    current_tick = SDL_GetTicks();
    delta_time = (current_tick - last_tick) / 1000.0f;
    std::vector<Entity *> entityVec;
    for (size_t i = 0; i < MAX_ENTITY; i++)
    {
        entityVec.push_back(&entities[i]);
    }
    Player *p1 = static_cast<Player *>(entities[0].data);
    player1HPBar.currentHP = p1->hp;
    Player *p2 = static_cast<Player *>(entities[1].data);
    player2HPBar.currentHP = p2->hp;
    CollisionChecker::checkCollision(entityVec);
    F2F::Facing(entityVec);
    UPDATE_ENTITIES(entities, entity_count, current_tick, last_tick, delta_time);
}

void render()
{
    SDL_RenderClear(renderer);
    menu->render();
    RENDER_ENTITIES(entities, entity_count, renderer);
    drawHPBar(renderer, player1HPBar);
    drawHPBar(renderer, player2HPBar);
    if (gameState == 1)
        choseChars->render();
    if (gameState == 0)

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background

    SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{

    update();
    render();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Error initializing SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow(
        "SDL5 Game",
        800,
        500,
        NULL);

    if (!window)
    {
        SDL_Log("Error creating window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        SDL_Log("Error creating renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    AxlLow milia1(renderer, false);
    entities[entity_count++] = milia1.init(renderer, false);

    MiliaRage milia2(renderer, true);
    entities[entity_count++] = milia2.init(renderer, true);
    player1HPBar = {10.0f, 10.0f, 200.0f, 20.0f, 100.0f, 100.0f, {255, 0, 0, 255}}; // Red
    player2HPBar = {590.0f, 10.0f, 200.0f, 20.0f, 100.0f, 100.0f, {255, 0, 0, 255}};
    menu = new Menu(renderer);
    return SDL_APP_CONTINUE;
}