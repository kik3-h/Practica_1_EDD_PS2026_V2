#pragma once // segun entiendo preprocesa la clase para que no se incluya mas de una vez
//durante la compilacion

 //esta es una clase abstracta base para todas las cartas UNO

#include "Enums.h"

struct EstadoJuego; // 

class Carta {
protected:
    ColorCarta  color_;
    TipoCarta   tipo_;
    AccionCarta accion_;
    LadoMazo    lado_;   // claro u oscuro uno flip

public:
    Carta(ColorCarta color, TipoCarta tipo,
        AccionCarta accion, LadoMazo lado = LadoMazo::CLARO)
          : color_(color), tipo_(tipo), accion_(accion), lado_(lado) {}

     virtual ~Carta() = default;

    //metodos virtuales puros que cada tipo de carta implementará según su lógica específica
    virtual void dibujar()                              const = 0;
    virtual bool esJugable(const Carta* cartaCima)      const = 0;
    virtual void aplicarEfecto(EstadoJuego& estado)     const = 0;
    virtual std::string getEtiqueta()                   const = 0;

    ColorCarta  getColor()  const { return color_; }
    TipoCarta   getTipo()   const { return tipo_; }
    AccionCarta getAccion() const { return accion_; }
    LadoMazo    getLado()   const { return lado_; }

    // Setter para comodin elige color al jugarse
     void setColor(ColorCarta c) { color_ = c; }
};
