#include "../include/VistaConsola.h"
#include "../include/Colores.h"
#include "../include/CartaNumero.h"
#include "../include/CartaAccion.h"
#include "../include/CartaComodin.h"
#include "../include/CartaFlip.h"
#include "../include/CartaPersonalizada.h"
#include <iostream>
#include <iomanip> //libreria de couts y cins
#include <string>
#include <limits> //para definir limites entre valores numericos

void VistaConsola::limpiarPantalla() {
    std::cout << "\033[2J\033[H";
}

void VistaConsola::pausar() {
    std::cout << Color::DIM << "\n  porfa presiona ENTER para continuar..." << Color::RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void VistaConsola::linea(int largo) {
    std::cout << Color::DIM;
    for (int i = 0; i < largo; ++i) std::cout << "─";
    std::cout << Color::RESET << "\n";
}

void VistaConsola::titulo(const std::string& texto) {
    std::cout << "\n" << Color::NEGRITA << Color::AMARILLO;
    linea(60);
    int pad = (58 - static_cast<int>(texto.size())) / 2;
    std::cout << "│";
    for (int i = 0; i < pad; ++i) std::cout << " ";
    std::cout << texto;
    int rest = 58 - pad - static_cast<int>(texto.size());
    for (int i = 0; i < rest; ++i) std::cout << " ";
    std::cout << "│\n";
    linea(60);
    std::cout << Color::RESET << "\n";
}

const char* VistaConsola::bgColor(ColorCarta c) {
    switch (c) {
        case ColorCarta::ROJO:     return Color::BG_ROJO;
        case ColorCarta::VERDE:    return Color::BG_VERDE;
        case ColorCarta::AZUL:     return Color::BG_AZUL;
        case ColorCarta::AMARILLO: return Color::BG_AMARILLO;
        case ColorCarta::ROSA:     return Color::BG_ROSA;
        case ColorCarta::TURQUESA: return Color::BG_TURQUESA;
        case ColorCarta::NARANJA:  return Color::BG_NARANJA;
        case ColorCarta::VIOLETA:  return Color::BG_VIOLETA;
        case ColorCarta::NEGRO:    return Color::BG_NEGRO;
        default:                   return Color::BG_NEGRO;
    }
}

const char* VistaConsola::fgColor(ColorCarta c) {
    switch (c) {
        case ColorCarta::ROJO:     return Color::ROJO;
        case ColorCarta::VERDE:    return Color::VERDE;
        case ColorCarta::AZUL:     return Color::AZUL;
        case ColorCarta::AMARILLO: return Color::AMARILLO;
        case ColorCarta::ROSA:     return Color::ROSA;
        case ColorCarta::TURQUESA: return Color::TURQUESA;
        case ColorCarta::NARANJA:  return Color::NARANJA;
        case ColorCarta::VIOLETA:  return Color::VIOLETA;
        case ColorCarta::NEGRO:    return Color::NEGRO;
        default:                   return Color::BLANCO;
    }
}

void VistaConsola::dibujarCarta(const Carta* c) {
    if (!c) {
        // Carta reversa (oculta)
        std::cout << Color::BG_AZUL << Color::BLANCO;
        std::cout << "╔═══════╗\n";
        std::cout << "║░░░░░░░║\n";
        std::cout << "║░ UNO ░║\n";
        std::cout << "║░░░░░░░║\n";
        std::cout << "╚═══════╝" << Color::RESET << "\n";
        return;
    }

    const char* bg  = bgColor(c->getColor());
    const char* fg  = (c->getColor() == ColorCarta::NEGRO ||
                       c->getColor() == ColorCarta::AZUL)
                      ? Color::BLANCO : Color::NEGRO;
    std::string etq = c->getEtiqueta();
    std::string col = colorNombre(c->getColor()).substr(0, 1); // inicial del color pq aja ya no cabe

    auto centrar = [](const std::string& s, int ancho) -> std::string {
        int pad = (ancho - static_cast<int>(s.size())) / 2;
        std::string res(pad, ' ');
        res += s;
        while (static_cast<int>(res.size()) < ancho) res += ' ';
        return res;
    };

    std::string etqC = centrar(etq, 5);

    std::cout << bg << fg << Color::NEGRITA;
    std::cout << "╔═══════╗\n";
    std::cout << "║" << col << "      ║\n";
    std::cout << "║ " << etqC << " ║\n";
    std::cout << "║       ║\n";
    std::cout << "║ " << etqC << " ║\n";
    std::cout << "║      " << col << "║\n";
    std::cout << "╚═══════╝" << Color::RESET << "\n";
}

// dibuja cartas horizontalmente una al lado de la otra
void VistaConsola::dibujarCartasHorizontal(const ListaCartas* lista, int inicio, int fin) {
    if (!lista) return;
    const int FILAS = 7;
    const int MAX_CARTAS = fin - inicio;
    if (MAX_CARTAS <= 0) return;

    struct LineasCarta {
        std::string filas[7];
    };

    LineasCarta* buffer = new LineasCarta[MAX_CARTAS];

    for (int ci = 0; ci < MAX_CARTAS; ++ci) {
        int idx = inicio + ci;
        const Carta* c = lista->obtener(idx);
        if (!c) {
            for (int f = 0; f < FILAS; ++f)
                buffer[ci].filas[f] = "         ";
            continue;
        }

        const char* bg  = bgColor(c->getColor());
        const char* fg  = (c->getColor() == ColorCarta::NEGRO ||
                           c->getColor() == ColorCarta::AZUL)
                          ? Color::BLANCO : Color::NEGRO;
        std::string etq = c->getEtiqueta();
        std::string col = colorNombre(c->getColor()).substr(0, 1);

        auto centrar = [](const std::string& s, int ancho) -> std::string {
            int pad = (ancho - static_cast<int>(s.size())) / 2;
            std::string res(pad, ' ');
            res += s;
            while (static_cast<int>(res.size()) < ancho) res += ' ';
            return res;
        };
        std::string etqC = centrar(etq, 5);

        buffer[ci].filas[0] = std::string(bg) + fg + Color::NEGRITA + "╔═══════╗" + Color::RESET;
        buffer[ci].filas[1] = std::string(bg) + fg + Color::NEGRITA + "║" + col + "      ║" + Color::RESET;
        buffer[ci].filas[2] = std::string(bg) + fg + Color::NEGRITA + "║ " + etqC + " ║" + Color::RESET;
        buffer[ci].filas[3] = std::string(bg) + fg + Color::NEGRITA + "║       ║" + Color::RESET;
        buffer[ci].filas[4] = std::string(bg) + fg + Color::NEGRITA + "║ " + etqC + " ║" + Color::RESET;
        buffer[ci].filas[5] = std::string(bg) + fg + Color::NEGRITA + "║      " + col + "║" + Color::RESET;
        buffer[ci].filas[6] = std::string(bg) + fg + Color::NEGRITA + "╚═══════╝" + Color::RESET;
    }

    for (int f = 0; f < FILAS; ++f) {
        for (int ci = 0; ci < MAX_CARTAS; ++ci) {
            std::cout << buffer[ci].filas[f] << " ";
        }
        std::cout << "\n";
    }

    delete[] buffer;
}

//mostrar mano completa de un jugador
void VistaConsola::mostrarMano(const ListaCartas* lista, const std::string& nombre) {
    if (!lista) return;
    std::cout << "\n" << Color::NEGRITA << Color::AMARILLO
              << "   Mano de " << nombre << " ["
              << lista->tamanio() << " cartas]"
              << Color::RESET << "\n";
    linea(60);

    const int GRUPO = 8;
    int total = lista->tamanio();
    for (int i = 0; i < total; i += GRUPO) {
        int fin = (i + GRUPO < total) ? i + GRUPO : total;

        std::cout << "";
        for (int j = i; j < fin; ++j) {
            std::cout << std::setw(9) << std::left << ("[" + std::to_string(j) + "]") << " ";
        }
        std::cout << "\n";
        dibujarCartasHorizontal(lista, i, fin);
    }
}

void VistaConsola::mostrarMenuPrincipal() {
    limpiarPantalla();
    std::cout << "\n";
    std::cout << Color::AMARILLO << " ---  VIDEOJUEGO UNO / UNO FLIP ---\n" << Color::RESET;
    std::cout << Color::AZUL << "       BIENVENID@S\n" << Color::RESET;
    std::cout << Color::TURQUESA<< "    Practica 1 EDD PS 2026 \n" << Color::RESET;
    std::cout << Color::AZUL<< "     by: kik3.h\n" << Color::RESET;
    std::cout << "\n";
    linea(50);
    std::cout << Color::AMARILLO << "1." << Color::RESET << " Nueva Partida\n";
    std::cout << Color::AMARILLO << "2." << Color::RESET << " Configurar Reglas\n";
    std::cout << Color::AMARILLO << "3." << Color::RESET << " Demo de Cartas\n";
    std::cout << Color::AMARILLO << "4." << Color::RESET << " Cargar Reglas desde Archivo\n";
    std::cout << Color::ROJO     << "0." << Color::RESET << " Salir\n";
    linea(50);
    std::cout << "  Selecciona una opcion: ";
}

void VistaConsola::mostrarMenuReglas(const Reglas& r) {
    limpiarPantalla();
    titulo("CONFIGURACION DE REGLAS");
    r.mostrar();
    std::cout << "\n";
    std::cout << Color::AMARILLO << "1." << Color::RESET << " Alternar Acumulacion\n";
    std::cout << Color::AMARILLO << "2." << Color::RESET << " Alternar Reto +4\n";
    std::cout << Color::AMARILLO << "3." << Color::RESET << " Alternar Modo Robo (A/B)\n";
    std::cout << Color::AMARILLO << "4." << Color::RESET << " Alternar Grito UNO\n";
    std::cout << Color::AMARILLO << "5." << Color::RESET << " Alternar Ganar con Negra\n";
    std::cout << Color::AMARILLO << "6." << Color::RESET << " Alternar UNO Flip\n";
    std::cout << Color::AMARILLO << "7." << Color::RESET << " Guardar Reglas en Archivo\n";
    std::cout << Color::ROJO     << "0." << Color::RESET << " Volver\n";
    std::cout << "\n  Selecciona una opcion: ";
}

void VistaConsola::mostrarMenuTurno(const Jugador* j, int turno) {
    std::cout << "\n" << Color::NEGRITA << Color::VERDE
              << "  ┌─ TURNO # " << turno << " ── " << j->getNombre()
              << " [" << j->cantidadCartas() << " cartas] ─┐"
              << Color::RESET << "\n";
    std::cout << Color::AMARILLO << "(0-N)" << Color::RESET << " Jugar carta por indice\n";
    std::cout << Color::AMARILLO << "(R)" << Color::RESET << " Robar carta\n";
    std::cout << Color::AMARILLO << "(U)" << Color::RESET << " Gritar UNO!\n";
    std::cout << Color::AMARILLO << "(V)" << Color::RESET << " Ver mi mano\n";
    std::cout << Color::AMARILLO << "(S)" << Color::RESET << " Salir de la partida\n";
    if (j->cantidadCartas() == 1)
        std::cout << "  " << Color::ROJO << Color::NEGRITA << "  ¡tienes solo 1 carta! ¡Grita UNO!\n" << Color::RESET;
    std::cout << "Ingresa tu opcion: ";
}

// mesa de Juego
void VistaConsola::mostrarMesa(const EstadoJuego& estado,
                                const Jugador*    jugadores[],
                                int               nJugadores,
                                int               idxActual,
                                int               cartasMazo,
                                const Carta*      cimaPila) {
    limpiarPantalla();

    std::cout << Color::NEGRITA << Color::TURQUESA
              << "  ══ UNO ══  Turno #" << estado.turnoActual
              << "  Lado: " << (estado.ladoActual == LadoMazo::CLARO ? "  CLARO" : "  OSCURO")
              << "  Direccion: " << (estado.direccionNormal ? "Hacia la derecha" : "Hacia la izquierda")
              << Color::RESET << "\n";
    linea(60);

    std::cout << "\n  " << Color::NEGRITA << Color::BLANCO
              << " MAZO (" << cartasMazo << ")      DESCARTADAS\n" << Color::RESET;
// aca como mostrar las cartas aun por obtener o robar
    auto linMazo = [](int f) -> std::string {
        std::string bg = std::string(Color::BG_AZUL) + Color::BLANCO + Color::NEGRITA;
        std::string reset = Color::RESET;
        switch (f) {
            case 0: return bg + "╔════════╗" + reset;
            case 1: return bg + "║░░░░░░░░║" + reset;
            case 2: return bg + "║░ UNO ░░║" + reset;
            case 3: return bg + "║░ DISP░░║" + reset;
            case 4: return bg + "║░░░░░░░░║" + reset;
            case 5: return bg + "║░░░░░░░░║" + reset;
            case 6: return bg + "╚════════╝" + reset;
            default: return "         ";
        }
    };
//el como mostrar la carta descartada 
    auto linDescarte = [&](int f) -> std::string {
        if (!cimaPila) return "         ";
        const char* bg = bgColor(cimaPila->getColor());
        const char* fg = (cimaPila->getColor() == ColorCarta::NEGRO ||
                          cimaPila->getColor() == ColorCarta::AZUL)
                         ? Color::BLANCO : Color::NEGRO;
        std::string etq = cimaPila->getEtiqueta();
        std::string col = colorNombre(cimaPila->getColor()).substr(0, 1);
        auto centrar = [](const std::string& s, int ancho) -> std::string {
            int pad = (ancho - static_cast<int>(s.size())) / 2;
            std::string res(pad, ' ');
            res += s;
            while (static_cast<int>(res.size()) < ancho) res += ' ';
            return res;
        };
        std::string etqC = centrar(etq, 5);
        std::string r = std::string(Color::RESET);
        std::string b = std::string(bg) + fg + Color::NEGRITA;
        switch (f) {
            case 0: return b + "╔═══════╗" + r;
            case 1: return b + "║" + col + "      ║" + r;
            case 2: return b + "║ " + etqC + " ║" + r;
            case 3: return b + "║       ║" + r;
            case 4: return b + "║ " + etqC + " ║" + r;
            case 5: return b + "║      " + col + "║" + r;
            case 6: return b + "╚═══════╝" + r;
            default: return "         ";
        }
    };

    for (int f = 0; f < 7; ++f) {
        std::cout << "  " << linMazo(f) << "    " << linDescarte(f) << "\n";
    }

    std::cout << "\n  Color en juego: " << fgColor(estado.colorActual) << Color::NEGRITA
              << colorNombre(estado.colorActual) << Color::RESET << "\n";
    if (estado.acumuladoRobo > 0)
        std::cout << "  " << Color::ROJO << Color::NEGRITA
                  << "  Robo acumulado: +" << estado.acumuladoRobo << Color::RESET << "\n";

    linea(60);
    //saber quiene sta en el turno actual
    std::cout << Color::NEGRITA << "  JUGADORES:\n" << Color::RESET;
    for (int i = 0; i < nJugadores; ++i) {
        if (!jugadores[i] || jugadores[i]->estaEliminado()) continue;
        bool esActual = (i == idxActual);
        std::cout << (esActual ? Color::VERDE : Color::DIM)
                  << Color::NEGRITA
                  << "  " << (esActual ? "-> " : "  ")
                  << jugadores[i]->getNombre()
                  << " [" << jugadores[i]->cantidadCartas() << " cartas]"
                  << (jugadores[i]->getGritoUNO() ? " ! UNO !" : "")
                  << (jugadores[i]->getTieneEscudo() ? " Tiene Escudo " : "")
                  << Color::RESET << "\n";
    }
    linea(60);
}
//pa saber cuando gritar uno
void VistaConsola::mensajeUNO(const std::string& nombre) {
    std::cout << "\n" << Color::AMARILLO << Color::NEGRITA
              << "   ¡" << nombre << " grito UNO! \n" << Color::RESET;
}

void VistaConsola::mensajeGanador(const std::string& nombre) {
    limpiarPantalla();
    titulo("¡TENEMOS UN GANADOR!");
    std::cout << Color::AMARILLO << Color::NEGRITA
              << "\n  Xx  " << nombre << "  gano la partida!  xX\n\n"
              << Color::RESET;
}

void VistaConsola::mensajePenalizacion(const std::string& nombre, int cartas) {
    std::cout << Color::ROJO
              << "  X  " << nombre << " roba " << cartas << " carta(s) de penalización.\n"
              << Color::RESET;
}

void VistaConsola::mensajeTurno(const std::string& nombre, int turno) {
    std::cout << Color::VERDE
              << "\n  ── Turno #" << turno << ": " << nombre << " ──\n"
              << Color::RESET;
}

void VistaConsola::mensajeError(const std::string& msg) {
    std::cout << Color::ROJO << "  X " << msg << Color::RESET << "\n";
}

void VistaConsola::mensajeFlip(LadoMazo nuevoLado) {
    if (nuevoLado == LadoMazo::OSCURO)
        std::cout << Color::VIOLETA << Color::NEGRITA
                  << "\n  ↕  ¡FLIP! El mazo cambia al LADO OSCURO \n" << Color::RESET;
    else
        std::cout << Color::AMARILLO << Color::NEGRITA
                  << "\n  ↕  ¡FLIP! El mazo vuelve al LADO CLARO \n" << Color::RESET;
}

//  Demo de Cartas para pruebas
void VistaConsola::demoCartas() {
    limpiarPantalla();
    titulo("DEMO DE CARTAS UNO");

    CartaNumero cn_rojo_7 (ColorCarta::ROJO,     7);
    CartaNumero cn_azul_3 (ColorCarta::AZUL,     3);
    CartaNumero cn_verde_0(ColorCarta::VERDE,     0);
    CartaNumero cn_amarillo_9(ColorCarta::AMARILLO, 9);
    CartaAccion ca_skip   (ColorCarta::ROJO,     AccionCarta::SKIP);
    CartaAccion ca_reverse(ColorCarta::VERDE,    AccionCarta::REVERSE);
    CartaAccion ca_mas2   (ColorCarta::AZUL,     AccionCarta::MAS_DOS);
    CartaComodin cw_color (false);
    CartaComodin cw_mas4  (true);
    CartaFlip    cf_flip  (ColorCarta::ROJO);
    CartaRobaColor crc    (ColorCarta::AMARILLO);
    CartaEscudo    cesc   (ColorCarta::VIOLETA);
    CartaNumero cn_rosa_5 (ColorCarta::ROSA,     5, LadoMazo::OSCURO);
    CartaAccion ca_skip_todos(ColorCarta::TURQUESA, AccionCarta::SKIP_TODOS, LadoMazo::OSCURO);

    ListaCartas lista;
    lista.agregar(&cn_rojo_7);
    lista.agregar(&cn_azul_3);
    lista.agregar(&cn_verde_0);
    lista.agregar(&cn_amarillo_9);

    std::cout << Color::NEGRITA << "  ── Cartas Numero ──\n" << Color::RESET;
    std::cout << "  [0]       [1]       [2]       [3]\n";
    dibujarCartasHorizontal(&lista, 0, 4);

    // Acciones
    ListaCartas lista2;
    lista2.agregar(&ca_skip);
    lista2.agregar(&ca_reverse);
    lista2.agregar(&ca_mas2);
    lista2.agregar(&cw_color);
    lista2.agregar(&cw_mas4);
    std::cout << "\n" << Color::NEGRITA << "  ── Cartas Accion y Comodin ──\n" << Color::RESET;
    std::cout << "  [SKIP]     [REV]     [+2]      [CAMB]     [+4]\n";
    dibujarCartasHorizontal(&lista2, 0, 5);

    // Especiales
    ListaCartas lista3;
    lista3.agregar(&cf_flip);
    lista3.agregar(&crc);
    lista3.agregar(&cesc);
    lista3.agregar(&cn_rosa_5);
    lista3.agregar(&ca_skip_todos);
    std::cout << "\n" << Color::NEGRITA << "  ── Flip / Personalizadas / Lado Oscuro ──\n" << Color::RESET;
    std::cout << "  [FLIP]    [ROBC]      [ESCUD]     [Rosa5]   [SKIP!]\n";
    dibujarCartasHorizontal(&lista3, 0, 5);

    std::cout << "\n";
    linea(60);

    lista.limpiar();
    lista2.limpiar();
    lista3.limpiar();

    pausar();
}