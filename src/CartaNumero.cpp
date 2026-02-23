#include "../include/CartaNumero.h"
#include "../include/VistaConsola.h"
#include "../include/EstadoJuego.h"
#include <string>

CartaNumero::CartaNumero(ColorCarta color, int numero, LadoMazo lado)
    : Carta(color, TipoCarta::NUMERO, AccionCarta::NINGUNA, lado),
      numero_(numero) {}

void CartaNumero::dibujar() const {
    VistaConsola::dibujarCarta(this);
}

bool CartaNumero::esJugable(const Carta* cima) const {
    if (!cima) return true;
    return (cima->getColor() == color_) ||
           (cima->getTipo()  == TipoCarta::NUMERO &&
            dynamic_cast<const CartaNumero*>(cima) != nullptr &&
            static_cast<const CartaNumero*>(cima)->getNumero() == numero_);
}

void CartaNumero::aplicarEfecto(EstadoJuego& /*estado*/) const {
    //como son especiales sepa que efectos seme ocurran
}

std::string CartaNumero::getEtiqueta() const {
    return std::to_string(numero_);
}