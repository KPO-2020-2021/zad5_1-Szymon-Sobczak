#include "Geometrical_solid.hh"

Geometrical_solid::Geometrical_solid(){
    Name_of_file_global = "../datasets/Global_cords_file_";
}

void Geometrical_solid::udpate_scale(Vector3D const & new_scale){
    Scale = new_scale;
}

std::string const & Geometrical_solid::Get_Name_of_file_global (){
    return Name_of_file_global;
}