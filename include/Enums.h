#pragma once
//Enums.h
// clase para enumeraciones globales donde obtengo colores, tipos de carta, lados UNO Flip
 
#include <string>

// colores que estaran disponibles
enum class ColorCarta {

    
    ROJO, VERDE, AZUL, AMARILLO, // lado claro
    ROSA, TURQUESA, NARANJA, VIOLETA, // lado oscuro uno flip
    // cartas especiales
    NEGRO,   // comodín normal
    NINGUNO  // sin color asignado aún
};

// tipos de carta
enum class TipoCarta {
    NUMERO,
    ACCION,     // +2, +4, saltar, reversa
    COMODIN,    // cambia color o la +4 comodín
    FLIP,       // carta de volteo esto en uno flip
    PERSONALIZADA_ROBA_COLOR,  // carta personalizada 1
    PERSONALIZADA_ESCUDO        // carta "" 2
};

// lado del mazo uno flip
enum class LadoMazo { CLARO, OSCURO };

// acciones de carta
enum class AccionCarta {
    NINGUNA,
    MAS_UNO,     // +1 en flip claro
    MAS_DOS,     // +2
    MAS_TRES,    // +3 en flip oscuro
    MAS_CUATRO,  // +4
    MAS_SEIS,    // +6 flip oscuro
    SKIP,        // saltar siguiente
    SKIP_TODOS,  // saltar todos flip oscuro, vuelve al lanzador
    REVERSE,     // invertir dirección
    CAMBIAR_COLOR,
    FLIP_MAZO,   // voltear mazo claro oscuro
    COLOR_ETERNO,// comodín oscuro: siguiente roba hasta hallar color
    ROBA_COLOR,  // carta personalizada
    ESCUDO       // carta personalizada
};

// Utilidades
inline std::string colorNombre(ColorCarta c) {
    switch (c) {
         case ColorCarta::ROJO:     return "Rojo";
         case ColorCarta::VERDE:    return "Verde";
         case ColorCarta::AZUL:     return "Azul";
        case ColorCarta::AMARILLO: return "Amarillo";
        case ColorCarta::ROSA:     return "Rosa";
        case ColorCarta::TURQUESA: return "Turquesa";
        case ColorCarta::NARANJA:  return "Naranja";
        case ColorCarta::VIOLETA:  return "Violeta";
        case ColorCarta::NEGRO:    return "Negro";
        default:                   return "?";
    }
}
