#include "../tests/doctest/doctest.h"
#include "Drone.hh"

TEST_CASE("Test konstruktora klasy z parametrem oraz metod do pozyskiwania wartosci wektora polozenia drona oraz kata orientacji drona."){
    double val[3]={100,100,3};
    Vector3D center(val);
    Drone Example(center);

    CHECK((Example.get_drone_location()[0] ==100 && Example.get_drone_location()[1] == 100 && Example.get_drone_location()[2] == 3));    
}