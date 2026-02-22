#pragma once

// carta flip voltea el mazo de lado claro a oscuro y viceversa

#include "Carta.h"
#include <string>

class CartaFlip : public Carta {
public:
    explicit CartaFlip(ColorCarta color, LadoMazo lado = LadoMazo::CLARO);

    void        dibujar()                           const override;
    bool        esJugable(const Carta* cartaCima)   const override;
    void        aplicarEfecto(EstadoJuego& estado)  const override;
    std::string getEtiqueta()                       const override;
};