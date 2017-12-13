#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "ball.hpp"
#include<vector>
/**
 * @brief Class describing a block to destroy.
 * 
 */
class Block{
private:
    double x, y;
    int id;
    int category;
    
    double height, width;
    /**
     * @brief The number of points given according to the category of the block
     * 
     */
    const int cat2points[4] = {1,2,4,8};
    /**
     * @brief Not implemented, but colors could be assigned to every category.
     * 
     */
    const unsigned short cat2R[4] = {0xF0, 0xFF, 0x00, 0x00};
    const unsigned short cat2B[4] = {0x00, 0x00, 0xF0, 0xFF};

public:
    Block(int _id=0, int cat = 0, double _x=0, double _y=0, double w=10, double h=3){
        id = _id;
        if (cat > -1 && cat < 4)
            category = cat;
        else
            category = 0;
        x = _x;
        y = _y;
        height = h;
        width = w;
    }
    /**
     * @brief Checks if the ball collides the block
     * 
     * @param ball reference to the ball of the game
     * @return true if collision
     * @return false it no collision
     */
    bool collides(const Ball& ball){
        auto ballPos = ball.getPos();
        double rad = ball.getRadius();
        if (ballPos.first-rad  < x + (width/2) && ballPos.first+rad > x - (width/2)
            && ballPos.second-rad < y + (height/2) && ballPos.second + rad > y - (height/2))
            return true;
        return false;
    }
    /**
     * @brief Gives the amount of points for breaking this block
     * 
     * @return int 
     */
    int givePoints(){
        return cat2points[category];
    }

    /**
     * @brief Getter for the position (top-left corner) of the block
     * 
     * @return std::pair<double,double> getPos the (x,y) coordinates
     */
    std::pair<double,double> getPos() const{
        return std::pair<double,double>(x,y);
    }

    /**
     * @brief getter for the dimensions.
     * 
     * @return std::pair<double,double> getDims dimensions (w,h)
     */
    std::pair<double,double> getDims() const{
        return std::pair<double,double>(width,height);
    }

    /**
     * @brief Overloaded equal operator, not to copy the const fields.
     * 
     * @param other 
     * @return Block& 
     */
    Block & operator=(const Block & other){
        height = other.height;
        width = other.width;
        id = other.id;
        x = other.x;
        y = other.y;
        category = other.category;
        return *this;
    }

};

#endif