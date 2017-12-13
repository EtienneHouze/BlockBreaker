// A simple block breaker game I coded to try SDL2 functions.
// Nothing too fancy here, but it is pretty much working.
// Author : Etienne Houze, December 2017


#include <iostream>
#include "gameWorld.hpp"



int main(int argc, char** argv){
    GameWorld world = GameWorld();  
    bool test_init = world.init(1280,720);  
    if (test_init){
        world.run();
        world.quit();
    }
    else{
        std::cerr << "Error : the world has not been initialized."<<std::endl;
        return -1;
    }
    return 0;
}