#ifndef DIE_CPP
#define DIE_CPP

#include "die.hpp"
#include <cstdlib>
#include <ctime>

int die::roll() {
    srand(time(0));
    return (rand() % 6) + 1;
}

#endif