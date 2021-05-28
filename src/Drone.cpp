#include "Drone.hh"

Drone::Drone(Vector3D location){
    drone_location = location;
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

void Drone::Calculate_and_save_to_file_drone(){
    Calculate_and_save_to_file_fusleage();
    std::cout<< drone_location << std::endl;
}


void Drone::drone_go_verical(double altitude, PzG::LaczeDoGNUPlota & Link){
    drone_location[2]+=altitude;
    Calculate_and_save_to_file_drone();
    Link.Rysuj();
}
