#pragma once

/* 
Dos cartas personalizadas creativas:
 1) CartaRobaColor  el siguiente jugador roba todas las cartas de un color específico de su mano
 2) CartaEscudo      protege al jugador actual del próximo efecto de robo (+2/+4/+6)

 alchile no se me ocurrio algo mas ingenioso ajajaj
*/

#include "Carta.h"
#include <string>

/* carta roba color
 el jugador elige un color el siguiente jugador debe robar todas sus cartas
 de ese color y añadirlas al mazo y las pierde de su mano
 */
class CartaRobaColor : public Carta {
public:
    explicit CartaRobaColor(ColorCarta color, LadoMazo lado = LadoMazo::CLARO);

    void        dibujar()                           const override;
    bool        esJugable(const Carta* cartaCima)   const override;
    void        aplicarEfecto(EstadoJuego& estado)  const override;
    std::string getEtiqueta()                       const override;
};

/* carta escudo
 cuando se juega activa un escudo sobre el jugador actual
 el próximo efecto de robo +2/+4/+6 queda anulado y se devuelve al que lo lanzo como en el lol
*/
class CartaEscudo : public Carta {
public:
    explicit CartaEscudo(ColorCarta color, LadoMazo lado = LadoMazo::CLARO);

    void        dibujar()                           const override;
    bool        esJugable(const Carta* cartaCima)   const override;
    void        aplicarEfecto(EstadoJuego& estado)  const override;
    std::string getEtiqueta()                       const override;
};