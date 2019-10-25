//
// Created by Jeronimo on 2019-10-24.
//

#ifndef CALCULATOR_DRIVER_H
#define CALCULATOR_DRIVER_H

#include "Token_stream.h"

void calculate(){
    while(true){
        ts.get();
        if(ts.current().kind == Kind::end) break;
        if(ts.current().kind == Kind::print) continue;
        std::cout<< expr(false)<<'\n';
    }
}

#endif //CALCULATOR_DRIVER_H