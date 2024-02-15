#include <iostream>
#include "objekt.h"

Objekt::Objekt(int x, int y) {
    this->x = x;
    this->y = y;
}

void Objekt::izpis() {
    std::cout << "x: " << x << " y: " << y << std::endl;
}