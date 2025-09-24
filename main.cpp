#include <iostream>
#include "Properties/head.h"

class Point {
    int* _x = new int{0};
    int* _y = new int{0};
public:
    Property<int> x {
        [this](){ return *_x; },
        [this](auto v){ _x = new int{v}; },
        [this](){ return _x; },
        [this](){ delete _x; }
    };

    Property<int> y {
        [this](){ return *_y; },
        [this](auto v){ _y = new int{v}; },
        [this](){ return _y; },
        [this](){ delete _y; }
    };
    
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

};

int main(){
    Point x{1,2};
    return 0;
}