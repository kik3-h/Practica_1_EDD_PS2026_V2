#pragma once

 // Cartas comodín donde hay cambio de color y +4
 
#include "Carta.h"
#include <string>

class CartaComodin : public Carta {
private:
    bool esMasCuatro_; // true = +4 false = solo cambio de color

public:
    explicit CartaComodin(bool esMasCuatro, LadoMazo lado = LadoMazo::CLARO);

    void        dibujar()                           const override;
    bool        esJugable(const Carta* cartaCima)   const override;
    void        aplicarEfecto(EstadoJuego& estado)  const override;
    std::string getEtiqueta()                       const override;

    bool esMasCuatro() const { return esMasCuatro_; }
};