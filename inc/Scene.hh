#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"
#include "Cuboid.hh"
#include "Drone.hh"
#include "Hexagonal_prism.hh"
#include "lacze_do_gnuplota.hh"

class Scene{
    private:
        std::vector <Drone> Drones;

        PzG::LaczeDoGNUPlota Link;

        unsigned int nbr_of_active_drone;

    public:
        Scene();

        void choose_drone(unsigned int active_drone);

        Drone const & get_active_drone();

        Drone & use_active_drone();
};