#include "Hexagonal_prism.hh"

Hexagonal_prism::Hexagonal_prism(){
    double values[3] = {8,8,2};
    Vector3D rotor_scale(values);
    udpate_scale(rotor_scale);

    double v_Apx1[3]={0.5,0,-0.5},v_Apx2[3]={0.25,0.433,-0.5},v_Apx3[3]={-0.25,0.433,-0.5},v_Apx4[3]={-0.5,0,-0.5},
           v_Apx5[3]={-0.25,-0.433,-0.5},v_Apx6[3]={0.25,-0.433,-0.5},v_Apx7[3]={0.5,0,0.5},v_Apx8[3]={0.25,0.433,0.5},
           v_Apx9[3]={-0.25,0.433,0.5},v_Apx10[3]={-0.5,0,0.5},v_Apx11[3]={-0.25,-0.433,0.5},v_Apx12[3]={0.25,-0.433,0.5};
    Vector3D Apx1(v_Apx1),Apx2(v_Apx2),Apx3(v_Apx3),Apx4(v_Apx4),Apx5(v_Apx5),Apx6(v_Apx6),
             Apx7(v_Apx7),Apx8(v_Apx8),Apx9(v_Apx9),Apx10(v_Apx10),Apx11(v_Apx11),Apx12(v_Apx12);
    
    Local_corners[0] = Apx1;
    Local_corners[1] = Apx2;
    Local_corners[2] = Apx3;
    Local_corners[3] = Apx4;
    Local_corners[4] = Apx5;
    Local_corners[5] = Apx6;
    Local_corners[6] = Apx7;
    Local_corners[7] = Apx8;
    Local_corners[8] = Apx9;
    Local_corners[9] = Apx10;
    Local_corners[10] = Apx11;
    Local_corners[11] = Apx12;

    Roration_angle_Zaxis = 0;
}

void Hexagonal_prism::Transform_to_global_coords(Vector3D const & vec, Vector3D const & position_of_drone,double const & drone_angle){
    center_of_prism = position_of_drone;
    Matrix3x3 Rotation_matrix = Fill_matrix_OZ(drone_angle), Animation_matrix = Fill_matrix_OZ(Roration_angle_Zaxis);
    for (unsigned int i=0; i < 12; ++i)
        Global_corners [i] = Rotation_matrix * (Animation_matrix * (Local_corners[i] * Scale) + vec) + center_of_prism ;
}

const Vector3D & Hexagonal_prism::operator [] (int index) const {
    if (index < 0 || index >= 12) {
        throw std::runtime_error("Bledna wartosc indeksu wierzcholka graniastoslupa");
    } 
    return Global_corners[index];
}

/*!                                                                                                 
    \param[in]  index - index wierzcholka globalnego prostopadloscianu.                                             
                                                                  
    \return Wartosc wierzcholka globalnego prostopadloscianu w danym miejscu tablicy.                           
*/

 Vector3D & Hexagonal_prism::operator[](int index) {
    if (index < 0 || index >= 12) {
        throw std::runtime_error("Bledna wartosc indeksu wierzcholka graniastoslupa");
    } 
    return const_cast <Vector3D &> (const_cast <const Hexagonal_prism *> (this)->operator[](index));
}


 void Hexagonal_prism::update_angle(double additional_angle){
    Roration_angle_Zaxis += additional_angle;
    if(Roration_angle_Zaxis >=360)
        Roration_angle_Zaxis -=360;
 }