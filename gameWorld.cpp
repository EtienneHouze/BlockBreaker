#include "gameWorld.hpp"

void GameWorld::updateAllPos(){
        ball.compute_new_pos();
        player.updatePos();
    }


std::vector<Block>::iterator GameWorld::manageBounces(Ball* ball){
        for (auto it = blocks.begin(); it != blocks.end(); ++it){
            if (it->collides(*ball)){
                ball->bounce_vertical();
                return it;
            }
        }
        if (player.collides(*ball)){
                ball->bounce_with_angle((ball->getPos().first-player.getPos().first)/player.getDim().first);
                return blocks.end();
            }
            std::pair<double,double> ballPos = ball->getPos();
            if (ballPos.first < 0 || ballPos.first > gameWidth)
                ball->bounce_horizontal();
            if (ballPos.second < 0)
                ball->bounce_vertical();
            return blocks.end();
    }


void GameWorld::run(){
        SDL_Event e;
        while(true){
            std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
            window.display();
            updateAllPos();
            auto touched = manageBounces(&ball);
            if (touched != blocks.end()){
                score += touched->givePoints();
                blocks.erase(touched);
            }
            double timeSpan = 0;
            int number_of_inputs = 0;
            bool playerQuit = false;
            while (timeSpan < delta_T){
                SDL_PollEvent(&e);
                if (e.type == SDL_QUIT){
                    playerQuit = true;
                    break;
                }
                switch (e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        if(number_of_inputs == 0){
                            player.accelerate(1);
                            number_of_inputs++;
                        }
                        break;
                    case SDLK_LEFT:
                        if (number_of_inputs == 0){
                            player.accelerate(-1);
                            number_of_inputs ++;
                        }
                        break;
                    default:
                        player.accelerate(0);
                        break;
                }
                std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double,std::milli> timeDiff = t2 - beginTime;
                timeSpan = timeDiff.count()/1000;
            }
            if (number_of_inputs == 0)
                player.accelerate(0);
            if (playerQuit)
                break;
            if(ball.isLost()){
                lives--;
                if (lives > -1){
                    ball = Ball(0,delta_T);
                    score -= (3-lives)*10;
                    player = PlayerBreaker(0,50,50,10,3);
                    window.display();
                    SDL_Delay(1000);
                }
            }
            if (lives < 0){
                std::cout << "You lost !" << std::endl;
                break;
            }
            if(blocks.size() == 0){
                std::cout << "Level complete ! \n Your score is : " << score << "\n Now to the next !" <<std::endl;
                new_level();
                window.display();
                SDL_Delay(1000);
                }
            SDL_Delay(std::floor(delta_T*1000));
        }

    }



bool GameWorld::init(int sWidth, int sHeight){
        window = GameWindow(this,sWidth,sHeight);
        return window.init();
    }