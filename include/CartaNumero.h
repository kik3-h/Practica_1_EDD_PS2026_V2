#pragma once
// carta de numero 0-9 del uno osea del mazo disponibles

#include "Carta.h"
#include <string>

class CartaNumero : public Carta {
private:
    int numero_; // de  0 a 9

public:
    CartaNumero(ColorCarta color, int numero, LadoMazo lado = LadoMazo::CLARO);

    void        dibujar()                           const override;
    bool        esJugable(const Carta* cartaCima)   const override;
    void        aplicarEfecto(EstadoJuego& estado)  const override;
    std::string getEtiqueta()                       const override;

    int getNumero() const { return numero_; }
};