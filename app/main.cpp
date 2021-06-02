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
   char Option;
   double user_angle=0,distance = 0;
   unsigned int nbr_of_act_drone=1;
   PzG::LaczeDoGNUPlota Link;

   Scene Scenery(Link);
 
   Link.Inicjalizuj();

   try{
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
      
      while (Option != 'k'){ /* Glowna petla menu, dzialajaca do czasu wybrania opcji zakonczenia- k */
         std::cout << "Twoj wybor? (m - menu) > ";
         std::cin >> Option;
         switch(Option){  
            case 'a':
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
            
            case 'p':
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
               std::cout << "Rysowanie zaplanowanej sciezki przelotu ... " << std::endl;
               Scenery.use_active_drone().plan_path(user_angle,distance,Link);
               Link.DodajNazwePliku("../datasets/path.dat");
               usleep(100000);
               
               std::cout << "Wznoszenie ... " << std::endl;    
               Scenery.use_active_drone().go_verical(ALTITUDE,Link);
               usleep(1000000);
                  
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
            
            case 'm':
               std::cout << "Menu wyboru opcji:" << std::endl
               << "\ta - wybierz aktywnego drona" << std::endl
               << "\tp - zadaj parametry przelotu" << std::endl
               << "\tm - wyswietl menu" << std::endl 
               << "\tz - wykonaj zwiad" << std::endl << std::endl
               << "\tk - koniec dzialania programu" << std::endl << std::endl;
            break;
               
            case 'k':
               std::cout << "Konczenie pracy programu ..." << std::endl;
            break;

            case 'z':
               std::cout << "Wykonywanie zwiadu ..." << std::endl;

               std::cout << "Rysowanie zaplanowanej sciezki przelotu ... " << std::endl;
               Scenery.use_active_drone().plan_reacon(Link);
               Link.DodajNazwePliku("../datasets/path_reacon.dat");
               Link.Rysuj();
               usleep(100000);

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

            default:   /* dzialanie, gdy podana opcja nie bedzie uprzednio zdefiniowana */
               std::cout << ":/ Opcja niezdefiniowana" << std::endl;
         }
      
   /*    std::cout << "Aktualna ilosc obiektow Wektor3D: " << test.counter_actual_vectors << std::endl;
         std::cout << "Laczna ilosc obiektow Wektor3D: " << test.counter_all_vectors << std::endl;  */
      }
   }
   catch (std::runtime_error & e){ /* W wyniku wyrzucenia bledu program poinformuje o tym i zakonczy swoje dzialanie */
      std::cerr << ":O Wystapil blad!"<< std::endl << e.what() << std::endl;
      exit(1);
   }
   return 0;
} 
    // try{
        

    //     double Apx1[]={50,60,40}; /* Dodanie do sceny pierwszego, przykladowego prostopadloscianu */
    //     Vector3D A(Apx1);
    //     Scenery.Add_cuboid(A,40,30,20);
    //     Scenery[active_cuboid].Write_cub_to_file(adresses_of_files.at(active_cuboid).c_str()); /* Zapis i wyswietlenie w GNUplot stanu poczatkowego, pierwszego, przykladowego prostopadloscianu */
    //     Link.Rysuj();
 
    //     std::cout << "Poczatkowy stan bokow prostopadloscianu: " << std::endl;
    //     Scenery[active_cuboid].Is_it_cub(); 

    //     std::cout << "Menu wyboru opcji:" << std::endl
    //               << "\ta - zmien aktywny prostopadloscian" << std::endl
    //               << "\to - obrot bryly o zadana sekwencje katow" << std::endl
    //               << "\tt - powtorzenie poprzedniego obrotu" << std::endl
    //               << "\tr - wyswietlenie macierzy rotacji" << std::endl
    //               << "\tp - przesuniecie bryly o zadany wektor " << std::endl
    //               << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
    //               << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
    //               << "\tm - wyswietl menu" << std::endl
    //               << "\td - dodaj nowy prostopadloscian" << std::endl
    //               << "\tk - koniec dzialania programu" << std::endl << std::endl;

    //     while (Option != 'k'){ /* Glowna petla menu, dzialajaca do czasu wybrania opcji zakonczenia- k */
    //         std::cout << "Numer aktywnego prostopadloscianu: " << active_cuboid << std::endl;
    //         std::cout << "Twoj wybor? (m - menu) > ";
    //         std::cin >> Option;
    //         switch(Option){  
    //             case 'a': /* Opcja pozwalajaca na zmiane aktywnego prostopaloscianu */
    //                 while (true){
    //                     try{
    //                         std::cout << "Podaj numer prostopadloscianu, ktory ma byc aktywny: " << std::endl;;
    //                         std::cout << "Dostepne prostopadlosciany [0;" << Scenery.how_many_cuboids()-1  << "] " << std::endl;
    //                         std::cin >> active_cuboid; 
    //                         if(std::cin.fail() || active_cuboid > (Scenery.how_many_cuboids()-1))
    //                             throw std::invalid_argument(":/ Podano bledny numer prostopadloscianu ");
    //                         else   
    //                             break;
    //                     }
    //                     catch (std::invalid_argument & a){ 
    //                         std::cerr << a.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
    //                         std::cin.clear();
    //                         std::cin.ignore(10000,'\n');   
    //                     }
    //                 } 
    //             break;

    //             case 'o': /* Opcja pozwalajaca na zadanie sekwencji obrotu prostopadloscianu */
    //                 temp_rot_matrix.reset_matrix();
    //                 std::cout << "Podaj sekwencje: " << std::endl; /* Okreslenie sekwencji obrotow prostopadloscianu */
    //                 while (Option !='.'){  
    //                     try{
    //                         std::cin >> Option;
    //                         switch(Option){
    //                             case 'x':
    //                             std::cin >> angle;
    //                             if(std::cin.fail())
    //                                 throw std::invalid_argument(":/ Podano bledna wartosc kata obrotu "); /*  */
    //                             else 
    //                                 temp_rot_matrix = Fill_matrix_OX(angle) * temp_rot_matrix;
    //                             break;

    //                             case 'y':
    //                             std::cin >> angle;
    //                             if(std::cin.fail())
    //                                 throw std::invalid_argument(":/ Podano bledna wartosc kata obrotu ");
    //                             else
    //                                 temp_rot_matrix = Fill_matrix_OY(angle) * temp_rot_matrix;
    //                             break;

    //                             case 'z':
    //                             std::cin >> angle;
    //                             if(std::cin.fail())
    //                                 throw std::invalid_argument(":/ Podano bledna wartosc kata obrotu ");
    //                             else
    //                                 temp_rot_matrix = Fill_matrix_OZ(angle) * temp_rot_matrix;
    //                             break;

    //                             case '.':    
    //                                 std::cout << ":) Podawanie sekwencji obrotow zakonczone pomyslnie. " << std::endl;      
    //                             break;

    //                             default:
    //                                 std::cout << ":/ Bledne oznaczenie osi. Dopuszczalne znaki to: (x, y, z, .)" << std::endl; 
    //                                 std::cout << ":/ Sprobuj jeszcze raz" << std::endl;
    //                                 std::cin.ignore(10000,'\n');
    //                             break;            
    //                           } 
    //                     }
    //                     catch (std::invalid_argument & d){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby, program poinformuje o tym i usunie blad ze strumienia */
    //                         std::cerr << d.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
    //                         std::cin.clear();
    //                         std::cin.ignore(10000,'\n');   
    //                     }
    //                 }

    //                 while (true){
    //                     try{
    //                         std::cout << "Ile razy operacja obrotu ma byc powtorzona? "<< std::endl; /* Okreslenie ile razy wprowadzony obrot ma sie wykonac */
    //                         std::cin >> multiplier; 
    //                         if(std::cin.fail() || multiplier < 0)
    //                             throw std::invalid_argument(":/ Podano bledna wartosc mnoznika ");
    //                         else   
    //                             break;
    //                     }
    //                     catch (std::invalid_argument & f){ /* W wyniku wyrzucenia bledu dot. wprowadzania liczby, program poinformuje o tym i usunie blad ze strumienia */
    //                         std::cerr << f.what() << std::endl << ":/ Sprobuj jeszcze raz"  << std::endl;
    //                         std::cin.clear();
    //                         std::cin.ignore(10000,'\n');   
    //                     }
    //                 } 

    //                 for (unsigned int i=0; i<multiplier;++i) /* Uzupelnienie macierzy rotacji dla wskazanego prostopadloscianu o zadana sekwencje obrotu, zadana ilosc razy */
    //                     Scenery.update_matrix(temp_rot_matrix, active_cuboid);
                    
    //                 Scenery.Move_figure(active_cuboid); /* Wykonanie obrotu i wyswietlenie w Gnuplot */
    //                 Scenery[active_cuboid].Is_it_cub();
    //                 Scenery[active_cuboid].Write_cub_to_file(adresses_of_files.at(active_cuboid).c_str());
    //                 Link.Rysuj();
    //             break;

    //             case 'p': /* Opcja translacji o wektor */
    //                 std::cout << "Wprowadz wspolrzedne wektora translacji w postaci trzech liczb 'x y z' ";
    //                 std::cin >> T_vector;

    //                 Scenery.update_vector(T_vector,active_cuboid);
    //                 Scenery.Move_figure(active_cuboid);

    //                 Scenery[active_cuboid].Write_cub_to_file(adresses_of_files[active_cuboid].c_str());
    //                 Scenery[active_cuboid].Is_it_cub();
                    
    //                 Link.Rysuj();
    //             break;

    //             case 'w': /* Opcja wyswietlajaca wspolrzedne prostopadloscianu */
    //                 std::cout << "Aktualne wspolrzedne prostopadloscianu: " << std::endl;
    //                 std::cout << Scenery[active_cuboid];
    //             break;

    //             case 't': /* Opcja pozwlajaca na powtorzenie ostatniej rotacji na aktywnym prostopadloscianie */
    //                 for (unsigned int i=0; i<multiplier;++i)
    //                     Scenery.update_matrix(temp_rot_matrix,active_cuboid);  
    //                 Scenery.Move_figure(active_cuboid);
    //                 Scenery[active_cuboid].Write_cub_to_file(adresses_of_files[active_cuboid].c_str());
    //                 Scenery[active_cuboid].Is_it_cub();
    //                 Link.Rysuj();
    //             break;

    //             case 'r': /* Opcja ponawiajaca ostatni obrot prostopadloscianu */   
    //                 std::cout << "Macierz rotacji " << std::endl << Scenery.get_matrix(active_cuboid) << std::endl; 
    //             break;

    //             case 'm': /* Opcja wyswietlajaca dostepne w menu opcje */        
    //                 std::cout << "Menu wyboru opcji:" << std::endl
    //                           << "\ta - zmien aktywny prostopadloscian" << std::endl
    //                           << "\to - obrot bryly o zadana sekwencje katow" << std::endl
    //                           << "\tt - powtorzenie poprzedniego obrotu" << std::endl
    //                           << "\tr - wyswietlenie macierzy rotacji" << std::endl
    //                           << "\tp - przesuniecie bryly o zadany wektor " << std::endl
    //                           << "\tw - wyswietlenie wspolrzednych wierzcholkow " << std::endl
    //                           << "\ts - sprawdzenie dlugosci przeciwleglych bokow" << std::endl
    //                           << "\tm - wyswietl menu" << std::endl
    //                           << "\td - dodaj nowy prostopadloscian" << std::endl
    //                           << "\tk - koniec dzialania programu" << std::endl << std::endl;
    //             break;

    //             case 'k': /* Opcja konczaca program */
    //                 std::cout << ":) Konczenie pracy programu" << std::endl;
    //             break;

    //             case 's': /* Opcja wyswietlajaca wspolrzedne prostopadloscianu */
    //                 Scenery[active_cuboid].Is_it_cub();
    //             break;

    //             case 'd': /* Opcja dodajaca do sceny nowy prostopadloscian */
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

    //             default: /* dzialanie, gdy podana opcja nie bedzie uprzednio zdefiniowana */
    //                 std::cout << ":/ Opcja niezdefiniowana" << std::endl;
    //         }
    //     }
    // }
    // catch (std::runtime_error & e){ /* W wyniku wyrzucenia bledu program poinformuje o tym i zakonczy swoje dzialanie */
    //     std::cerr << ":O Wystapil blad!"<< std::endl << e.what() << std::endl;
    //     exit(1);
    // }


