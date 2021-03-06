#include "Geometrical_solid.hh"

/*!
    \file
        \brief Definicje metod klasy Geometrical_solid

    Zawiera definicje funkcji i metod klasy Geometrical_solid.
*/

/*!
    Domyślny konstruktor obiektu typu Cuboid. 
                                                                                                                                              
    \return Bryla geometryczna o domyslnej nazwie.        
 */

Geometrical_solid::Geometrical_solid(){
    Name_of_file_global = "../datasets/Glb_crd_";
}


/*!
    Metoda zmienia skale bryly geometrycznej, czyli to jakie dlugosci bokow bedzie posiadala bryla. 
    
    \param[in] new_scale - nowa skala bryly geometrycznej.
*/

void Geometrical_solid::update_scale(Vector3D const & new_scale){
    Scale = new_scale;
}

/*!
    Metdoa pozwala na pobranie informacji o skali danej bryly geometrycznej. 

    \return Aktualna skale bryly geometrycznej, obiekt typu Vector3D.
*/

Vector3D Geometrical_solid::get_scale() const{
    return Scale;
}

/*!
    Metoda pozwala na pobranie infromacji o nazwie danej bryly geometrycznej. 

    \return Aktualna nazwe bryly geometrycznej, obiekt typu std::string.
*/

std::string const & Geometrical_solid::Get_Name_of_file_global (){
    return Name_of_file_global;
}



































