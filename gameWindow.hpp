#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include<SDL2/SDL.h>

class GameWorld;

/**
 * @brief Describes the display window using SDL2.
 * 
 */
class GameWindow{
private:
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Renderer* renderer;

    int height, width;

    char* TITLE = "Block Breaker 1.0";

    GameWorld *world = nullptr;

public:
    GameWindow(int w = 1280, int h = 720){
        window = NULL;
        screenSurface = NULL;
        renderer = NULL;
        height = h;
        width = w;
    }

    GameWindow(GameWorld* parent,int w = 1280, int h = 720){
        window = NULL;
        screenSurface = NULL;
        height = h;
        width = w;
        world = parent;
    }

    void quit(){
        SDL_FreeSurface(screenSurface);
        screenSurface = NULL;
        SDL_DestroyWindow(window);
        window = NULL;
        SDL_Quit();
    }

    bool init(){
        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
        if (window == NULL)
            return false;
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
            return false;
        return true;
    }

    int getWidth(){
        return width;
    }

    int getHeight(){
        return height;
    }

    /**
     * @brief Display all elements contained in the world, plus the score.
     * 
     * @return true 
     * @return false 
     */
    bool display();


};

#endif