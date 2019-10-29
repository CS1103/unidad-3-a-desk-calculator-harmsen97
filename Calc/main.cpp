#include <iostream>
#include <fstream>
#include <sstream>

#include "driver.h"

int main() {

    table["pi"] = 3.14;

    std::ifstream archivo("../prueba", std::ios::in);
    std::string expresion;
    while(archivo>>expresion){
        ts.set_input(new std::istringstream{expresion});

        calculate();

    }



    return no_of_errors;
}