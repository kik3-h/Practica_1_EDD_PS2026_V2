#include "../include/Reglas.h"
#include "../include/Colores.h"
#include <iostream>

void Reglas::mostrar() const {
    auto yn = [](bool v) -> std::string {
        return v ? (std::string(Color::VERDE) + "SI" + Color::RESET)
                 : (std::string(Color::ROJO)  + "NO" + Color::RESET);
    };
    std::cout << Color::NEGRITA << "  Reglas actuales:\n" << Color::RESET;
    std::cout << "  1. Acumulación (+2 o +4): " << yn(acumulacion)     << "\n";
    std::cout << "  2. Reto del +4:         " << yn(retoPlus4)       << "\n";
    std::cout << "  3. Modo robo B (hasta poder jugar): " << yn(modoRoboB) << "\n";
    std::cout << "  4. Grito UNO:           " << yn(gritoUNO)        << "\n";
    std::cout << "  5. Ganar con negra:     " << yn(ganarConNegra)   << "\n";
    std::cout << "  6. UNO Flip activado:   " << yn(unoFlipActivado) << "\n";
}
