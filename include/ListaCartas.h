#pragma once
/**
 lista enlazada simple para la mano de un jugador
 implementada con punteros y new o delete
 */
#include "Carta.h"

class ListaCartas {
private:
    struct Nodo {
        Carta* carta;
        Nodo*  siguiente;
        explicit Nodo(Carta* c) : carta(c), siguiente(nullptr) {}
    };

    Nodo* cabeza_;
    int   tamanio_;

public:
    ListaCartas()  : cabeza_(nullptr), tamanio_(0) {}
    ~ListaCartas() { limpiar(); }

    ListaCartas(const ListaCartas&)            = delete;
    ListaCartas& operator=(const ListaCartas&) = delete;

    // Agrega carta al final y segun comprendo es O(n)
    void agregar(Carta* c) {
        Nodo* nuevo = new Nodo(c);
        if (!cabeza_) {
            cabeza_ = nuevo;
        } else {
            Nodo* it = cabeza_;
            while (it->siguiente) it = it->siguiente;
            it->siguiente = nuevo;
        }
        ++tamanio_;
    }

    // elimina y retorna carta en posicion idx (0-based) O(n)
    Carta* extraer(int idx) {
        if (idx < 0 || idx >= tamanio_) return nullptr;
        Nodo* prev = nullptr;
        Nodo* curr = cabeza_;
        for (int i = 0; i < idx; ++i) { prev = curr; curr = curr->siguiente; }
        if (prev) prev->siguiente = curr->siguiente;
        else      cabeza_ = curr->siguiente;
        Carta* c = curr->carta;
        delete curr;
        --tamanio_;
        return c;
    }

    //acceso por indice O(n)
    Carta* obtener(int idx) const {
        if (idx < 0 || idx >= tamanio_) return nullptr;
        Nodo* it = cabeza_;
        for (int i = 0; i < idx; ++i) it = it->siguiente;
        return it->carta;
    }

    int  tamanio()  const { return tamanio_; }
    bool vacia()    const { return tamanio_ == 0; }

    // libera nodos sin destruir cartas la carta la gestiona el mazo pa ahorrar memoria
    void limpiar() {
        while (cabeza_) {
            Nodo* tmp = cabeza_;
            cabeza_ = cabeza_->siguiente;
            delete tmp;
        }
        tamanio_ = 0;
    }
};
