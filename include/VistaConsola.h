#pragma once
/**
 clase para toda la representación visual en terminal
 usando códigos ANSI para colores y dibujo ASCII de cartas
 */
#include "Carta.h"
#include "ListaCartas.h"
#include "Jugador.h"
#include "Reglas.h"
#include "EstadoJuego.h"
#include <string>

class VistaConsola {
private:
    // Retorna el código ANSI de fondo según color de carta
    static const char* bgColor(ColorCarta c);
    //Retorna el código ANSI de texto según color de carta
    static const char* fgColor(ColorCarta c);
// Símbolo para el tipo de acción 
    static std::string simboloAccion(AccionCarta a);

public:
    //Utilidades de pantalla
    static void limpiarPantalla();
    static void pausar();
    static void linea(int largo = 60);
    static void titulo(const std::string& texto);

    // Menús
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

    // Mensajes del juego
    static void mensajeUNO(const std::string& nombre);
    static void mensajeGanador(const std::string& nombre);
    static void mensajePenalizacion(const std::string& nombre, int cartas);
    static void mensajeTurno(const std::string& nombre, int turno);
    static void mensajeError(const std::string& msg);
    static void mensajeFlip(LadoMazo nuevoLado);

    // Demo de cartas
    static void demoCartas();
};
