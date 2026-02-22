#pragma once
//cartas de acción +2, +1(flip), Skip, Reverse
// 
#include "Carta.h"
#include <string>

class CartaAccion : public Carta { //hereda de carta .h
public:
    CartaAccion(ColorCarta color, AccionCarta accion,
                LadoMazo lado = LadoMazo::CLARO);

    void        dibujar()                           const override;
    bool        esJugable(const Carta* cartaCima)   const override;
    void        aplicarEfecto(EstadoJuego& estado)  const override;
    std::string getEtiqueta()                       const override;
};
