#include "Drone.hh"

Drone::Drone(Vector3D location){
    drone_location = location;
    Orientation_angle = 60;
}

void Drone::Calculate_and_save_to_file_fusleage(){
    fuselage.Transform_to_global_coords(drone_location);

    std::ofstream  FileStrm;
    Vector3D P1,P2, temp_vec[]={fuselage[0],fuselage[7],fuselage[2],fuselage[5]};
    
    std::string name_of_file = fuselage.Get_Name_of_file_global();
    name_of_file += "fusledge";
    FileStrm.open(name_of_file);
    if (!FileStrm.is_open()){
      throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
    }
    
    P1 = (temp_vec[0] + temp_vec[1])/2;
    P2 = (temp_vec[2] + temp_vec[3])/2;

    FileStrm << P1 << std::endl
             << fuselage[6] << std::endl
             << fuselage[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;

    FileStrm << P1 << std::endl
             << fuselage[7] << std::endl
             << fuselage[5] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << fuselage[1] << std::endl
             << fuselage[3] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << fuselage[0] << std::endl
             << fuselage[2] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm << P1 << std::endl
             << fuselage[6] << std::endl
             << fuselage[4] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 

    FileStrm.close();
}


/* Opcja dodajaca do sceny nowy prostopadloscian */
    //                 std::cout << "Podaj wspolrzedne punktow, na ktorych zostanie rozpiety nowy prostopadloscian: " << std::endl; 
    //                 std::cout << "Podaj wspolrzedne x y z pierwszego punktu: "; 
    //                 std::cin >> ctr_of_new_cub;
    //                 std::cout << "Podaj wartosci dlugosci o jakie punkt ma zostac rozsuniety na osiach OX, OY, OZ " << std::endl; 
    //                 std::cin >> tr_X >> tr_Y >> tr_Z;
    //                 if (std::cin.fail() || (tr_X == 0 && tr_Y == 0 && tr_Z == 0)){
    //                     std::cerr << ":( Niepoprawne oznaczenie dlugosci, dodawanie przerwane." << std::endl; 
    //                     std::cin.clear();
    //                     std::cin.ignore(10000,'\n');   
    //                     break;
    //                 }

    //                 name_of_new_file = "../datasets/cuboid.dat";
    //                 name_of_new_file.insert(18, std::to_string(Scenery.how_many_cuboids() + 1));
    //                 adresses_of_files.push_back(name_of_new_file);
    //                 Link.DodajNazwePliku(name_of_new_file.c_str(),PzG::RR_Ciagly, 2);

    //                 Scenery.Add_cuboid(ctr_of_new_cub,tr_X,tr_Y,tr_Z);

    //                 Scenery[Scenery.how_many_cuboids()-1].Write_cub_to_file(name_of_new_file.c_str());

    //                 Link.Rysuj();
    //             break;

void Drone::Calculate_and_save_to_file_rotor(unsigned int index, Vector3D Trasnlation){
    
    rotors[index].Transform_to_global_coords(Trasnlation,drone_location,Orientation_angle);

    std::ofstream  FileStrm;
    Vector3D P1,P2;
    
    std::string name_of_file = rotors[index].Get_Name_of_file_global();
    name_of_file += "rotor_";
    name_of_file += std::to_string(index);
    FileStrm.open(name_of_file);
    if (!FileStrm.is_open()){
      throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
    }
    
    P1 = (rotors[index][0] + rotors[index][3])/2;
    P2 = (rotors[index][6] + rotors[index][9])/2;

    FileStrm << P1 << std::endl
             << rotors[index][0] << std::endl
             << rotors[index][6] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;

    FileStrm << P1 << std::endl
             << rotors[index][1] << std::endl
             << rotors[index][7] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 
     
    FileStrm << P1 << std::endl
             << rotors[index][2] << std::endl
             << rotors[index][8] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;       
      
    FileStrm << P1 << std::endl
             << rotors[index][3] << std::endl
             << rotors[index][9] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;       
      
    FileStrm << P1 << std::endl
             << rotors[index][4] << std::endl
             << rotors[index][10] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;                

    FileStrm << P1 << std::endl
             << rotors[index][5] << std::endl
             << rotors[index][11] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;     

    FileStrm << P1 << std::endl
             << rotors[index][0] << std::endl
             << rotors[index][6] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;
       
    FileStrm.close();
}

void Drone::Calculate_and_save_to_file_drone(){
    double val_rot1[3]={5,4,6},val_rot2[3]={-5,4,6},val_rot3[3]={5,-4,6},val_rot4[3]={-5,-4,6};
    Vector3D vec_rot1(val_rot1),vec_rot2(val_rot2),vec_rot3(val_rot3),vec_rot4(val_rot4);
    
    Calculate_and_save_to_file_fusleage();
    Calculate_and_save_to_file_rotor(0,vec_rot1);
    Calculate_and_save_to_file_rotor(1,vec_rot2);
    Calculate_and_save_to_file_rotor(2,vec_rot3);
    Calculate_and_save_to_file_rotor(3,vec_rot4);
}

void Drone::drone_go_verical(double altitude, PzG::LaczeDoGNUPlota & Link){
    std::cout << fuselage << std::endl; 
    for (int i = 0; i < 100; ++i){
        drone_location[2]+=altitude/100;
        Calculate_and_save_to_file_drone();
        Link.Rysuj();
        usleep(20000);
    }
    std::cout << fuselage << std::endl; 
    Link.Rysuj();
}

std::ostream & operator << (std::ostream & Out, const Cuboid2 & Rc){
    for (int i = 0; i < CORNERS; i++){
        Out << Rc[i] << std::endl;
        if(i%2==1)
            Out << std::endl;
    }
    return Out;
}
