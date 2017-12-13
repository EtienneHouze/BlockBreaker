#include "gameWindow.hpp"
#include "gameWorld.hpp"
#include "charDisplay.cpp"
#include<string>

bool GameWindow::display(){
    SDL_RenderClear(renderer);
    std::vector<SDL_Rect> blocksToDisplay = world->blockToDisplay();
    SDL_Rect ballRect = world->getBallRect();
    SDL_Rect playerRect = world->getPlayerBreaker();
    SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x00);
    SDL_RenderFillRect(renderer,NULL);
    SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,0xFF);
    for (auto it = blocksToDisplay.begin(); it != blocksToDisplay.end(); ++it){
        SDL_RenderFillRect(renderer,&(*it));
    }
    SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,0x00);
    SDL_RenderFillRect(renderer,&playerRect);
    SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer,&ballRect);
    auto scoreString = std::string("SCORE ");
    scoreString.append(std::to_string(world->getScore()));
    SDL_Rect where_text = SDL_Rect();
    where_text.x = 200;
    where_text.w = 16;
    where_text.h = 30;
    where_text.y = 680;
    charDisplay::display_from_left(renderer,&where_text,scoreString);
    SDL_RenderPresent(renderer);

}