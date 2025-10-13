#include <iostream>
#include "Properties/head.h"

class Point {
    int _x,_y;
public:
    Property<int> x{
        [this](){return _x;},
        [this](auto v){_x = x;}
    };

    Property<int> y{
        [this](){return _y;},
        [this](auto v){_y = x;}
    };

    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};
