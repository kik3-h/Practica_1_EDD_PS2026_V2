/**
 Pruebas unitarias: Stack<T>, ListaCircular, conteo del mazo | Compilar y ejecutar:
 make test
 */
#include "../include/Stack.h"
#include "../include/ListaCircular.h"
#include "../include/Mazo.h"
#include "../include/Reglas.h"
#include "../include/Jugador.h"
#include <iostream>
#include <cassert> //permite verificar que una condicion logica sea verdadera durante la ejecucion del programa
#include <string>

#define OK   "\033[32m[OK]\033[0m "
#define FAIL "\033[31m[FAIL]\033[0m "
#define INFO "\033[33m[--]\033[0m "

static int pruebas_ok   = 0;
static int pruebas_fail = 0;

#define ASSERT(cond, msg) \
    if (!(cond)) { \
        std::cerr << FAIL << msg << " (linea " << __LINE__ << ")\n"; \
        ++pruebas_fail; \
    } else { \
        std::cout << OK << msg << "\n"; \
        ++pruebas_ok; \
    }

void test_stack_push_pop() {
    std::cout << INFO << "--- Stack<int>: push/pop/top ---\n";
    Stack<int> s;

    ASSERT(s.empty(), "pila vacia al inicio");
    ASSERT(s.size() == 0, "Tamanio 0 al inicio");

    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT(s.size() == 3,    "Tamanio 3 tras 3 push");
    ASSERT(s.top() == 30,    "top() == 30");
    ASSERT(!s.empty(),       "No vacia tras push");

    s.pop();
    ASSERT(s.top() == 20,    "top() == 20 tras pop");
    ASSERT(s.size() == 2,    "Tamanio 2 tras pop");

    s.pop();
    s.pop();
    ASSERT(s.empty(),        "Vacia tras 3 pops");
    ASSERT(s.size() == 0,    "Tamanio 0 tras vaciar");
}

void test_stack_underflow() {
    std::cout << INFO << "--- Stack<int>: excepción underflow ---\n";
    Stack<int> s;
    bool excepcion = false;
    try { s.pop(); }
    catch (const std::underflow_error&) { excepcion = true; }
    ASSERT(excepcion, "pop() en pila vacia lanza underflow_error");

    bool excepcion2 = false;
    try { s.top(); }
    catch (const std::underflow_error&) { excepcion2 = true; }
    ASSERT(excepcion2, "top() en pila vacia lanza underflow_error");
}

void test_stack_array_roundtrip() {
    std::cout << INFO << "--- Stack<int>: toArray/fromArray ---\n";
    Stack<int> s;
    for (int i = 0; i < 5; ++i) s.push(i * 10);  // 0,10,20,30,40

    int arr[5];
    s.toArray(arr);
    // cima es 40 indice 0 del arreglo
    ASSERT(arr[0] == 40, "arr[0] == 40 (cima)");
    ASSERT(arr[4] == 0,  "arr[4] == 0 (fondo)");

    s.fromArray(arr, 5);
    ASSERT(s.size() == 5, "fromArray restaura tamaño");
    ASSERT(s.top() == 0,  "fromArray: cima es arr[0] del origen = 0 (último push)");
}

// Tests ListaCircular
void test_lista_circular() {
    std::cout << INFO << "--- ListaCircular: insertar/siguiente ---\n";

    Jugador j1("Ana"), j2("Bob"), j3("Carlos");
    ListaCircular lc;

    ASSERT(lc.estaVacia(), "Lista circular vacia al inicio");

    lc.insertar(&j1);
    lc.insertar(&j2);
    lc.insertar(&j3);

    ASSERT(lc.tamanio() == 3, "Tamanio 3 tras insertar 3 jugadores");
    ASSERT(lc.getActual() == &j1, "Primer jugador es kike");

    lc.siguiente();
    ASSERT(lc.getActual() == &j2, "Siguiente es mario");

    lc.siguiente();
    ASSERT(lc.getActual() == &j3, "Siguiente es carlos");

    lc.siguiente();
    ASSERT(lc.getActual() == &j1, "Circular: vuelve a kike");
}

void test_lista_circular_invertir() {
    std::cout << INFO << "--- ListaCircular: invertir direccion ---\n";

    Jugador j1("A"), j2("B"), j3("C");
    ListaCircular lc;
    lc.insertar(&j1);
    lc.insertar(&j2);
    lc.insertar(&j3);

    lc.invertir();
    lc.siguiente();
    ASSERT(lc.getActual() == &j3, "Invertido: A -> C");

    lc.siguiente();
    ASSERT(lc.getActual() == &j2, "Invertido: C -> B");
}

void test_lista_circular_saltar() {
    std::cout << INFO << "--- ListaCircular: saltar (Skip) ---\n";

    Jugador j1("A"), j2("B"), j3("C"), j4("D");
    ListaCircular lc;
    lc.insertar(&j1);
    lc.insertar(&j2);
    lc.insertar(&j3);
    lc.insertar(&j4);

    lc.saltar(); 
    ASSERT(lc.getActual() == &j3, "Saltar salta a j3");
}

void test_lista_circular_eliminar() {
    std::cout << INFO << "--- ListaCircular: eliminarActual ---\n";

    Jugador j1("A"), j2("B"), j3("C");
    ListaCircular lc;
    lc.insertar(&j1);
    lc.insertar(&j2);
    lc.insertar(&j3);

    lc.siguiente(); 
    lc.eliminarActual(); 
    ASSERT(lc.tamanio() == 2, "Tamaño 2 tras eliminar");
    ASSERT(lc.getActual() == &j3, "Actual es C tras eliminar B");

    lc.siguiente();
    ASSERT(lc.getActual() == &j1, "Circular: C -> A");
}

// Tests Mazo 
void test_mazo_conteo() {
    std::cout << INFO << "--- Mazo: conteo de cartas ---\n";

    Reglas r;
    r.unoFlipActivado = false;

    Mazo m;
    m.construir(1, r);

    int total = m.cartasRestantes();
    ASSERT(total > 100, "Mazo con 1 deck tiene > 100 cartas");
    std::cout << "    Cartas en mazo (1 deck): " << total << "\n";

    Mazo m2;
    m2.construir(7, r); 
    int total2 = m2.cartasRestantes();
    ASSERT(total2 == total * 2, "7 jugadores = 2 mazos (doble de cartas)");
    std::cout << "    Cartas en mazo (2 decks): " << total2 << "\n";
}

void test_mazo_robar_descartar() {
    std::cout << INFO << "--- Mazo: robar y descartar ---\n";

    Reglas r;
    Mazo m;
    m.construir(2, r);

    int antes = m.cartasRestantes();
    Carta* c = m.robar();
    ASSERT(c != nullptr, "robar() retorna carta no nula");
    ASSERT(m.cartasRestantes() == antes - 1, "cartasRestantes disminuye tras robar");

    m.descartar(c);
    ASSERT(m.cartasDescartadas() == 1, "Descarte tiene 1 carta");
    ASSERT(m.cimaPila() == c, "cimaPila() == carta descartada");
}

void test_mazo_barajado_mantiene_conteo() {
    std::cout << INFO << "--- Mazo: barajar mantiene conteo ---\n";

    Reglas r;
    Mazo m;
    m.construir(3, r);
    int antes = m.cartasRestantes();
    m.barajar();
    ASSERT(m.cartasRestantes() == antes, "barajar() no pierde ni duplica cartas");
}

// Resumen
int main() {
    std::cout << "\033[1m\033[36m";
    std::cout << "║  Pruebas Unitarias de practica 1 del juego UNO EDD 2026        ║\n";
    std::cout << "\033[0m\n";

    test_stack_push_pop();
    test_stack_underflow();
    test_stack_array_roundtrip();
    test_lista_circular();
    test_lista_circular_invertir();
    test_lista_circular_saltar();
    test_lista_circular_eliminar();
    test_mazo_conteo();
    test_mazo_robar_descartar();
    test_mazo_barajado_mantiene_conteo();

    std::cout << "\n\033[1m";
    std::cout << "────────────────────────────────────────────\n";
    std::cout << "  Resultados: " << "\033[32m" << pruebas_ok << " OK\033[0m\033[1m  "
              << "\033[31m" << pruebas_fail << " FAIL\033[0m\n";
    std::cout << "────────────────────────────────────────────\n\033[0m\n";

    return pruebas_fail > 0 ? 1 : 0;
}
