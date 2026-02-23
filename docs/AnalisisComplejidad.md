# Análisis de Complejidad – PRACTICA 1 - UNO - EDD 2026

## Estructuras de Datos y Operaciones

### Stack<T> (Mazo / Pila de Descarte)

| Operación     | Complejidad | Justificación                          |
| ------------- | ----------- | -------------------------------------- |
| `push()`      | O(1)        | Inserta al inicio de la lista enlazada |
| `pop()`       | O(1)        | Elimina el nodo cima directamente      |
| `top()`       | O(1)        | Acceso al nodo cabeza                  |
| `size()`      | O(1)        | Contador mantenido internamente        |
| `toArray()`   | O(n)        | Recorre todos los nodos                |
| `fromArray()` | O(n)        | Push n elementos                       |

### ListaCircular (Turnos)

| Operación          | Complejidad | Justificación                   |
| ------------------ | ----------- | ------------------------------- |
| `insertar()`       | O(1)        | Con puntero anterior disponible |
| `siguiente()`      | O(1)        | Puntero directo                 |
| `saltar()`         | O(1)        | Dos llamadas a siguiente()      |
| `invertir()`       | O(1)        | Cambio de flag booleano         |
| `eliminarActual()` | O(1)        | Punteros dobles permiten O(1)   |

### ListaCartas (Mano del Jugador)

| Operación      | Complejidad | Justificación          |
| -------------- | ----------- | ---------------------- |
| `agregar()`    | O(n)        | Recorre hasta el final |
| `extraer(idx)` | O(n)        | Recorre hasta índice   |
| `obtener(idx)` | O(n)        | Recorre hasta índice   |

> Nota: Para la mano del jugador se usa lista enlazada simple por sencillez. En una versión
> optimizada se podría mantener un puntero al último nodo para `agregar()` en O(1).

---

## Algoritmo de Barajado: Fisher-Yates

```
void barajar():
    n = tamaño del mazo
    toArray(arr)            // O(n)
    for i = n-1 downto 1:  // O(n)
        j = rand() % (i+1)
        swap(arr[i], arr[j])
    fromArray(arr, n)       // O(n)
```

**Complejidad total: O(n)**  
**Espacio auxiliar: O(n)** (arreglo temporal)

El algoritmo garantiza una permutación aleatoria **uniforme**: cada una de las n! permutaciones posibles tiene exactamente la misma probabilidad de ocurrir.

---

## Construcción del Mazo

```
construir(n_jugadores, reglas):
    k = ((n_jugadores - 1) / 6 + 1)   // número de decks
    for i = 0..k-1:
        crearMazoClaro()               // O(108)
        if flip: crearMazoOscuro()     // O(~116)
    barajar()                          // O(n)
```

**Complejidad: O(k · c + k·c)** donde c ≈ 108-224 cartas por deck  
= O(k) ≈ O(n_jugadores / 6) · O(cartas por deck) = **O(n_jugadores)**

---

## Búsqueda de carta jugable en mano

```
primerCartaJugable(jugador, cartaCima):
    for i = 0..cantCartas-1:       // O(m) donde m = cartas en mano
        if carta[i].esJugable(cima): return i
    return -1
```

**Peor caso: O(m)** donde m es la cantidad de cartas en la mano (≤ ~20 en condiciones normales)

---

## Resumen General

| Operación clave              | Complejidad     |
| ---------------------------- | --------------- |
| Turno completo (jugar carta) | O(m)            |
| Robar carta                  | O(1) amortizado |
| Barajar                      | O(n)            |
| Construir mazos              | O(n_jugadores)  |
| Avanzar turno                | O(1)            |
| Detectar ganador             | O(1)            |
| Giro de dirección            | O(1)            |

La complejidad dominante del juego completo es **O(T · m)** donde T es el número de turnos y m el tamaño máximo de la mano de un jugador.
