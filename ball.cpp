#include "ball.hpp"

void Ball::bounce_with_angle(double ratio){
        double new_v_x = ratio * std::sqrt(2)/2;
        double new_v_y = -std::abs(v_y);
        v_x = new_v_x/std::sqrt(new_v_x*new_v_x+new_v_y*new_v_y);
        v_y = new_v_y/std::sqrt(new_v_x*new_v_x+new_v_y*new_v_y);
        // std::cerr << v_y << std::endl;
        return ;
    }

std::pair<double,double> Ball::compute_new_pos(){
    x = x + total_v * v_x * delta_T;
    y = y + total_v * v_y * delta_T;
    return std::pair<double,double>(x,y);
}