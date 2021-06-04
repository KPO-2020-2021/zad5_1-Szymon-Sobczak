#include "Drone.hh"

/*!
    \file
        \brief Definicje metod klasy Drone.

    Zawiera definicje metod klasy Drone.
*/

/*!
    Konstruktor z parametrem obiektu typu Drone. 
    Tworzy nieobroconego drona w podanym punkcie globalnym sceny.
    Nadaje dronowi domyslne ID.  

    \param [in] location - wektor okreslajacy poczatkowe polozenie srodka kadluba drona w ukladzie globalnym sceny. 

    \return Drona o srodku w ukladzie globalnym w punkcie, nieobroconego.        
*/

Drone::Drone(Vector3D const & location){
    drone_location = location;
    Drone_ID = 0;
    Orientation_angle = 0;
}

/*!
    Metoda zapisuje do pliku, o wygenerowanej automatycznie nazwie, dane o polozeniu wierzcholkow globalnych kadluba- prostopadloscianu, po uprzednim wyliczeniu ich. 
    Zapis odbywa sie w sposob umozliwajacy wyswietlenie wszystkich scian kadluba w Gnuplot.   
*/

void Drone::Calculate_and_save_to_file_fuselage(){
    fuselage.Transform_to_global_coords(drone_location);

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

/*!
    Metoda zapisuje do pliku, o wygenerowanej automatycznie nazwie, dane o polozeniu wierzcholkow globalnych kamery przedniej- graniostoslupa, po uprzednim wyliczeniu ich. 
    Zapis odbywa sie w sposob umozliwajacy wyswietlenie wszystkich scian graniostoslupa w Gnuplot.   
*/

void Drone::Calculate_and_save_to_file_front_camera(Vector3D const & Trasnlation){
    double camera_scale_scale[3]={3,8,2};
    Vector3D camera_scale(camera_scale_scale);
    front_camera.update_scale(camera_scale);

    front_camera.Transform_to_global_coords(Trasnlation, drone_location, fuselage.get_angle());

    std::ofstream  FileStrm;
    Vector3D P1,P2;
    
    std::string name_of_file = front_camera.Get_Name_of_file_global() + "No_" + std::to_string(Drone_ID) + "_front_camera.dat";

    FileStrm.open(name_of_file);
    if (!FileStrm.is_open()){
      throw std::runtime_error(":(  Operacja otwarcia pliku do zapisu nie powiodla sie.");
    }
    
    P1 = (front_camera[0] + front_camera[3])/2;
    P2 = (front_camera[6] + front_camera[9])/2;

    FileStrm << P1 << std::endl
             << front_camera[0] << std::endl
             << front_camera[6] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;

    FileStrm << P1 << std::endl
             << front_camera[1] << std::endl
             << front_camera[7] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl; 
     
    FileStrm << P1 << std::endl
             << front_camera[2] << std::endl
             << front_camera[8] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;       
      
    FileStrm << P1 << std::endl
             << front_camera[3] << std::endl
             << front_camera[9] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;       
      
    FileStrm << P1 << std::endl
             << front_camera[4] << std::endl
             << front_camera[10] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;                

    FileStrm << P1 << std::endl
             << front_camera[5] << std::endl
             << front_camera[11] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;     

    FileStrm << P1 << std::endl
             << front_camera[0] << std::endl
             << front_camera[6] << std::endl
             << P2 << std::endl
             << '#' << std::endl
             << std::endl;
       
    FileStrm.close();
}


/*!
    Metoda zapisuje do pliku, o wygenerowanej automatycznie nazwie, dane o polozeniu wierzcholkow globalnych rotora- graniostoslupa froemnego szesciokatnego, po uprzednim wyliczeniu ich. 
    Zapis odbywa sie w sposob umozliwajacy wyswietlenie wszystkich scian rotora w Gnuplot.   
*/

void Drone::Calculate_and_save_to_file_rotor(unsigned int index, Vector3D const & Trasnlation){
    
    rotors[index].Transform_to_global_coords(Trasnlation, drone_location, fuselage.get_angle());

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

/*!
    Metoda publiczna pozwalajaca w polaczony sposob zapisac wszystkie elementy drona do plikow. 
    Metoda wyznacza wektory przesuniecia rotorow i kamery w ukladzie prostopadloscianu.
*/

void Drone::Calculate_and_save_to_file_drone(){
    double val_rot1[3]={5,4,4},val_rot2[3]={-5,4,4},val_rot3[3]={5,-4,4},val_rot4[3]={-5,-4,4},val_cam[3]={5,0,0};
    Vector3D vec_rot1(val_rot1), vec_rot2(val_rot2), vec_rot3(val_rot3), vec_rot4(val_rot4),vec_cam(val_cam);
    
    Calculate_and_save_to_file_fuselage();

    Calculate_and_save_to_file_front_camera(vec_cam);

    Calculate_and_save_to_file_rotor(0,vec_rot1);
    Calculate_and_save_to_file_rotor(1,vec_rot2);
    Calculate_and_save_to_file_rotor(2,vec_rot3);
    Calculate_and_save_to_file_rotor(3,vec_rot4);
}

/*!
    Metoda sluzaca do poruszania sie dornem w pionie, w gore i w dol.
    Metoda realizuje przelot w formie animacji, nasladujacej prawdziwa dynamike rotorow.

    \param [in] altitude - dlugosc na jaka ma sie wzniesc / z jakiej ma sie opuscic dron.
    \param [in] Link - lacze do Gnuplota.
*/

void Drone::go_verical(double const & altitude, PzG::LaczeDoGNUPlota & Link){
    for (int i = 0; i < FRAMES; ++i){
        if (altitude >= 0){
        rotors[0].update_angle(-10);
        rotors[1].update_angle(10);
        rotors[2].update_angle(10);
        rotors[3].update_angle(-10);
        }
        else{
            rotors[0].update_angle(-3);
            rotors[1].update_angle(3);
            rotors[2].update_angle(3);
            rotors[3].update_angle(-3);
        }
        drone_location[2]+=altitude/FRAMES;
        Calculate_and_save_to_file_drone();
        Link.Rysuj();
        usleep(20000);
    }
    Link.Rysuj();
}


/*!
    Metoda sluzaca do obracania w osi Z dornem o podany kat.
    Metoda realizuje obrot w formie animacji, nasladujacej prawdziwa dynamike rotorow.

    \param [in] user_angle - kat o jaki ma sie obrocic dron.
    \param [in] Link - lacze do Gnuplota.
*/

void Drone::rotate_drone(double const & user_angle, PzG::LaczeDoGNUPlota & Link){
    for (int i = 0; i < FRAMES; ++i){
        fuselage.update_angleZ(user_angle/FRAMES); 
        if((user_angle == 0)){
            rotors[0].update_angle(-5);
            rotors[1].update_angle(5);
            rotors[2].update_angle(5);
            rotors[3].update_angle(-5);
        }
        else if (user_angle > 0){
            rotors[0].update_angle(-10);
            rotors[1].update_angle(3);
            rotors[2].update_angle(3);
            rotors[3].update_angle(-10);
        }
        else{
            rotors[0].update_angle(-3);
            rotors[1].update_angle(10);
            rotors[2].update_angle(10);
            rotors[3].update_angle(-3);
        }
        Calculate_and_save_to_file_drone();
        usleep(20000);
        Link.Rysuj();
    } 
}

/*!
    Metoda sluzaca do poruszania sie dornem w poziomie.
    Metoda realizuje przelot w formie animacji, nasladujacej prawdziwa dynamike rotorow.

    \param [in] distance - odleglosc na jaka ma polecec dron.
    \param [in] user_angle - Kat o jaki ma obrocic sie dron.
    \param [in] Link - lacze do Gnuplota.
*/

void Drone::go_horizontal(double const & distance, double const & user_angle, PzG::LaczeDoGNUPlota & Link){
    double unit_values[3]={1,0,0};
    Vector3D unit_vector(unit_values);
    
    rotate_drone(user_angle,Link);
    
    Matrix3x3 Rotation_matrix = Fill_matrix_OZ(Orientation_angle);
    
    unit_vector = Rotation_matrix * unit_vector;
    
    Vector3D translation_vector = (unit_vector * distance) / FRAMES;
    
    for (int i = 0; i < FRAMES; ++i){
        drone_location = drone_location + translation_vector;
        rotors[0].update_angle(-5);
        rotors[1].update_angle(5);
        rotors[2].update_angle(5);
        rotors[3].update_angle(-5);
        Calculate_and_save_to_file_drone();
        Link.Rysuj();
        usleep(20000);
    }
    Link.Rysuj();
}

/*!
    Metoda sluzaca do wyznaczania linii reprezentujacej zaplanowany przelot drona.

    \param [in] distance - odleglosc na jaka ma polecec dron.
    \param [in] angle - Kat o jaki ma obrocic sie dron.
    \param [in] Link - lacze do Gnuplota.
*/

void Drone::plan_path(double const & angle, double const & distance, PzG::LaczeDoGNUPlota & Link){
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

/*!
    Metoda sluzaca do wyznaczania linii reprezentujacej przelot drona podczas predefiniowanego zwiadu.

    \param [in] Link - lacze do Gnuplota.
*/

void Drone::plan_reacon(PzG::LaczeDoGNUPlota & Link){
    std::ofstream  FileStrm;
    std::string name_of_file = "../datasets/path_reacon.dat";
    Vector3D path_point_location = drone_location;
     
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
    path_point_location = path_point_location + (unit_vector*REACON_RADIUS);
    FileStrm << path_point_location << std::endl;
   
    Rotation_matrix = Fill_matrix_OZ(112.5);
    unit_vector = Rotation_matrix * unit_vector;
    path_point_location = path_point_location + (unit_vector*REACON_RADIUS/sqrt((2+sqrt(2))/2));
    FileStrm << path_point_location << std::endl;
   
    for (unsigned int i = 0;i < 7 ; ++i){
        Rotation_matrix = Fill_matrix_OZ(45);
        unit_vector = Rotation_matrix * unit_vector;
        path_point_location = path_point_location + (unit_vector*REACON_RADIUS/sqrt((2+sqrt(2))/2));
        FileStrm << path_point_location << std::endl;
    }
   
    Rotation_matrix = Fill_matrix_OZ(112.5);
    unit_vector = Rotation_matrix * unit_vector;
    path_point_location = path_point_location + (unit_vector*REACON_RADIUS);
    FileStrm << path_point_location << std::endl;
   
    path_point_location[2] -= ALTITUDE; 
    FileStrm << path_point_location << std::endl;

    Link.Rysuj();

    FileStrm.close();
} 

/*!
    Metoda zmienia numer ID, potrzebny przy zapisie elementow drona do pliku.

    \param [in] new_ID - nowe ID drona.
*/

void Drone::set_ID(unsigned int const & new_ID){
    Drone_ID = new_ID;
}

/*!
    \return Vector3D aktualnego polozenia srodka kadluba drona w ukladzie globalnym sceny.
*/

Vector3D const Drone::get_drone_location() const{
    return drone_location;
} 

/*! 
    Zadany dodatkowy kat obrotu drona zostanie zsumowany z aktualnym katem obrotu drona.

    \param [in] additional_angle - dodtkowy kat, o ktory dron zostanie obrocony.
*/
void Drone::update_angle(double const & additional_angle){
     Orientation_angle += additional_angle;
}