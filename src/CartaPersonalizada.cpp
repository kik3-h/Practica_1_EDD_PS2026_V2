#include "../include/CartaPersonalizada.h"
#include "../include/VistaConsola.h"
#include "../include/EstadoJuego.h"
#include "../include/ListaCircular.h"
#include "../include/Mazo.h"
//cartas creativas  RobaColor y Escudo

CartaRobaColor::CartaRobaColor(ColorCarta color, LadoMazo lado)
    : Carta(color, TipoCarta::PERSONALIZADA_ROBA_COLOR,
            AccionCarta::ROBA_COLOR, lado) {}

void CartaRobaColor::dibujar() const {
    VistaConsola::dibujarCarta(this);
}

bool CartaRobaColor::esJugable(const Carta* cima) const {
    if (!cima) return true;
    return (cima->getColor() == color_) ||
           (cima->getAccion()== AccionCarta::ROBA_COLOR);
}

void CartaRobaColor::aplicarEfecto(EstadoJuego& estado) const {
    Jugador* sig = estado.jugadores->getSiguiente();
    ListaCartas* mano = sig->getMano();
    int i = 0;
    while (i < mano->tamanio()) {
        Carta* c = mano->obtener(i);
        if (c && c->getColor() == estado.colorActual) {
            Carta* extraida = mano->extraer(i);
            estado.mazo->descartar(extraida);
        } else {
            ++i;
        }
    }
}

std::string CartaRobaColor::getEtiqueta() const { return "ROBC"; }

CartaEscudo::CartaEscudo(ColorCarta color, LadoMazo lado)
    : Carta(color, TipoCarta::PERSONALIZADA_ESCUDO,
            AccionCarta::ESCUDO, lado) {}

void CartaEscudo::dibujar() const {
    VistaConsola::dibujarCarta(this);
}

bool CartaEscudo::esJugable(const Carta* cima) const {
    if (!cima) return true;
    return (cima->getColor() == color_) ||
           (cima->getAccion()== AccionCarta::ESCUDO);
}

void CartaEscudo::aplicarEfecto(EstadoJuego& estado) const {
    Jugador* actual = estado.jugadores->getActual();
    if (actual) actual->setEscudo(true);
}

std::string CartaEscudo::getEtiqueta() const { return "ESCUD"; }