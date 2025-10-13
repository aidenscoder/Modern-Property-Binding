#include <iostream>
#include "Properties/head.h"
#include <cstdbool>

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
};

int main(){
    return 0;
}