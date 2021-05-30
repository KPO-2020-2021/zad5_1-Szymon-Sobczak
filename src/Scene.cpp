#include "Scene.hh"

Scene::Scene(){
    nbr_of_active_drone = 1;
    double val_ctr1[3]={100,100,3}, val_ctr2[3]={50,50,3};
    Vector3D center_of_drone1(val_ctr1),center_of_drone2(val_ctr2);
    Drone drone_1(center_of_drone1), drone_2(center_of_drone2); 
    Drones.push_back(drone_1);
    Drones.at(0).set_ID(1);

    Drones.push_back(drone_2);
    Drones.at(1).set_ID(2);
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