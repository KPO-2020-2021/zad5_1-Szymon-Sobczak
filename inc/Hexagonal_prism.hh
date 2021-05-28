#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"
#include "matrix3x3.hh"
#include "Geometrical_solid.hh"

class Hexagonal_prism: public Geometrical_solid{
    private:
        Vector3D center_of_prism;

        Vector3D Local_corners[12]; 

        Vector3D Global_corners[12]; 

        double Roration_angle_Zaxis;
    public:
        Hexagonal_prism();
        
        void Transform_to_global_coords(Vector3D const & vec, Vector3D const & position_of_drone,double const & drone_angle);

        /*! \brief Przeciazenie operatora indeksujacego */
        const Vector3D & operator [] (int index) const;         
        
        /*! \brief Przeciazenie operatora indeksujacego */
        Vector3D & operator [] (int index);
};