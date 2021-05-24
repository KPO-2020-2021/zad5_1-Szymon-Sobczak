#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"

class Geometrical_solid{
    private:
        std::string Name_of_file_global;
        std::string Name_of_file_prattern;
    public:
        Vector3D Scale;
        std::string const & Get_Name_of_file_global (); 
        std::string const & Get_Name_of_file_pattern (); 
        Vector3D const scale(Vector3D const & pattern_vector);
};