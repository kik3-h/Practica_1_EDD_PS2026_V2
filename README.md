# Practica_1_EDD_PS2026_V2

**Universidad San Carlos de Guatemala – Centro Universitario de Occidente**  
**Laboratorio de Estructura de Datos – Ing. en Ciencias y Sistemas**  
**Docente: Ing. Mario Moisés Ramírez Tobar | Primer Semestre – 2026**

Practica 1 estructura de datos del primer semestre 2026 version 2 (en consola)

debido a problemas en qt decidi cambiarme a hacerlo en consola

Proyecto de la Primera Práctica de Estructura de Datos.
Obtuve de calificacion 78%
by: Instagram: kik3.h

## Requisitos

- Fedora 43
- g++ 15.2.1
- VS Code
- `make`, `cmake` (opcional)

## Compilación

make

## Ejecutar

make run

## Ejecutar pruebas

make test

## Limpiar

make clean

## Descripción

Implementación del juego de cartas **UNO** (con variante **UNO Flip**) en C++, ejecutándose en consola (CLI).  
El proyecto demuestra el uso de estructuras de datos implementadas **desde cero**:

- `Stack<T>` (mazo/pila de descarte)
- Lista circular doblemente enlazada (orden de turnos)
- Lista enlazada simple (mano de jugadores)

---

## Estructura del Proyecto

```
UNO_EDD_2026/
├── bin/                  # Ejecutables generados
├── build/                # Archivos CMake/objetos
├── include/              # Headers (.h)
│   ├── Colores.h         # Códigos ANSI
│   ├── Stack.h           # TAD Pila genérico
│   ├── Enums.h           # Enumeraciones globales
│   ├── Carta.h           # Clase abstracta base
│   ├── CartaNumero.h
│   ├── CartaAccion.h
│   ├── CartaComodin.h
│   ├── CartaFlip.h
│   ├── CartaPersonalizada.h
│   ├── ListaCartas.h     # Lista simple (mano jugador)
│   ├── ListaCircular.h   # Lista circular doble (turnos)
│   ├── Jugador.h
│   ├── Mazo.h
│   ├── Reglas.h
│   ├── EstadoJuego.h
│   └── VistaConsola.h
├── src/                  # Implementaciones (.cpp)
│   ├── main.cpp
│   ├── CartaNumero.cpp
│   ├── CartaAccion.cpp
│   ├── CartaComodin.cpp
│   ├── CartaFlip.cpp
│   ├── CartaPersonalizada.cpp
│   ├── Jugador.cpp
│   ├── Mazo.cpp
│   ├── Reglas.cpp
│   ├── ListaCircular.cpp
│   └── VistaConsola.cpp
├── tests/
│   └── test_stack.cpp    # Pruebas unitarias
├── docs/
│   ├── ManualUsuario.md
│   └── AnalisisComplejidad.md
├── CMakeLists.txt
├── CmakeScript.sh
├── Makefile
└── README.md
```

---

## Cartas Personalizadas

| Carta               | Efecto                                                                                  |
| ------------------- | --------------------------------------------------------------------------------------- |
| **Roba Color (RC)** | El siguiente jugador pierde todas las cartas del color actual en su mano                |
| **Escudo (ESC)**    | Activa protección; anula el próximo efecto de robo (+2/+4/+6) y lo devuelve al lanzador |

---

## Reglas Configurables

| Regla           | Descripción                                                             |
| --------------- | ----------------------------------------------------------------------- |
| Acumulación     | Apilar +2 sobre +2, +4 sobre +4                                         |
| Reto del +4     | El afectado puede retar si el lanzador tenía opción de jugar otra carta |
| Modo Robo B     | Robar hasta poder jugar (en vez de solo 1 carta)                        |
| Grito UNO       | Obligatorio gritar "UNO" al quedar con 1 carta                          |
| Ganar con Negra | Permitir/prohibir ganar con carta de comodín                            |
| UNO Flip        | Activa el lado oscuro con colores y reglas especiales                   |

---

## Autores

Enrique Hernandez
23/02/2025
ig: kik3.h
