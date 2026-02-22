#pragma once
//Enums.h
// clase para enumeraciones globales donde obtengo colores, tipos de carta, lados UNO Flip
 
#include <string>

// colores que estaran disponibles
enum class ColorCarta {

    
    ROJO, VERDE, AZUL, AMARILLO, 
    ROSA, TURQUESA, NARANJA, VIOLETA, 
    
    NEGRO,   
    NINGUNO  
};


enum class TipoCarta {
    NUMERO,
    ACCION,     // +2, +4, saltar, reversa
    COMODIN,    // cambia color o la +4 comodín
    FLIP,       // carta de volteo esto en uno flip
    PERSONALIZADA_ROBA_COLOR,  // carta personalizada 1
    PERSONALIZADA_ESCUDO        // carta "" 2
};


enum class LadoMazo { CLARO, OSCURO };


enum class AccionCarta {
    NINGUNA,
    MAS_UNO,     
    MAS_DOS,     
    MAS_TRES,    
    MAS_CUATRO,  
    MAS_SEIS,    
    SKIP,        
    SKIP_TODOS,  
    REVERSE,     
    CAMBIAR_COLOR,
    FLIP_MAZO,   
    COLOR_ETERNO,
    ROBA_COLOR,  
    ESCUDO       
};


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
