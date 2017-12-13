#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include<vector>
#include<SDL2/SDL.h>
#include <cmath>
#include<chrono>
#include <ctime>
#include<ratio>

#include "block.hpp"
#include "playerBreaker.hpp"
#include "ball.hpp"
#include "gameWindow.hpp"

/**
 * @brief Defines the game universe, containing all other elements.
 * 
 */
class GameWorld{
private:
    int score;  // Score of the player
    int lives;  // Number of lives remaining.
    PlayerBreaker player;   // Raquette controlled by the player.
    std::vector<Block> blocks;  // Vector of all the remaining blocks.
    Ball ball;  // Ball
    int difficulty; // Unused.
    double delta_T; // Time step between two frames
    GameWindow window;  // The display.
    double gameWidth = 100;
    double gameHeight = 50;

    double DEFAULT_DELTA = 0.0166666; // default timestep (60 frames per second)

public:
    GameWorld(){
        score = 0;
        lives = 3;
        player = PlayerBreaker(0,50,50,10,3);
        difficulty = 0;
        blocks = std::vector<Block>(40);
        for (int i = 0; i < 40; i++){
            blocks[i] = Block(i,(39-i)/8,(i%8)*12 + 8,(i/8)*5 + 3,10,3);
        }
        delta_T = DEFAULT_DELTA;
        ball = Ball(0,delta_T);
    }

    /**
     * @brief Initializes the window to display the game
     * 
     * @param sWidth width of the display
     * @param sHeight height of the display
     * @return true if init is successful
     * @return false else
     */
    bool init(int sWidth, int sHeight);


    /**
     * @brief Main loop of the game
     * 
     */
    void run();

    /**
     * @brief destroys the game and the display.
     * 
     */
    void quit(){
        window.quit();
    }

    /**
     * @brief getter for the remaining blocks
     * 
     * @return std::vector<SDL_Rect> returns rectangles for every block
     */
    std::vector<SDL_Rect> blockToDisplay(){
        auto ans = std::vector<SDL_Rect>();
        int window_h = window.getHeight();
        int window_w = window.getWidth();
        double scaling_x = (double)(window_w)/gameWidth;
        double scaling_y = (double)(window_h)/gameHeight;
        for (auto it = blocks.begin(); it != blocks.end(); ++it){
            SDL_Rect newRect = SDL_Rect();
            auto blockPos = it->getPos();
            auto blockDim = it->getDims();
            newRect.h = blockDim.second * scaling_y;
            newRect.w = blockDim.first * scaling_x;
            newRect.x = (blockPos.first - (blockDim.first/2)) * scaling_x;
            newRect.y = (blockPos.second - (blockDim.second/2)) * scaling_y;
            ans.push_back(newRect);
        }
        return ans;
    }

    SDL_Rect getPlayerBreaker(){
        int window_h = window.getHeight();
        int window_w = window.getWidth();
        double scaling_x = (double)(window_w)/gameWidth;
        double scaling_y = (double)(window_h)/gameHeight;
        SDL_Rect ans = SDL_Rect();
        ans.h = player.getDim().second * scaling_y;
        ans.w = player.getDim().first * scaling_y;
        ans.x = (player.getPos().first - (player.getDim().first/2)) * scaling_x;
        ans.y = (player.getPos().second - (player.getDim().second/2)) * scaling_y;
        return ans;
    }

    int getScore(){
        return score;
    }

    SDL_Rect getBallRect(){
        int window_h = window.getHeight();
        int window_w = window.getWidth();
        double scaling_x = (double)(window_w)/gameWidth;
        double scaling_y = (double)(window_h)/gameHeight;
        SDL_Rect ans = SDL_Rect();
        ans.h =  scaling_y;
        ans.w =  scaling_y;
        ans.x = (ball.getPos().first - 1/2) * scaling_x;
        ans.y = (ball.getPos().second - 1/2) * scaling_y;
        return ans;
    }

private:

    /**
     * @brief Computes an updates new positions for the player and the ball
     * 
     */
    void updateAllPos();

    /**
     * @brief Checks if the ball collides something and updates its speed accordingly.
     * 
     * @param ball 
     * @return std::vector<Block> ::iterator an iterator to the collided block, or to the end of the block vector if no collision.
     */
    std::vector<Block>::iterator manageBounces(Ball* ball);

    void new_level(){
        blocks = std::vector<Block>(40);
        for (int i = 0; i < 40; i++){
            blocks[i] = Block(i,(39-i)/8,(i%8)*12 + 8,(i/8)*5 + 3,10,3);
        }
        ball = Ball(0,delta_T);
        player = PlayerBreaker(0,50,50,10,3);
    }

};

#endif