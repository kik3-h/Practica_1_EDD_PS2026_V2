#include "../include/CartaFlip.h"
#include "../include/VistaConsola.h"
#include "../include/EstadoJuego.h"

CartaFlip::CartaFlip(ColorCarta color, LadoMazo lado)
    : Carta(color, TipoCarta::FLIP, AccionCarta::FLIP_MAZO, lado) {}

void CartaFlip::dibujar() const {
    VistaConsola::dibujarCarta(this);
}

bool CartaFlip::esJugable(const Carta* cima) const {
    if (!cima) return true;
    return (cima->getColor()  == color_) ||
           (cima->getAccion() == AccionCarta::FLIP_MAZO) ||
           (cima->getTipo()   == TipoCarta::COMODIN);
}

void CartaFlip::aplicarEfecto(EstadoJuego& estado) const {
    // Voltear el lado activo
    estado.ladoActual = (estado.ladoActual == LadoMazo::CLARO)
                        ? LadoMazo::OSCURO
                        : LadoMazo::CLARO;
    VistaConsola::mensajeFlip(estado.ladoActual);
}

std::string CartaFlip::getEtiqueta() const {
    return "FLIP";
}