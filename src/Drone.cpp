#include "Drone.hh"

Drone::Drone(Vector3D location){
    drone_location = location;
    Drone_ID = 0;
    Orientation_angle = 0;
}

void Drone::Calculate_and_save_to_file_fuselage(){

    fuselage.Transform_to_global_coords(drone_location, Orientation_angle);

    std::ofstream  FileStrm;
    Vector3D P1,P2, temp_vec[]={fuselage[0],fuselage[7],fuselage[2],fuselage[5]};
    
    std::string name_of_file = fuselage.Get_Name_of_file_global() + "No_" + std::to_string(Drone_ID) + "_fuselage.dat";
    
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
    
    rotors[index].Transform_to_global_coords(Trasnlation, drone_location, Orientation_angle);

    std::ofstream  FileStrm;
    Vector3D P1,P2;
    
    std::string name_of_file = rotors[index].Get_Name_of_file_global() + "No_" + std::to_string(Drone_ID) + "_rotor" + std::to_string(index) + ".dat";

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
    double val_rot1[3]={5,4,4},val_rot2[3]={-5,4,4},val_rot3[3]={5,-4,4},val_rot4[3]={-5,-4,4};
    Vector3D vec_rot1(val_rot1), vec_rot2(val_rot2), vec_rot3(val_rot3), vec_rot4(val_rot4);
    
    Calculate_and_save_to_file_fuselage();

    Calculate_and_save_to_file_rotor(0,vec_rot1);
    Calculate_and_save_to_file_rotor(1,vec_rot2);
    Calculate_and_save_to_file_rotor(2,vec_rot3);
    Calculate_and_save_to_file_rotor(3,vec_rot4);
}

void Drone::drone_go_verical(double altitude, PzG::LaczeDoGNUPlota & Link){
    for (int i = 0; i < FRAMES; ++i){
        drone_location[2]+=altitude/FRAMES;
        Calculate_and_save_to_file_drone();
        Link.Rysuj();
        usleep(20000);
    }
    Link.Rysuj();
}

void Drone::drone_go_horizontal(double distance, PzG::LaczeDoGNUPlota & Link){
    double unit_values[3]={1,0,0};
    Vector3D unit_vector(unit_values);

    std::cout << Orientation_angle << std::endl;

    double rotation = Orientation_angle - fuselage.get_angle();
    
    for (int i = 0; i < FRAMES; ++i){
        fuselage.update_angle(rotation/FRAMES); 
        Calculate_and_save_to_file_drone();
        usleep(20000);
        Link.Rysuj();
    } 

    Matrix3x3 Rotation_matrix = Fill_matrix_OZ(Orientation_angle);
    
    unit_vector = Rotation_matrix * unit_vector;
    
    Vector3D translation_vector = (unit_vector*distance)/FRAMES;
    
    for (int i = 0; i < FRAMES; ++i){
        drone_location = drone_location + translation_vector;
        Calculate_and_save_to_file_drone();
        Link.Rysuj();
        usleep(20000);
    }
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


void Drone::plan_path(double angle, double distance, PzG::LaczeDoGNUPlota & Link){

    std::ofstream  FileStrm;
    std::string name_of_file = "../datasets/path.dat";
    Vector3D path_point_location = drone_location;
     
    Orientation_angle += angle;

    FileStrm.open(name_of_file);
    if (!FileStrm.is_open()){
      throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
    }

    FileStrm << path_point_location << std::endl;

    path_point_location[2] += ALTITUDE; 

    FileStrm << path_point_location << std::endl;

    double unit_values[3]={1,0,0};
    Vector3D unit_vector(unit_values);
    Matrix3x3 Rotation_matrix = Fill_matrix_OZ(Orientation_angle);
    unit_vector = Rotation_matrix * unit_vector;
    path_point_location = path_point_location + (unit_vector*distance);

    FileStrm << path_point_location << std::endl;
   
    path_point_location[2] -= ALTITUDE; 

    FileStrm << path_point_location << std::endl;

    Link.Rysuj();

    FileStrm.close();
} 

void Drone::set_ID(unsigned int new_ID){
    Drone_ID = new_ID;
}


Vector3D  Drone::get_drone_location(){
    return drone_location;
} 