#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL.h>
#include <vector>
#include <string>

class chooseChars
{
private:
    SDL_Renderer *renderer;
    std::vector<std::string> options = {"Press X to Start", "Options", "Exit"};
    int selectedOption = 0;
    bool isRunning = true;
    bool goToGameplay = false;
    // Font for rendering text
    SDL_Color textColor = {255, 255, 255, 255}; // White text

public:
    SDL_Texture *backgroundTexture;

    chooseChars(SDL_Renderer *ren) : renderer(ren)
    {
        backgroundTexture = IMG_LoadTexture(renderer, "C:/Users/dug26/OneDrive/Desktop/game/sthfighter/assets/bg.png");
        if (!backgroundTexture)
        {
            SDL_Log("IMG_LoadTexture: %s\n");
        }
    }

    ~chooseChars()
    {
        if (backgroundTexture)
        {
            SDL_DestroyTexture(backgroundTexture);
        }
    }

    void handleInput()
    {
        const bool *keyboardState = SDL_GetKeyboardState(NULL);

        static bool upPressed = false;
        static bool downPressed = false;
        static bool enterPressed = false;
        static bool xPressed = false;

        if (keyboardState[SDL_SCANCODE_UP])
        {
            if (!upPressed)
            {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
                upPressed = true;
            }
        }
        else
        {
            upPressed = false;
        }

        if (keyboardState[SDL_SCANCODE_DOWN])
        {
            if (!downPressed)
            {
                selectedOption = (selectedOption + 1) % options.size();
                downPressed = true;
            }
        }
        else
        {
            downPressed = false;
        }

        if (keyboardState[SDL_SCANCODE_RETURN])
        {
            if (!enterPressed)
            {
                executeOption();
                enterPressed = true;
            }
        }
        else
        {
            enterPressed = false;
        }

        if (keyboardState[SDL_SCANCODE_A])
        {
            goToGameplay = true;
            isRunning = false;
            xPressed = true;
        }
    }

    void executeOption()
    {
        if (options[selectedOption] == "Press X to Start")
        {
            SDL_Log("Starting Game...");
            isRunning = false;
            goToGameplay = true;
        }
        else if (options[selectedOption] == "Options")
        {
            SDL_Log("Options Menu Selected.");
        }
        else if (options[selectedOption] == "Exit")
        {
            SDL_Log("Exiting Game.");
            isRunning = false;
        }
    }

    void render()
    {
        SDL_RenderTexture(renderer, backgroundTexture, NULL, NULL);

        // Render text
        for (size_t i = 0; i < options.size(); i++)
        {
        }
    }

    bool running() { return isRunning; }
    bool shouldGoToGameplay() { return goToGameplay; }
};