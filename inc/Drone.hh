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

        Cuboid fuselage;

        double Orientation_angle;

        unsigned int Drone_ID;

        void Calculate_and_save_to_file_fuselage();

        void Calculate_and_save_to_file_rotor(unsigned int index, Vector3D const & Trasnlation);

    public:
        Drone(Vector3D const & location);

        void set_ID(unsigned int const & new_ID);

        Vector3D const get_drone_location() const;        

        void plan_path(double const & angle, double const & distance, PzG::LaczeDoGNUPlota & Link);

        void plan_reacon(PzG::LaczeDoGNUPlota & Link);

        void update_angle(double const &  additional_angle);

        void go_verical(double const &  altitude, PzG::LaczeDoGNUPlota & Link);

        void rotate_drone(double const &  user_angle,PzG::LaczeDoGNUPlota & Link);

        void go_horizontal(double const & distance, double const & user_angle, PzG::LaczeDoGNUPlota & Link);

        void Calculate_and_save_to_file_drone();

};