#pragma once
//clase para toda la representación visual en terminal
 //usando códigos ANSI para colores y dibujo ASCII de cartas
#include "Carta.h"
#include "ListaCartas.h"
#include "Jugador.h"
#include "Reglas.h"
#include "EstadoJuego.h"
#include <string>

class VistaConsola {
private:
    static const char* bgColor(ColorCarta c);
    static const char* fgColor(ColorCarta c);
    static std::string simboloAccion(AccionCarta a);

public:
    static void limpiarPantalla();
    static void pausar();
    static void linea(int largo = 60);
    static void titulo(const std::string& texto);

    static void mostrarMenuPrincipal();
    static void mostrarMenuReglas(const Reglas& r);
    static void mostrarMenuTurno(const Jugador* j, int turno);

    static void dibujarCarta(const Carta* c);

    static void dibujarCartasHorizontal(const ListaCartas* lista, int inicio, int fin);

    static void mostrarMano(const ListaCartas* lista, const std::string& nombre);

    static void mostrarMesa(const EstadoJuego& estado,
                            const Jugador*     jugadores[],
                            int                nJugadores,
                            int                idxActual,
                            int                cartasMazo,
                            const Carta*       cimaPila);

    static void mensajeUNO(const std::string& nombre);
    static void mensajeGanador(const std::string& nombre);
    static void mensajePenalizacion(const std::string& nombre, int cartas);
    static void mensajeTurno(const std::string& nombre, int turno);
    static void mensajeError(const std::string& msg);
    static void mensajeFlip(LadoMazo nuevoLado);

    static void demoCartas();
};
