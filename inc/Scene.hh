#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"
#include "Cuboid.hh"
#include "Hexagonal_prism.hh"
#include "lacze_do_gnuplota.hh"

class Drone{
    private:
        Drone Drones[2];
        PzG::LaczeDoGNUPlota Link;
    public:
        Drone const & get_active_drone();
        Drone & Use_active_dron();
};