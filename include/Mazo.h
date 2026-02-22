#pragma once

//mazo implementado con Stack<Carta*>
//incluye algoritmo Fisher-Yates para barajar

#include "Stack.h"
#include "Carta.h"
#include "Reglas.h"

class Mazo {
private:
    Stack<Carta*> pilaMazo_;     // cartas para robar o tomar como se diga alv
    Stack<Carta*> pilaDescarte_; // cartas jugadas 

    void crearMazoClaro();
    void crearMazoOscuro();
public:
    Mazo() = default;
    ~Mazo();

    Mazo(const Mazo&)            = delete;
    Mazo& operator=(const Mazo&) = delete;

    //aca se construye n_jugadores cantidad con mazos combinados y los baraja 
    //formula segun investigue y la que implemento ((n_jugadores - 1) / 6 + 1) mazos
    
    void construir(int n_jugadores, const Reglas& reglas);

    Carta* robar();

    void descartar(Carta* c);

    Carta* cimaPila() const;

    void reciclarDescarte();

    int cartasRestantes() const { return pilaMazo_.size(); }
    int cartasDescartadas()const{ return pilaDescarte_.size(); }

    bool estaVacio() const { return pilaMazo_.empty(); }

    void barajar();
    Stack<Carta*>& getPilaDescarte() { return pilaDescarte_; }
};