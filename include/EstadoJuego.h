#pragma once

 //Struct con el estado mutable del juego
 //Pasado por referencia a aplicarEfecto()
 
#include "Enums.h"
#include "Reglas.h"


class ListaCircular;
class Mazo;

struct EstadoJuego {
    ListaCircular* jugadores      = nullptr;
    Mazo*          mazo           = nullptr;  
    

    ColorCarta  colorActual       = ColorCarta::ROJO;
    LadoMazo    ladoActual        = LadoMazo::CLARO;
    int         acumuladoRobo     = 0;     
    bool        direccionNormal   = true;  
    bool        turnoExtra        = false; 
    bool        juegoTerminado    = false;
    std::string ganador           = "";

    Reglas      reglas;

    
    bool  esperandoReto           = false;
    int   cartasReto              = 0;

    
    int   turnoActual             = 0;
};
