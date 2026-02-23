#pragma once

 //Clase Jugador con su mano de cartas

#include "ListaCartas.h"
#include <string>

class Jugador {
private:
    std::string  nombre_;
    ListaCartas* mano_;
    bool         gritoUNO_;    
    bool         tieneEscudo_; 
    bool         eliminado_;

    
public:
    explicit Jugador(const std::string& nombre);
    ~Jugador();
    Jugador(const Jugador&)            = delete;
    Jugador& operator=(const Jugador&) = delete;

    void        recibirCarta(Carta* c);
    Carta*      jugarCarta(int idx);
    Carta*      verCarta(int idx)    const;
    int         cantidadCartas()     const;
    bool        sinCartas()          const;

    const std::string& getNombre()      const { return nombre_; }
    ListaCartas*       getMano()        const { return mano_; }
    bool               getGritoUNO()   const { return gritoUNO_; }
    bool               getTieneEscudo()const { return tieneEscudo_; }
    bool               estaEliminado() const { return eliminado_; }

    void setGritoUNO(bool v)    { gritoUNO_ = v; }
    void setEscudo(bool v)      { tieneEscudo_ = v; }
    void eliminar()             { eliminado_ = true; }
};