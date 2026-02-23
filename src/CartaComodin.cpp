#include "../include/CartaComodin.h"
#include "../include/VistaConsola.h"
#include "../include/EstadoJuego.h"
#include "../include/ListaCircular.h"
#include "../include/Mazo.h"

CartaComodin::CartaComodin(bool esMasCuatro, LadoMazo lado)
    : Carta(ColorCarta::NEGRO,
            TipoCarta::COMODIN,
            esMasCuatro ? AccionCarta::MAS_CUATRO : AccionCarta::CAMBIAR_COLOR,
            lado),
      esMasCuatro_(esMasCuatro) {}

void CartaComodin::dibujar() const {
    VistaConsola::dibujarCarta(this);
}

bool CartaComodin::esJugable(const Carta* /*cima*/) const {
    return true;
}

void CartaComodin::aplicarEfecto(EstadoJuego& estado) const {
    if (esMasCuatro_) {
        if (estado.reglas.acumulacion) {
            estado.acumuladoRobo += 4;
        } else {
            if (estado.reglas.retoPlus4) {
                estado.esperandoReto = true;
                estado.cartasReto    = 4;
            } else {
                Jugador* sig = estado.jugadores->getSiguiente();
                for (int i = 0; i < 4; ++i)
                    sig->recibirCarta(estado.mazo->robar());
                estado.jugadores->saltar();
            }
        }
    }
}

std::string CartaComodin::getEtiqueta() const {
    return esMasCuatro_ ? "+4" : "CMB";
}