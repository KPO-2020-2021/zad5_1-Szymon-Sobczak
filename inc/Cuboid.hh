#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"
#include "matrix3x3.hh"
#include "Geometrical_solid.hh"

class Cuboid2: public Geometrical_solid{
    private:
        Vector3D center_of_cuboid;

        Vector3D Local_corners[8]; 

        Vector3D Global_corners[8]; 

        double Roration_angle_Zaxis;
    public:
        Cuboid2();
        void Transform_to_global_coords(Vector3D const & vec,double const & angle);

        /*! \brief Przeciazenie operatora indeksujacego */
        const Vector3D & operator [] (int index) const;         
        
        /*! \brief Przeciazenie operatora indeksujacego */
        Vector3D & operator [] (int index);

};


/*! \brief Przeciazenie operatora << sluzace wyswietlaniu wartosci prostopadloscianu */ 
std::ostream & operator << (std::ostream & Strm, const Cuboid2 & Rc);    
 