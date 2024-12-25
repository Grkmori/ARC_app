
#pragma once

#include "utilities/debug.hpp"
#include "loader.hpp"
#include "graphics.hpp"
#include "grid.hpp"

using namespace sf;
using json = nlohmann::json;


class Network {
private:
    /* CONSTRUCTOR - PARAMETERS */
    // Classes //
    Debug debug;


    /* FUNCTION - INITIALIZATION */
    void initialize();


public:
    /* COSTRUCTOR (AND DESTRUCTOR) */
    Network();
    ~Network();  
};
