#pragma once
/**
 Struct con el estado mutable del juego
 Pasado por referencia a aplicarEfecto()
 */
#include "Enums.h"
#include "Reglas.h"

// declaraciones de las clasesa a usar
class ListaCircular;
class Mazo;

struct EstadoJuego {
    ListaCircular* jugadores      = nullptr;
    Mazo*          mazo           = nullptr;  // mazo de robo
    // pila de descarte se maneja en mazo

    ColorCarta  colorActual       = ColorCarta::ROJO;
    LadoMazo    ladoActual        = LadoMazo::CLARO;
    int         acumuladoRobo     = 0;     // cartas pendientes por acumulación
    bool        direccionNormal   = true;  // true=horario
    bool        turnoExtra        = false; // skip_all: el lanzador vuelve a jugar
    bool        juegoTerminado    = false;
    std::string ganador           = "";

    Reglas      reglas;

    // Para reto del +4
    bool  esperandoReto           = false;
    int   cartasReto              = 0;

    // Contador de turno actual (para log)
    int   turnoActual             = 0;
};
