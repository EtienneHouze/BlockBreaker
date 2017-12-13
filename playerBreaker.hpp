#ifndef PLAYERBREAK_HPP
#define PLAYERBREAK_HPP

#include <vector>
#include <cmath>

#include "ball.hpp"

class PlayerBreaker{
private:
    double x,y;
    double v_x;
    double max_v;
    double acceleration;
    double width, height;
    int id;
    double DELTA_T;

public:
    PlayerBreaker(){}

    PlayerBreaker(int _id,double _x, double _y, double w = 10, double h = 3,int acc = 15, double delta = 0.016666666667){
        id = _id;
        x = _x;
        y = _y;
        width = w;
        height = h;
        v_x = 0;
        DELTA_T = delta;
        acceleration = acc;
        max_v = 30;
    }

    void updatePos(){
        x += v_x * DELTA_T;
        if (x < 0)
            x = 0;
        if (x > 100)
            x = 100;
    }

    std::pair<double,double> getPos(){
        return std::pair<double,double>(x,y);
    }

    std::pair<double,double> getDim(){
        return std::pair<double,double>(width,height);
    }

    bool collides(const Ball& ball){
        auto ballPos = ball.getPos();
        double rad = ball.getRadius();
        if (ballPos.first-rad  < x + (width/2) && ballPos.first+rad > x - (width/2)
            && ballPos.second-rad < y + (height/2) && ballPos.second + rad > y - (height/2))
            return true;
        return false;
    }

    void accelerate(int direction){
        if (direction > 0)
            v_x = std::min(max_v,x+acceleration);
        if (direction < 0)
            v_x = std::max(-max_v,v_x-acceleration);
        else
            v_x = v_x * 0.8;
    }

};

#endif