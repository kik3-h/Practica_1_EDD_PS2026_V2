//implementación de CartaAccion (+2, +1, Skip, Reverse)

#include "../include/CartaAccion.h"
#include "../include/VistaConsola.h"
#include "../include/EstadoJuego.h"
#include "../include/ListaCircular.h"
#include "../include/Mazo.h"

CartaAccion::CartaAccion(ColorCarta color, AccionCarta accion, LadoMazo lado)
    : Carta(color, TipoCarta::ACCION, accion, lado) {}

void CartaAccion::dibujar() const {
    VistaConsola::dibujarCarta(this);
}

bool CartaAccion::esJugable(const Carta* cima) const {
    if (!cima) return true;
    return (cima->getColor()  == color_)  ||
           (cima->getAccion() == accion_) ||
           (cima->getTipo()   == TipoCarta::COMODIN);
}

void CartaAccion::aplicarEfecto(EstadoJuego& estado) const {
    Jugador* sig = estado.jugadores->getSiguiente();
    switch (accion_) {
        case AccionCarta::MAS_DOS:
            if (estado.reglas.acumulacion) {
                estado.acumuladoRobo += 2;
            } else {
                for (int i = 0; i < 2; ++i)
                    sig->recibirCarta(estado.mazo->robar());
                estado.jugadores->saltar();
            }
            break;
        case AccionCarta::MAS_UNO:
            sig->recibirCarta(estado.mazo->robar());
            estado.jugadores->saltar();
            break;
        case AccionCarta::MAS_TRES:
            if (estado.reglas.acumulacion)
                estado.acumuladoRobo += 3;
            else {
                for (int i = 0; i < 3; ++i)
                    sig->recibirCarta(estado.mazo->robar());
                estado.jugadores->saltar();
            }
            break;
        case AccionCarta::SKIP:
            estado.jugadores->saltar();
            break;
        case AccionCarta::SKIP_TODOS:
            estado.turnoExtra = true;
            break;
        case AccionCarta::REVERSE:
            estado.jugadores->invertir();
            estado.direccionNormal = !estado.direccionNormal;
            if (estado.jugadores->tamanio() == 2)
                estado.jugadores->saltar();
            break;
        default:
            break;
    }
}

std::string CartaAccion::getEtiqueta() const {
    switch (accion_) {
        case AccionCarta::MAS_DOS:    return "+2";
        case AccionCarta::MAS_UNO:    return "+1";
        case AccionCarta::MAS_TRES:   return "+3";
        case AccionCarta::SKIP:       return "SKP";
        case AccionCarta::SKIP_TODOS: return "SKP!";
        case AccionCarta::REVERSE:    return "REV";
        default:                      return "?";
    }
}
