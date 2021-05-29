#include "Cuboid.hh"

Cuboid2::Cuboid2(){

    double values[3] = {10,8,6};
    Vector3D fusledge_scale(values);
    udpate_scale(fusledge_scale);

    double v_Apx1[3]={-0.5,0.5,-0.5},v_Apx2[3]={-0.5,-0.5,-0.5},v_Apx3[3]={0.5,0.5,-0.5},v_Apx4[3]={0.5,-0.5,-0.5},
           v_Apx5[3]={0.5,0.5,0.5},v_Apx6[3]={0.5,-0.5,0.5},v_Apx7[3]={-0.5,0.5,0.5},v_Apx8[3]={-0.5,-0.5,0.5};
    Vector3D Apx1(v_Apx1),Apx2(v_Apx2),Apx3(v_Apx3),Apx4(v_Apx4),Apx5(v_Apx5),Apx6(v_Apx6),Apx7(v_Apx7),Apx8(v_Apx8);
    
    Local_corners[0] = Apx1;
    Local_corners[1] = Apx2;
    Local_corners[2] = Apx3;
    Local_corners[3] = Apx4;
    Local_corners[4] = Apx5;
    Local_corners[5] = Apx6;
    Local_corners[6] = Apx7;
    Local_corners[7] = Apx8;

    Roration_angle_Zaxis = 0;
}

void Cuboid2::Transform_to_global_coords(Vector3D const & vec, double const & angle){
    center_of_cuboid = vec;
    Roration_angle_Zaxis = angle;
    Matrix3x3 Rotation_matrix = Fill_matrix_OZ(Roration_angle_Zaxis);
   // double values[3] = {0,0,0.5};
   // Vector3D lift(values);
    for (unsigned int i=0; i < 8; ++i)
        Global_corners [i] = Rotation_matrix * (Local_corners[i] * Scale) + center_of_cuboid;
}

const Vector3D & Cuboid2::operator [] (int index) const {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu wierzcholka prostopadloscianu");
    } 
    return Global_corners[index];
}

/*!                                                                                                 
    \param[in]  index - index wierzcholka globalnego prostopadloscianu.                                             
                                                                  
    \return Wartosc wierzcholka globalnego prostopadloscianu w danym miejscu tablicy.                           
*/

 Vector3D & Cuboid2::operator[](int index) {
    if (index < 0 || index >= CORNERS) {
        throw std::runtime_error("Bledna wartosc indeksu wierzcholka prostopadloscianu");
    } 
    return const_cast <Vector3D &> (const_cast <const Cuboid2 *> (this)->operator[](index));
}
