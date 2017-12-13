#ifndef BALL_HPP
#define BALL_HPP

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>

/**
 * @brief Describes the ball in the game
 * 
 */
class Ball{
private:
    int id;
    double x,y;
    double radius;
    /**
     * @brief v_x and v_y are between 0 and 1, and correspond to the sine and cosine of the normalized velocity vector
     * 
     */
    double v_x, v_y;    
    /**
     * @brief Actual value of the velocity.
     * 
     */
    double total_v = 0;
    double delta_T;

public:
    Ball(int _id = 0, double delta = 0.0166666666):delta_T(delta){
        x = 51;
        y = 25;
        id = _id;
        v_x = 0;
        v_y = 1;
        total_v = 30;
        radius = 1;
    }

    /**
     * @brief Used for bounde upon the play raquette.
     * 
     * @param ratio between -1 an +1, correspond to the position of the ball center regarding the center of the raquette.
     */
    void bounce_with_angle(double ratio);

    /**
     * @brief Used when the ball bounces upon a block or the top of the window.
     * 
     */
    void bounce_vertical(){
        v_y = -v_y;
    }

    /**
     * @brief Used when the ball bounces upon the walls of the window.
     * 
     */
    void bounce_horizontal(){
        v_x = - v_x;
    }

    /**
     * @brief Checks if the ball is lost.
     * 
     * @return true 
     * @return false 
     */
    inline bool isLost()const{
        return (y > 50); // This assumes the game world is 50 units high.
    }


    inline double getRadius()const{
        return radius;
    }

    inline std::pair<double,double> getPos()const{
        return std::pair<double,double>(x,y);
    }

    /**
     * @brief Updates and returns the new position of the ball.
     * 
     * @return std::pair<double,double> the (x,y) new position.
     */
    std::pair<double,double> compute_new_pos();
};

#endif