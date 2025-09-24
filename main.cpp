#include <iostream>
#include "Properties/head.h"

class Point {
    int* _x = 0;
    int* _y = 0;
public:

    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    Property<int> x {
        [this](){ return _x; },
        [this](auto value){ _x = value; },
        [this](){},
        [this](){ return _x; }
    };
    Property<int> y {
        [this](){ return _y; },
        [this](auto value){ _y = value; },
        [this](){},
        [this](){ return _y; }
    };
};

int main(){
    Point x{1,2};
    return 0;
}