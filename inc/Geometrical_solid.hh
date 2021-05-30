#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"

class Geometrical_solid{
    private:
        std::string Name_of_file_global;
    public:
        Vector3D Scale;
        Geometrical_solid();
        std::string const & Get_Name_of_file_global(); 
        void udpate_scale(Vector3D const & new_scale);
};