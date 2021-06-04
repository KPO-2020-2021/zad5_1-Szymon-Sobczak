#pragma once

/*!
    \file  
        \brief definicje stalych wystepujacych w programie.
*/

/*! Ilosc wiecholkow przetwarzanej figury. */                         
constexpr int CORNERS = 8;  

/*! Warotsc minimalnej roznicy wartosci faktycznej od przyblizonej w programie. */            
constexpr double MAX_VALUE_DIFF = 0.0000000001;   

/*! Ilosc klatek animacji ruchu drona */      
constexpr int FRAMES = 100;  

/*! Wysokosc na jaka wznosi sie dron */ 
constexpr double ALTITUDE = 100;   

/*! Odleglosc na jaka dron odlatuje od pozycji poczatkowej. aby rozpoczac zwiad */ 
constexpr int REACON_RADIUS = 40;  