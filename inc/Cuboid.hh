#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "vector3D.hh"
#include "matrix3x3.hh"
#include "Geometrical_solid.hh"

class Cuboid: public Geometrical_solid{
    private:
        Vector3D center_of_cuboid;

        Vector3D Local_corners[8]; 

        Vector3D Global_corners[8]; 

        double Roration_angle_Zaxis;

    public:
        Cuboid();
        
        void Transform_to_global_coords(Vector3D const & vec);

        void update_angleZ(double const & additional_angle);
        
        /*! \brief Przeciazenie operatora indeksujacego */
        const Vector3D & operator [] (int index) const;         
        
        /*! \brief Przeciazenie operatora indeksujacego */
        Vector3D & operator [] (int index);

        double get_angle() const;
};

/*! \brief Przeciazenie operatora << sluzace wyswietlaniu wartosci prostopadloscianu */ 
std::ostream & operator << (std::ostream & Strm, const Cuboid & Rc);    
 