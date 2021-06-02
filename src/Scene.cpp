#include "Scene.hh"

Scene::Scene(PzG::LaczeDoGNUPlota & Link){
    nbr_of_active_drone = 1;
    double val_ctr1[3]={100,100,3}, val_ctr2[3]={50,50,3};
    Vector3D center_of_drone1(val_ctr1),center_of_drone2(val_ctr2);
    Drone drone_1(center_of_drone1), drone_2(center_of_drone2); 
    
    Drones.push_back(drone_1);
    Drones.at(0).set_ID(1);

    Drones.push_back(drone_2);
    Drones.at(1).set_ID(2);

    Link.ZmienTrybRys(PzG::TR_3D); /* Ustawienie trybu rysowania w gnuplot na 3D. */
    Link.UstawZakresY(0,200);      /* Uwstawienie zakresu osi OX, OY i OZ w Gnuplot */ 
    Link.UstawZakresX(0,200);
    Link.UstawZakresZ(0,150); 

    PzG::InfoPlikuDoRysowania *File_info_fsd1 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_1_fuselage.dat");
    File_info_fsd1 -> ZmienKolor(1);
    File_info_fsd1 -> ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_bed = & Link.DodajNazwePliku("../datasets/bed.dat");
    File_info_bed -> ZmienKolor(4);
    File_info_bed -> ZmienSzerokosc(2); 

    PzG::InfoPlikuDoRysowania *File_info_rot0_no1 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_1_rotor0.dat");
    File_info_rot0_no1->ZmienKolor(1);
    File_info_rot0_no1->ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_rot1_no1 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_1_rotor1.dat");
    File_info_rot1_no1->ZmienKolor(1);
    File_info_rot1_no1->ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_rot2_no1 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_1_rotor2.dat");
    File_info_rot2_no1->ZmienKolor(1);
    File_info_rot2_no1->ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_rot3_no1 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_1_rotor3.dat");
    File_info_rot3_no1->ZmienKolor(1);
    File_info_rot3_no1->ZmienSzerokosc(2); 

    PzG::InfoPlikuDoRysowania *File_info_fsd2 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_2_fuselage.dat");
    File_info_fsd2->ZmienKolor(2);
    File_info_fsd2->ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_rot0_no2 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_2_rotor0.dat");
    File_info_rot0_no2->ZmienKolor(2);
    File_info_rot0_no2->ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_rot1_no2 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_2_rotor1.dat");
    File_info_rot1_no2->ZmienKolor(2);
    File_info_rot1_no2->ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_rot2_no2 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_2_rotor2.dat");
    File_info_rot2_no2->ZmienKolor(2);
    File_info_rot2_no2->ZmienSzerokosc(2);

    PzG::InfoPlikuDoRysowania *File_info_rot3_no2 = & Link.DodajNazwePliku("../datasets/Global_cords_file_No_2_rotor3.dat");
    File_info_rot3_no2->ZmienKolor(2);
    File_info_rot3_no2->ZmienSzerokosc(2);  
}

void Scene::choose_drone(unsigned int active_drone){
    if(active_drone > Drones.size() || active_drone == 0)
      throw std::invalid_argument(":/ Podano bledny numer drona ");
    else    
        nbr_of_active_drone = active_drone;
}

Drone const & Scene::get_active_drone(){
    return Drones.at(nbr_of_active_drone-1);
}

Drone & Scene::use_active_drone(){
    return Drones.at(nbr_of_active_drone-1);
}