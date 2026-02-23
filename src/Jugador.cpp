#include "../include/Jugador.h"

Jugador::Jugador(const std::string& nombre)
    : nombre_(nombre),
      mano_(new ListaCartas()),
      gritoUNO_(false),
      tieneEscudo_(false),
      eliminado_(false) {}

Jugador::~Jugador() {
    delete mano_;
}

void Jugador::recibirCarta(Carta* c) {
    if (c) mano_->agregar(c);
    gritoUNO_ = false;
}

Carta* Jugador::jugarCarta(int idx) {
    return mano_->extraer(idx);
}

Carta* Jugador::verCarta(int idx) const {
    return mano_->obtener(idx);
}

int Jugador::cantidadCartas() const {
    return mano_->tamanio();
}

bool Jugador::sinCartas() const {
    return mano_->vacia();
}
