#include "Geometrical_solid.hh"

Geometrical_solid::Geometrical_solid(){
    Name_of_file_global = "../datasets/Glb_crd_";
}

void Geometrical_solid::update_scale(Vector3D const & new_scale){
    Scale = new_scale;
}

Vector3D Geometrical_solid::get_scale() const{
    return Scale;
}

std::string const & Geometrical_solid::Get_Name_of_file_global (){
    return Name_of_file_global;
}



































