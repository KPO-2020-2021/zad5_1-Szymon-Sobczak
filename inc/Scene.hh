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

        PzG::InfoPlikuDoRysowania *tab_of_properties_d1[5];

        PzG::InfoPlikuDoRysowania *tab_of_properties_d2[5];

        PzG::LaczeDoGNUPlota Link;

        unsigned int nbr_of_active_drone;

    public:
        Scene(PzG::LaczeDoGNUPlota & Link);

        void choose_drone(unsigned int active_drone);

        Drone const & get_active_drone();

        Drone & use_active_drone();
};