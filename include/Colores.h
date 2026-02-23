#pragma once

// Códigos ANSI para colores de consola


namespace Color {

    constexpr const char* RESET   = "\033[0m";
    constexpr const char* NEGRO   = "\033[30m";
    constexpr const char* ROJO    = "\033[31m";
    constexpr const char* VERDE   = "\033[32m";
    constexpr const char* AMARILLO= "\033[33m";
    constexpr const char* AZUL    = "\033[34m";
    constexpr const char* VIOLETA = "\033[35m";
    constexpr const char* TURQUESA= "\033[36m";
    constexpr const char* BLANCO  = "\033[37m";
    constexpr const char* ROSA    = "\033[95m";
    constexpr const char* NARANJA = "\033[91m";
    constexpr const char* BG_ROJO    = "\033[41m";
    constexpr const char* BG_VERDE   = "\033[42m";
    constexpr const char* BG_AMARILLO= "\033[43m";
    constexpr const char* BG_AZUL    = "\033[44m";
    constexpr const char* BG_VIOLETA = "\033[45m";
    constexpr const char* BG_TURQUESA= "\033[46m";
    constexpr const char* BG_NEGRO   = "\033[40m";
    constexpr const char* BG_ROSA    = "\033[105m";
    constexpr const char* BG_NARANJA = "\033[101m";
    constexpr const char* NEGRITA  = "\033[1m";
    constexpr const char* DIM      = "\033[2m";
}