#pragma once 

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <unistd.h>
#include "matrix3x3.hh"
#include "vector3D.hh"
#include "Cuboid.hh"
#include "Hexagonal_prism.hh"
#include "lacze_do_gnuplota.hh"

/*!
    \file
        \brief  Definicja klasy Drone.

    Prototypy funkcji i metod klasy Drone.
*/

/*!
    \brief Klasa modelujaca w programie pojecie drona.
    Dron jest reprezentowany przez prostopadloscian- kadlub, cztery graniastoslupy prawidlowe szesciokatne- rotory oraz dodatkowy element reprezentujacy kamere przednia.

    Klasa posiada:
        - prywatne pole "drone_location" bedace wektorem, opisuje ono wektorowo pozycje globalnego srodka drona.
        - prywatne pole "rotors" bedace tablica czteroelementowa obiektow Hexagonal_prism, reprezentuje ono zbior rotorow drona.
        - prywatne pole "fuselage" bedace typu Cuboid, reprezentuje ono kadlub drona.
        - prywatne pole "front_camera" bedace typu Hexagonal_prism, reprezentuje ono dodatkowa bryle wyrozniajaca front drona.
        - prywatne pole "Orientation_angle" opisujace obrot drona w osi Z. 
        - prywatne pole "Drone_ID" opisujace numer identyfikacyjny drona. 
        - publiczny konstruktor z parametrm, ktory okresla pozycje poczatkowa drona.
    
    Klasa posiada prywatne metody pozwalajace na:
        - Obliczenie i zapisanie danych o wierzcholkach globalnych kadluba do pliku.
        - Obliczenie i zapisanie danych o wierzcholkach globalnych pojedynczego rotora do pliku.
        - Obliczenie i zapisanie danych o wierzcholkach globalnych dodatkowego obiektu wyroznijacego front drona do pliku.

    Klasa posiada publiczne metody pozwalajace na:
        - Transformacje prostopadlosiacnu z ukladu lokalnego do ukladu globalnego, przechodzac przez uklad graniastoslupa prawidlowego szesciokatnego.
        - Aktualizajce kata obrotu graniastoslupa prawidlowego szesciokatnego.
        - Przeciazenie operatorow indeksujacych, umozliwajacych odczytywanie i zmiane wartosci reprezentujacych wierzcholki graniastoslupa prawidlowego szesciokatnego w ukladzie globalnym.   
        - Pobranie aktualngo kata obrotu graniastoslupa prawidlowego szesciokatnego.                                                        
*/

class Drone{
    private:
        Vector3D drone_location;

        Hexagonal_prism rotors[4];

        Hexagonal_prism front_camera; 

        Cuboid fuselage;

        double Orientation_angle;

        unsigned int Drone_ID;

        void Calculate_and_save_to_file_fuselage();

        void Calculate_and_save_to_file_rotor(unsigned int index, Vector3D const & Trasnlation);

        void Calculate_and_save_to_file_front_camera(Vector3D const & Trasnlation);

    public:
        Drone(Vector3D const & location);

        void set_ID(unsigned int const & new_ID);

        Vector3D const get_drone_location() const;        

        void plan_path(double const & angle, double const & distance, PzG::LaczeDoGNUPlota & Link);

        void plan_reacon(PzG::LaczeDoGNUPlota & Link);

        void update_angle(double const &  additional_angle);

        void go_verical(double const &  altitude, PzG::LaczeDoGNUPlota & Link);

        void rotate_drone(double const &  user_angle, PzG::LaczeDoGNUPlota & Link);

        void go_horizontal(double const & distance, double const & user_angle, PzG::LaczeDoGNUPlota & Link);

        void Calculate_and_save_to_file_drone();

};