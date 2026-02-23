#pragma once

//lista circular doblemente enlazada para el orden de turnos
//implementada desde cero con punteros 

//esta mrda me llevo un buen de tiempo ajskaj

#include "Jugador.h"

class ListaCircular {
public:
    struct Nodo {
        Jugador* jugador;
        Nodo*    siguiente;
        Nodo*    anterior;
        explicit Nodo(Jugador* j)
            : jugador(j), siguiente(nullptr), anterior(nullptr) {}
    };

private:
    Nodo* actual_;    
    int   tamanio_;
    bool  sentidoNormal_; // true = horario, false = antihorario / esto es clave eh (como peru xd)

public:
    ListaCircular()  : actual_(nullptr), tamanio_(0), sentidoNormal_(true) {}
    ~ListaCircular() { vaciar(); }

    ListaCircular(const ListaCircular&)            = delete;
    ListaCircular& operator=(const ListaCircular&) = delete;

    //se inserta un jugador al final del círculo O(1) con puntero anterior debido a la naturaleza circular vea
    void insertar(Jugador* j) {
        Nodo* nuevo = new Nodo(j);
        if (!actual_) {
            actual_ = nuevo;
            nuevo->siguiente = nuevo;
            nuevo->anterior  = nuevo;
        } else {
            // por lo cual se inserta antes del actual = al final del círculo y se actualizan punteros
            Nodo* prev = actual_->anterior;
            prev->siguiente  = nuevo;
            nuevo->anterior  = prev;
            nuevo->siguiente = actual_;
            actual_->anterior = nuevo; //esto es clave para mantener la circularidad y la inserción O(1)
        }
        ++tamanio_;
    }

    // avanza al siguiente turno segun direccion 
    void siguiente() {
        if (!actual_) return;
        actual_ = sentidoNormal_ ? actual_->siguiente : actual_->anterior;
    }

    // salta un turno O(1) con punteros vea
    void saltar() {
        siguiente();
        siguiente();
    }

    // Salta a todos (SkipAll flip oscuro): vuelve al mismo jugador actual 

    // Solo avanzamos sin cambiar – el mismo jugador vuelve a jugar 

       /* void saltarTodos() {
            if (!actual_) return;
            // No avanzamos el actual, el mismo jugador vuelve a jugar
        } alch no funcionaba y lo deje asi xd*/

    void invertir() { sentidoNormal_ = !sentidoNormal_; }

    void eliminarActual() {
        if (!actual_ || tamanio_ == 0) return;
        Nodo* siguiente = actual_->siguiente;
        if (tamanio_ == 1) {
            delete actual_;
            actual_ = nullptr;
            tamanio_ = 0;
            return;
        }
        Nodo* prev = actual_->anterior;
        prev->siguiente    = actual_->siguiente;
        siguiente->anterior = prev;
        delete actual_;
        actual_ = siguiente;
        --tamanio_;
    }
    Jugador* getActual()    const { return actual_ ? actual_->jugador : nullptr; }
    Jugador* getSiguiente() const {
        if (!actual_) return nullptr;
        Nodo* sig = sentidoNormal_ ? actual_->siguiente : actual_->anterior;
        return sig->jugador;
    }
    int  tamanio()          const { return tamanio_; }
    bool estaVacia()        const { return tamanio_ == 0; }
    bool getSentido()       const { return sentidoNormal_; }

    // Libera todos los nodos no destruye la gestión de memoria
    void vaciar() {
        if (!actual_) return;
        Nodo* it = actual_;
        for (int i = 0; i < tamanio_; ++i) {
            Nodo* tmp = it;
            it = it->siguiente;
            delete tmp;
        }
        actual_   = nullptr;
        tamanio_  = 0;
    }

    // iteracion retorna el nodo actual para recorrerlo
    Nodo* getNodoActual() const { return actual_; }
};