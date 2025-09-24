#include <iostream>
#include "Properties/head.h"

class Point {
    int _x = 0;
    int _y = 0;
public:
    Property<int> x {
        [this](){ return _x; }, //get
        [this](auto v){ _x = v; }, //set
        [this](){ return &_x; } //refrence
    };

    Property<int> y {
        [this](){ return _y; }, //get
        [this](auto v){ _y = v; }, //set
        [this](){ return &_x; } //refrence
    };
    
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

};

int main(){
    Point p{13,16};
    for (int i = 0; i < p.x; i++){
        std::cout << i << std::endl;
    }
    return 0;
}