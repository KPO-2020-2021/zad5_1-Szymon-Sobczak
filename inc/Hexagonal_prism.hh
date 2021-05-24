#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"
#include "Geometrical_solid.hh"

class Hexagonal_prism: public Geometrical_solid{
    private:
        Vector3D location;
        double Roration_angle_Zaxis;
    public:
        Vector3D const Transform_to_global_coords(Vector3D const & vec);
};