/* Executables must have the following defined if the library contains
doctest definitions. For builds with this disabled, e.g. code shipped to
users, this can be left out. */

/*!
    \file
        \brief Plik zawierajacy "main" programu.
*/

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include "exampleConfig.h"
#include "vector.hh"
#include "matrix.hh"
#include "vector3D.hh"
#include "matrix3x3.hh"
#include "vector.hh"
#include "Drone.hh"
#include "Scene.hh"
#include "../inc/lacze_do_gnuplota.hh"

/*! \brief Glowna funkcja programu.*/

int main(){
   char Option; /* Inicjalizacja zmiennych tymczasowych */
   double user_angle=0,distance = 0;
   unsigned int nbr_of_act_drone=1;
   PzG::LaczeDoGNUPlota Link; /* Zmienna potrzebna do wizualizacji rysunku sceny*/
   Scene Scenery(Link); /* Inicjalizacja sceny */

   try{
      /* Zapis i wyswietlenie stanu poczatkowego dronow */
      Scenery.use_active_drone().Calculate_and_save_to_file_drone();
      Scenery.choose_drone(2);

      Scenery.use_active_drone().Calculate_and_save_to_file_drone();
      Scenery.choose_drone(1);
      
      Link.Rysuj();
      
      std::cout << "Menu wyboru opcji:" << std::endl
               << "\ta - wybierz aktywnego drona" << std::endl
               << "\tp - zadaj parametry przelotu" << std::endl
               << "\tm - wyswietl menu" << std::endl 
               << "\tz - wykonaj zwiad" << std::endl << std::endl
               << "\tk - koniec dzialania programu" << std::endl << std::endl;
        
      std::cout << "Laczna ilosc obiektow Wektor3D: " << Vector3D::get_counter_all_vectors() << std::endl;  
      std::cout << "Aktualna ilosc obiektow Wektor3D: " << Vector3D::get_counter_actual_vectors() << std::endl; 
        
      while (Option != 'k'){ /* Glowna petla menu, dzialajaca do czasu wybrania opcji zakonczenia- k */
         std::cout << "Twoj wybor? (m - menu) > ";
         std::cin >> Option;
         switch(Option){  
            case 'a': /* Opcja pozwalajaca na zmiane aktywnego drona */
               std::cout << "Obecnie aktywny dron: "<< nbr_of_act_drone << std::endl;
               std::cout << "Wybor aktywnego drona: "<< std::endl;
               
               Scenery.choose_drone(1);
               std::cout << "Dron 1. Polozenie x: " 
                         << std::fixed << std::setprecision(5) << Scenery.get_active_drone().get_drone_location()[0] << "\ty: " 
                         << std::fixed << std::setprecision(5) << Scenery.get_active_drone().get_drone_location()[1] << std::endl;
               
               Scenery.choose_drone(2);
               std::cout << "Dron 2. Polozenie x: "   
                         << std::fixed << std::setprecision(5) << Scenery.get_active_drone().get_drone_location()[0] << "\ty: " 
                         << std::fixed << std::setprecision(5) << Scenery.get_active_drone().get_drone_location()[1] << std::endl;
               while (true){
                  try{
                        std::cout << "Podaj numer drona, ktory ma byc aktywny: "<< std::endl;
                        std::cin >> nbr_of_act_drone;
                        if(std::cin.fail() || nbr_of_act_drone > 2)
                           throw std::invalid_argument(":/ Podano bledny numer prostopadloscianu ");
                        else{
                           Scenery.choose_drone(nbr_of_act_drone);
                           break;
                        }
                  }
                  catch (std::invalid_argument & f){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby, program poinformuje o tym i usunie blad ze strumienia */
                     std::cerr << f.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
                     std::cin.clear();
                     std::cin.ignore(10000,'\n');   
                  }
               }
               Link.Rysuj();
            break;
            
            case 'p': /* Opcja pozwalajaca na przemieszenie aktywnego drona w okreslonym kierunku o okreslona dlugosc */
               while (true){
                  try{
                        std::cout << "Podaj kat obrotu w stopniach > ";
                        std::cin >> user_angle;
                        if(std::cin.fail())
                           throw std::invalid_argument(":/ Podano bledna wartosc kata obrotu ");
                        std::cout << "Podaj dlugosc lotu > ";
                        std::cin >> distance;
                        if(std::cin.fail())
                           throw std::invalid_argument(":/ Podano bledna wartosc dlugosci lotu ");
                        else   
                           break;
                  }
                  catch (std::invalid_argument & f){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby, program poinformuje o tym i usunie blad ze strumienia */
                        std::cerr << f.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
                        std::cin.clear();
                        std::cin.ignore(10000,'\n');   
                  }
               }

               /* Wyrysowanie sciezki przelotu */
               std::cout << "Rysowanie zaplanowanej sciezki przelotu ... " << std::endl;
               Scenery.use_active_drone().plan_path(user_angle,distance,Link);
               Link.DodajNazwePliku("../datasets/path.dat");
               usleep(100000);
               
               /* Wykonanie sekwencji ruchow drona */
               std::cout << "Wznoszenie ... " << std::endl;    
               Scenery.use_active_drone().go_verical(ALTITUDE,Link);
               usleep(100000);
                  
               std::cout << "Przelot ... " << std::endl;    
               Scenery.use_active_drone().go_horizontal(distance,user_angle,Link);
               usleep(100000);
               
               std::cout << "Ladowanie ... " << std::endl;    
               Scenery.use_active_drone().go_verical(-ALTITUDE,Link);
               usleep(100000);

               std::cout << "Dron wyladowal ... " << std::endl; 
               
               Link.UsunNazwePliku("../datasets/path.dat");

               Link.Rysuj();
            break;
            
            case 'm': /* Opcja wyswietlajaca dostepne w menu opcje */  
               std::cout << "Menu wyboru opcji:" << std::endl
               << "\ta - wybierz aktywnego drona" << std::endl
               << "\tp - zadaj parametry przelotu" << std::endl
               << "\tm - wyswietl menu" << std::endl 
               << "\tz - wykonaj zwiad" << std::endl << std::endl
               << "\tk - koniec dzialania programu" << std::endl << std::endl;
            break;
               
            case 'k': /* Opcja konczaca program */
               std::cout << "Konczenie pracy programu ..." << std::endl;
            break;

            case 'z': /* Opcjaq pozwalajaca na wykonanie zwiadu, predefiniowanego ruchu po osmiokacie */
               
               std::cout << "Wykonywanie zwiadu ..." << std::endl;

               /* Wyrysowanie sciezki zwiadu */
               std::cout << "Rysowanie zaplanowanej sciezki przelotu ... " << std::endl;
               Scenery.use_active_drone().plan_reacon(Link);
               Link.DodajNazwePliku("../datasets/path_reacon.dat");
               Link.Rysuj();
               usleep(100000);

                /* Wykonanie sekwencji ruchow drona podczas zwiadu */
               std::cout << "Wznoszenie ... " << std::endl;    
               Scenery.use_active_drone().go_verical(ALTITUDE,Link);
               usleep(100000);
               
               std::cout << "Przelot ... " << std::endl;   
               Scenery.use_active_drone().go_horizontal(REACON_RADIUS,0,Link);
               usleep(100000);

               Scenery.use_active_drone().update_angle(112.5);
               Scenery.use_active_drone().go_horizontal(REACON_RADIUS/sqrt((2+sqrt(2))/2),112.5,Link);
               usleep(100000);

               for (unsigned int i = 0;i < 7 ; ++i){
                  Scenery.use_active_drone().update_angle(45);
                  Scenery.use_active_drone().go_horizontal(REACON_RADIUS/sqrt((2+sqrt(2))/2),45,Link);
                  usleep(100000);
               }
            
               Scenery.use_active_drone().update_angle(112.5);
               Scenery.use_active_drone().go_horizontal(REACON_RADIUS,112.5,Link);
               usleep(100000);

               Scenery.use_active_drone().update_angle(180);
               Scenery.use_active_drone().go_horizontal(0,180,Link);
               usleep(10000);

               std::cout << "Ladowanie ... " << std::endl;    
               Scenery.use_active_drone().go_verical(-ALTITUDE,Link);
               usleep(100000); 

               std::cout << "Dron wyladowal ... " << std::endl; 

               Link.UsunNazwePliku("../datasets/path_reacon.dat");
               Link.Rysuj();
            break;

            default: /* dzialanie, gdy podana opcja nie bedzie uprzednio zdefiniowana */
               std::cout << ":/ Opcja niezdefiniowana" << std::endl;
         }
         
         /* Wypisanie licznika wszystkich instancji Wektora3D w porgramie, ktore powstaly */
         std::cout << "Laczna ilosc obiektow Wektor3D: " << Vector3D::get_counter_all_vectors() << std::endl;  

         /* Wypisanie licznika akutalnie istniejacych instancji Wektora3D w porgramie */
         std::cout << "Aktualna ilosc obiektow Wektor3D: " << Vector3D::get_counter_actual_vectors() << std::endl << std::endl;   
      }
   }
   catch (std::runtime_error & e){ /* W wyniku wyrzucenia bledu program poinformuje o tym i zakonczy swoje dzialanie */
      std::cerr << ":O Wystapil blad!"<< std::endl << e.what() << std::endl;
      exit(1);
   }
   return 0;
} 