# Manual de Usuario – UNO EDD 2026

## Inicio Rápido

Al ejecutar `./bin/Practica1_EDD_Enrique_Tebalan` verás el menú principal con las siguientes opciones:
con los comandos make run

```
[1] Nueva Partida
[2] Configurar Reglas
[3] Demo de Cartas
[4] Cargar Reglas desde Archivo
[0] Salir
```

---

## Nueva Partida

1. Selecciona **[1] Nueva Partida**
2. Ingresa el número de jugadores (mínimo 2)
3. Ingresa el nombre de cada jugador
4. El juego reparte 7 cartas a cada jugador y coloca una carta inicial en el descarte

### Durante el Turno

```
[0-N]  Jugar carta por índice   → escribe el número de la carta en tu mano
[ R ]  Robar carta              → escribe "R"
[ U ]  Gritar UNO!              → escribe "U" cuando te quede 1 carta
[ V ]  Ver mi mano              → escribe "V" para revisar tus cartas
```

### Descripción de la Mesa

```
     MAZO (42)          DESCARTE
  ╔═══════╗    ╔═══════╗
  ║░░░░░░░║    ║R  +2  ║   ← carta en el descarte
  ║░ UNO ░║    ║  +2   ║
  ║░░░░░░░║    ║       ║
  ╚═══════╝    ╚═══════╝

  Color en juego: Rojo
  ── JUGADORES:
  ▶ Ana    [6 cartas]    ← jugador activo
    Bob    [7 cartas]
    Carlos [7 cartas]
```

---

## Representación de Cartas

Cada carta se muestra con un borde de 9×7 caracteres:

```
  ╔═══════╗   ╔═══════╗   ╔═══════╗   ╔═══════╗
  ║R      ║   ║V  SKP ║   ║N  +4  ║   ║A FLIP ║
  ║   7   ║   ║  SKP  ║   ║  +4   ║   ║ FLIP  ║
  ║       ║   ║       ║   ║       ║   ║       ║
  ║   7   ║   ║  SKP  ║   ║  +4   ║   ║ FLIP  ║
  ║      R║   ║      V║   ║      N║   ║      A║
  ╚═══════╝   ╚═══════╝   ╚═══════╝   ╚═══════╝
  Rojo 7     Verde SKP   Negro +4    Azul FLIP
```

**Colores ANSI:**

- Rojo, Verde, Azul, Amarillo → lado Claro
- Rosa, Turquesa, Naranja, Violeta → lado Oscuro
- Negro → comodín

---

## Reglas del Juego

### Reglas base

- Juega una carta que coincida en **color** o **número/símbolo** con la cima
- Si no puedes jugar, **roba** (modo A: 1 carta; modo B: hasta poder)
- El primero en quedarse **sin cartas** gana

### Efectos de cartas

| Carta   | Efecto                                                |
| ------- | ----------------------------------------------------- |
| +2      | Siguiente jugador roba 2 y pierde turno               |
| +4      | Siguiente roba 4, tú eliges color                     |
| Skip    | Saltar siguiente turno                                |
| Reverse | Invertir dirección (con 2 jugadores = Skip)           |
| Comodín | Eliges el nuevo color                                 |
| Flip    | Voltear mazo a lado oscuro/claro                      |
| RC      | El siguiente pierde todas sus cartas del color actual |
| Escudo  | Protege del próximo efecto de robo                    |

### Comodín +4 – Reto

Si la regla **Reto del +4** está activa:

- El afectado puede escribir **"retar"** al recibir un +4
- Si el lanzador SÍ tenía otra opción: el lanzador roba 4
- Si el lanzador NO tenía opción: el que retó roba 6 (+4 original +2 penalización)

### Grito UNO

- Al quedarte con 1 carta, debes escribir **"U"** antes de terminar tu turno
- Si no lo haces y alguien lo reporta: robas 2 cartas de penalización

---

## UNO Flip (Lado Oscuro)

Al activar UNO Flip en la configuración:

| Característica | Lado Claro                  | Lado Oscuro                        |
| -------------- | --------------------------- | ---------------------------------- |
| Robo           | +2                          | +3 / +6 multicolor                 |
| Skip           | Saltar siguiente            | Saltar a todos (relanzador vuelve) |
| Colores        | Rojo, Verde, Azul, Amarillo | Rosa, Turquesa, Naranja, Violeta   |

Cuando se juega una carta **FLIP**, se voltea el mazo y todos los jugadores giran sus cartas.

---

## Configuración de Reglas

Selecciona **[2] Configurar Reglas** para ver y activar/desactivar cada flag.
Las reglas se pueden guardar en `reglas.txt` y cargar en la siguiente sesión con la opción **[4]**.
