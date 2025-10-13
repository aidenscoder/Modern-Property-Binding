#include <iostream>
#include "Properties/head.h"

class Point {
    int _x,_y;
    property<int> x {
        get_p {  return _x; },
        set_p { _x = value; },
        ref_p { return &_x; }
    };

    property<int> y {
        get_p { return _y; },
        set_p { _y = value; },
        ref_p { return &_y; }
    };

public:
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

int main(){
    Point x = {1,2};
    x;
    return 0;
}