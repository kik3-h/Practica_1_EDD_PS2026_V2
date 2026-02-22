#pragma once
/**
  Flags configurables de las reglas del juego UNO
  Serializable a archivo de texto
 */
#include <string>
#include <fstream>
#include <iostream>

struct Reglas {
    bool acumulacion     = false; //  +2 sobre +2, +4 sobre +4
    bool retoPlus4       = false; // El afectado puede retar el +4
    bool modoRoboB       = false; // false=ModoA(1 carta), true=ModoB(hasta poder)
    bool gritoUNO        = true;  // Obligatorio gritar UNO
    bool ganarConNegra   = false; // Puede ganar con carta negra
    bool unoFlipActivado = false; // Activa la expansión UNO Flip

    //muestra las reglas actuales en consola
    void mostrar() const;

    //Serializa a archivo de texto simple
    bool guardar(const std::string& ruta) const {
        std::ofstream f(ruta);
        if (!f) return false;
        f << "acumulacion="     << acumulacion     << "\n"
          << "retoPlus4="       << retoPlus4       << "\n"
          << "modoRoboB="       << modoRoboB       << "\n"
          << "gritoUNO="        << gritoUNO        << "\n"
          << "ganarConNegra="   << ganarConNegra   << "\n"
          << "unoFlipActivado=" << unoFlipActivado << "\n";
        return true;
    }

    // Carga desde archivo de texto
    bool cargar(const std::string& ruta) {
        std::ifstream f(ruta);
        if (!f) return false;
        std::string linea;
        while (std::getline(f, linea)) {
            auto pos = linea.find('=');
            if (pos == std::string::npos) continue;
            std::string clave = linea.substr(0, pos);
            int val = std::stoi(linea.substr(pos + 1));
            if      (clave == "acumulacion")     acumulacion     = val;
            else if (clave == "retoPlus4")       retoPlus4       = val;
            else if (clave == "modoRoboB")       modoRoboB       = val;
            else if (clave == "gritoUNO")        gritoUNO        = val;
            else if (clave == "ganarConNegra")   ganarConNegra   = val;
            else if (clave == "unoFlipActivado") unoFlipActivado = val;
        }
        return true;
    }
};