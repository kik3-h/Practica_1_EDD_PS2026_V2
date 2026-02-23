#include <iostream>
#include <string>
#include <limits>
#include "VistaConsola.h"
#include "Mazo.h"
#include "Jugador.h"
#include "ListaCircular.h"
#include "Reglas.h"
#include "EstadoJuego.h"
#include "Colores.h"
#include "CartaComodin.h"
#include "CartaNumero.h"

static int leerEntero(int min, int max) {
    int val;
    while (!(std::cin >> val) || val < min || val > max) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Valor inválido. Ingresa entre " << min << " y " << max << ": ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

static std::string leerLinea(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    while (s.empty()) std::getline(std::cin, s);
    return s;
}

// esto para los comodines
static ColorCarta elegirColor(LadoMazo lado) {
    std::cout << "\n  Elige el color:\n";
    if (lado == LadoMazo::CLARO) {
        std::cout << "  [1] Rojo  [2] Verde  [3] Azul  [4] Amarillo\n  Opción: ";
        int op = leerEntero(1, 4);
        switch (op) {
            case 1: return ColorCarta::ROJO;
            case 2: return ColorCarta::VERDE;
            case 3: return ColorCarta::AZUL;
            default: return ColorCarta::AMARILLO;
        }
    } else {
        std::cout << "  [1] Rosa  [2] Turquesa  [3] Naranja  [4] Violeta\n  Opción: ";
        int op = leerEntero(1, 4);
        switch (op) {
            case 1: return ColorCarta::ROSA;
            case 2: return ColorCarta::TURQUESA;
            case 3: return ColorCarta::NARANJA;
            default: return ColorCarta::VIOLETA;
        }
    }
}

static int primerCartaJugable(const Jugador* j, const Carta* cima, const EstadoJuego& estado) {
    for (int i = 0; i < j->cantidadCartas(); ++i) {
        const Carta* c = j->verCarta(i);
        if (!c) continue;
        if (estado.acumuladoRobo > 0 && estado.reglas.acumulacion) {
            if (c->getAccion() == cima->getAccion() ||
                c->getAccion() == AccionCarta::MAS_CUATRO)
                return i;
            continue;
        }
        if (c->esJugable(cima)) return i;
    }
    return -1;
}

// aca los turnos de los jugadores
static void ejecutarTurno(EstadoJuego& estado) {
    Jugador* j   = estado.jugadores->getActual();
    Carta*   cima = estado.mazo->cimaPila();

    const int MAX_J = 50;
    const Jugador* arrJ[MAX_J];
    int nJ = 0;
    int idxActual = 0;
    {
        ListaCircular::Nodo* inicio = estado.jugadores->getNodoActual();
        ListaCircular::Nodo* it    = inicio;
        do {
            arrJ[nJ] = it->jugador;
            if (it->jugador == j) idxActual = nJ;
            ++nJ;
            it = it->siguiente;
        } while (it != inicio && nJ < MAX_J);
    }

    VistaConsola::mostrarMesa(estado, arrJ, nJ, idxActual, estado.mazo->cartasRestantes(), cima);

    if (j->getTieneEscudo() && estado.acumuladoRobo > 0) {
        std::cout << Color::VERDE << Color::NEGRITA
                  << "  (x) ¡" << j->getNombre() << " tiene Escudo! El efecto se repele jaja.\n"
                  << Color::RESET;
        j->setEscudo(false);
        estado.acumuladoRobo = 0;
        estado.jugadores->siguiente();
        return;
    }

    // aca se verifica si se puede apilar mas cartas o sino toca tomarlas
    if (estado.acumuladoRobo > 0 && estado.reglas.acumulacion) {
        int idx = primerCartaJugable(j, cima, estado);
        if (idx < 0) {
            std::cout << Color::ROJO
                      << "  No puedes apilar obtienes/robas " << estado.acumuladoRobo << " cartas.\n"
                      << Color::RESET;
            for (int i = 0; i < estado.acumuladoRobo; ++i)
                j->recibirCarta(estado.mazo->robar());
            estado.acumuladoRobo = 0;
            estado.jugadores->siguiente();
            return;
        }
    }
    VistaConsola::mostrarMenuTurno(j, estado.turnoActual);

    std::string input;
    std::getline(std::cin, input);
    //alchile nose como es el upper case y tower case de java asi que uso esto jaja
    if (input == "S" || input == "s") {
        estado.juegoTerminado = true;
        std::cout << Color::AMARILLO << "\n  Saliendo de la partida y regresando al menu principal \n" << Color::RESET;
        return;
    }

    if (input == "R" || input == "r") {
        if (!estado.reglas.modoRoboB) {
            Carta* c = estado.mazo->robar();
            if (c) {
                j->recibirCarta(c);
                std::cout << "  Robaste: " << c->getEtiqueta() << "\n";
            }
            estado.jugadores->siguiente();
        } else {
            bool puedoJugar = false;
            do {
                Carta* c = estado.mazo->robar();
                if (!c) break;
                j->recibirCarta(c);
                std::cout << "  Robaste: " << c->getEtiqueta() << "\n";
                cima = estado.mazo->cimaPila();
                if (c->esJugable(cima)) { puedoJugar = true; break; }
            } while (true);
            if (!puedoJugar) estado.jugadores->siguiente();
        }
        return;
    }

    if (input == "U" || input == "u") {
        j->setGritoUNO(true);
        VistaConsola::mensajeUNO(j->getNombre());
        return;
    }

    if (input == "V" || input == "v") {
        VistaConsola::mostrarMano(j->getMano(), j->getNombre());
        VistaConsola::pausar();
        return;
    }

    // aca se intenta jugar por índice
    try {
        int idx = std::stoi(input);
        if (idx < 0 || idx >= j->cantidadCartas()) {
            VistaConsola::mensajeError("Indice fuera de rango");
            return;
        }
        Carta* c = j->verCarta(idx);
        if (!c) { VistaConsola::mensajeError("Carta invalida"); return; }

        // veo si se puede o no jugar
        bool jugable = true;
        if (estado.acumuladoRobo > 0 && estado.reglas.acumulacion) {
            jugable = (c->getAccion() == cima->getAccion() ||
                       c->getAccion() == AccionCarta::MAS_CUATRO);
        } else {
            jugable = c->esJugable(cima);
        }

        if (!jugable) {
            VistaConsola::mensajeError("Esa carta no es jugable en este momento.");
            return;
        }

        // verificar regla de flio de ganar con negra
        if (j->cantidadCartas() == 1 &&
            c->getColor() == ColorCarta::NEGRO &&
            !estado.reglas.ganarConNegra) {
            VistaConsola::mensajeError("No puedes ganar con carta negra. Debes robar.");
            Carta* rob = estado.mazo->robar();
            if (rob) j->recibirCarta(rob);
            estado.jugadores->siguiente();
            return;
        }

        Carta* jugada = j->jugarCarta(idx);

        // aca si es comodin se cambia color
        if (jugada->getTipo() == TipoCarta::COMODIN) {
            ColorCarta nuevo = elegirColor(estado.ladoActual);
            jugada->setColor(nuevo);
            estado.colorActual = nuevo;
        } else {
            estado.colorActual = jugada->getColor();
        }

        estado.mazo->descartar(jugada);

        jugada->aplicarEfecto(estado);

        
        if (j->cantidadCartas() == 1 && !j->getGritoUNO() && estado.reglas.gritoUNO) {
            // aca se verifica si tiene solo 1 carta y sino grito uno el wey
        }

        // verifica si hay un ganador
        if (j->sinCartas()) {
            estado.juegoTerminado = true;
            estado.ganador = j->getNombre();
            return;
        }
        // avanzar turno a menos que el efecto ya haya avanzado o sea turno extra
        if (!estado.turnoExtra)
            estado.jugadores->siguiente();
        else
            estado.turnoExtra = false;

    } catch (...) {
        VistaConsola::mensajeError("Opcion no reconocida.");
    }
}

// aca comenzamos jsjs
static void nuevaPartida(Reglas& reglas) {
    VistaConsola::limpiarPantalla();
    VistaConsola::titulo("---- BIENVENID@ A NUEVA PARTIDA ---");

    std::cout << "  Numero de jugadores (mínimo 2): ";
    int n = leerEntero(2, 20);

    // os se crea el jugaodr
    Jugador** jugadores = new Jugador*[n];
    for (int i = 0; i < n; ++i) {
        std::string nombre = leerLinea("  Nombre del jugador: " + std::to_string(i + 1) + ": ");
        jugadores[i] = new Jugador(nombre);
    }

    Mazo* mazo = new Mazo();
    mazo->construir(n, reglas);

    // aca utilizo la lista circular que se pide
    ListaCircular* circulo = new ListaCircular();
    for (int i = 0; i < n; ++i)
        circulo->insertar(jugadores[i]);

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < 7; ++k) // reparticion de cartas a cada jug
            jugadores[i]->recibirCarta(mazo->robar());

    Carta* primera = mazo->robar();
    while (primera && primera->getTipo() == TipoCarta::COMODIN) {
        mazo->descartar(primera);
        primera = mazo->robar();
    }
    if (primera) mazo->descartar(primera);

    // el estado inicial del juguito
    EstadoJuego estado;
    estado.jugadores  = circulo;
    estado.mazo       = mazo;
    estado.reglas     = reglas;
    estado.colorActual = primera ? primera->getColor() : ColorCarta::ROJO;
    estado.ladoActual  = LadoMazo::CLARO;

    while (!estado.juegoTerminado && circulo->tamanio() > 0) {
        ++estado.turnoActual;
        ejecutarTurno(estado);
    }

    if (!estado.ganador.empty())
        VistaConsola::mensajeGanador(estado.ganador);
    else
        std::cout << Color::AMARILLO << "\n  ¡Partida terminada!\n" << Color::RESET;

    VistaConsola::pausar();

    // aca lo que pide el inge de liberar memoria
    circulo->vaciar();
    delete circulo;
    delete mazo;
    for (int i = 0; i < n; ++i) delete jugadores[i];
    delete[] jugadores;
}

// configurar reglas
static void configurarReglas(Reglas& r) {
    bool salir = false;
    while (!salir) {
        VistaConsola::mostrarMenuReglas(r);
        int op = leerEntero(0, 7);
        switch (op) {
            case 1: r.acumulacion     = !r.acumulacion;     break;
            case 2: r.retoPlus4       = !r.retoPlus4;       break;
            case 3: r.modoRoboB       = !r.modoRoboB;       break;
            case 4: r.gritoUNO        = !r.gritoUNO;        break;
            case 5: r.ganarConNegra   = !r.ganarConNegra;   break;
            case 6: r.unoFlipActivado = !r.unoFlipActivado; break;
            case 7:
                if (r.guardar("reglas.txt"))
                    std::cout << Color::VERDE << "  Reglas guardadas en reglas.txt\n" << Color::RESET;
                VistaConsola::pausar();
                break;
            case 0: salir = true; break;
            default: break;
        }
    }
}

// ahora si el main principal 
int main() {
    Reglas reglas;

    bool ejecutar = true;
    while (ejecutar) {
        VistaConsola::mostrarMenuPrincipal();
        int op = leerEntero(0, 4);
        switch (op) {
            case 1: nuevaPartida(reglas);         break;
            case 2: configurarReglas(reglas);     break;
            case 3: VistaConsola::demoCartas();   break;
            case 4:
                if (reglas.cargar("reglas.txt"))
                    std::cout << Color::VERDE << "\n  Reglas cargadas.\n" << Color::RESET;
                else
                    VistaConsola::mensajeError("No se encontro reglas.txt");
                VistaConsola::pausar();
                break;
            case 0: ejecutar = false; break;
            default: break;
        }
    }

    std::cout << Color::TURQUESA << "\n  ¡adiositoo !\n\n" << Color::RESET;
    return 0;
}