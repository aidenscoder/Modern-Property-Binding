#include <iostream>
#include "Properties/head.h"
#include "string.h"

class nametag {
private:
    std::string internal;
public:
    Property<std::string> name {
        [this](){ return internal; },
        [this](auto value){ internal = value; },
        [this](){ return &internal; }
    };
    nametag(std::string internal){
        name = internal;
    }
    
};

int main(){
    nametag x = nametag("hello");
    return 0;
}