#include "../include/Mazo.h"
#include "../include/CartaNumero.h"
#include "../include/CartaAccion.h"
#include "../include/CartaComodin.h"
#include "../include/CartaFlip.h"
#include "../include/CartaPersonalizada.h"
#include <cstdlib>
#include <ctime>
//implementación del Mazo con Stack<Carta*> y Fisher-Yates
//destructor
Mazo::~Mazo() {
    while (!pilaMazo_.empty()) {
        delete pilaMazo_.top();
        pilaMazo_.pop();
    }
    while (!pilaDescarte_.empty()) {
        delete pilaDescarte_.top();
        pilaDescarte_.pop();
    }
}

void Mazo::crearMazoClaro() {
    ColorCarta colores[] = {
        ColorCarta::ROJO, ColorCarta::VERDE,
        ColorCarta::AZUL, ColorCarta::AMARILLO
    };

    for (auto& col : colores) {
        
        pilaMazo_.push(new CartaNumero(col, 0, LadoMazo::CLARO));
        
        for (int num = 1; num <= 9; ++num) {
            pilaMazo_.push(new CartaNumero(col, num, LadoMazo::CLARO));
            pilaMazo_.push(new CartaNumero(col, num, LadoMazo::CLARO));
        }
        
        for (int i = 0; i < 2; ++i) {
            pilaMazo_.push(new CartaAccion(col, AccionCarta::SKIP,    LadoMazo::CLARO));
            pilaMazo_.push(new CartaAccion(col, AccionCarta::REVERSE, LadoMazo::CLARO));
            pilaMazo_.push(new CartaAccion(col, AccionCarta::MAS_DOS, LadoMazo::CLARO));
        }   
        pilaMazo_.push(new CartaRobaColor(col, LadoMazo::CLARO));
        pilaMazo_.push(new CartaEscudo(col, LadoMazo::CLARO));
    }
    for (int i = 0; i < 4; ++i) {
        pilaMazo_.push(new CartaComodin(false, LadoMazo::CLARO));
        pilaMazo_.push(new CartaComodin(true,  LadoMazo::CLARO));
    }
}

// construcción de lado oscuro uno flip
void Mazo::crearMazoOscuro() {
    ColorCarta coloresOscuros[] = {
        ColorCarta::ROSA,    ColorCarta::TURQUESA,
        ColorCarta::NARANJA, ColorCarta::VIOLETA
    };

    for (auto& col : coloresOscuros) {
        pilaMazo_.push(new CartaNumero(col, 0, LadoMazo::OSCURO));
        for (int num = 1; num <= 9; ++num) {
            pilaMazo_.push(new CartaNumero(col, num, LadoMazo::OSCURO));
            pilaMazo_.push(new CartaNumero(col, num, LadoMazo::OSCURO));
        }
        for (int i = 0; i < 2; ++i) {
            pilaMazo_.push(new CartaAccion(col, AccionCarta::SKIP_TODOS, LadoMazo::OSCURO));
            pilaMazo_.push(new CartaAccion(col, AccionCarta::REVERSE,    LadoMazo::OSCURO));
            pilaMazo_.push(new CartaAccion(col, AccionCarta::MAS_TRES,   LadoMazo::OSCURO));
        }
        pilaMazo_.push(new CartaFlip(col, LadoMazo::OSCURO));
        pilaMazo_.push(new CartaFlip(col, LadoMazo::OSCURO));
    }
    for (int i = 0; i < 4; ++i) {
        pilaMazo_.push(new CartaComodin(false, LadoMazo::OSCURO)); 
        pilaMazo_.push(new CartaAccion(ColorCarta::NEGRO, AccionCarta::MAS_SEIS, LadoMazo::OSCURO));
    }
}

// construir mazos combinados
void Mazo::construir(int n_jugadores, const Reglas& reglas) {
    int nMazos = (n_jugadores - 1) / 6 + 1;
    for (int m = 0; m < nMazos; ++m) {
        crearMazoClaro();
        if (reglas.unoFlipActivado) crearMazoOscuro();
    }
    barajar();
}
 
void Mazo::barajar() {
    int n = pilaMazo_.size();
    if (n <= 1) return;

    Carta** arr = new Carta*[n];
    pilaMazo_.toArray(arr);

    srand(static_cast<unsigned>(time(nullptr)));
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Carta* tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }

    pilaMazo_.fromArray(arr, n);
    delete[] arr;
}

Carta* Mazo::robar() {
    if (pilaMazo_.empty()) reciclarDescarte();
    if (pilaMazo_.empty()) return nullptr;
    Carta* c = pilaMazo_.top();
    pilaMazo_.pop();
    return c;
}

void Mazo::descartar(Carta* c) {
    if (c) pilaDescarte_.push(c);
}

Carta* Mazo::cimaPila() const {
    if (pilaDescarte_.empty()) return nullptr;
    return pilaDescarte_.top();
}

void Mazo::reciclarDescarte() {
    if (pilaDescarte_.empty()) return;
    Carta* cima = pilaDescarte_.top();
    pilaDescarte_.pop();
    while (!pilaDescarte_.empty()) {
        pilaMazo_.push(pilaDescarte_.top());
        pilaDescarte_.pop();
    }
    barajar();
    pilaDescarte_.push(cima);
}
