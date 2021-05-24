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
        Vector3D location;
        Hexagonal_prism rotors[4];
        Cuboid fuselage;
        double Orientation_angle;
        bool Calculate_and_save_to_file_fusleage();
        bool Calculate_and_save_to_file_rotor();
    protected:
        Vector3D const Transform_to_global_coords(Vector3D const & vec);
    public:
        bool drone_go_up(double altitude, PzG::LaczeDoGNUPlota & Link);
        bool drone_go_forward(double distance, PzG::LaczeDoGNUPlota & Link);
        bool Calculate_and_save_to_file_drone();
};