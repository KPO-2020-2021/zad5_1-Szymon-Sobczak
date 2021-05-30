#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <unistd.h>
#include "matrix3x3.hh"
#include "vector3D.hh"
#include "Cuboid.hh"
#include "Hexagonal_prism.hh"
#include "lacze_do_gnuplota.hh"

class Drone{
    private:
        Vector3D drone_location;

        Hexagonal_prism rotors[4];

        Cuboid2 fuselage;

        double Orientation_angle;

        unsigned int Drone_ID;

        void Calculate_and_save_to_file_fuselage();

        void Calculate_and_save_to_file_rotor(unsigned int index, Vector3D Trasnlation);

    public:
        Drone(Vector3D location);

        void set_ID( unsigned int new_ID);

        Vector3D  get_drone_location();        

        void plan_path(double angle, double distance, PzG::LaczeDoGNUPlota & Link);

        void drone_go_verical(double altitude, PzG::LaczeDoGNUPlota & Link);

        void drone_go_horizontal(double distance, PzG::LaczeDoGNUPlota & Link);

        void Calculate_and_save_to_file_drone();
};