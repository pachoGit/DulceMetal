#include "Motor.hpp"
#include "Enemigo.hpp"
#include "Convertir.hpp"

#include <string>

Enemigo::Enemigo(Vector2 _posicion, TipoAuto _tipo, unsigned _ID) : Auto(_posicion, _tipo, _ID)
{
    tipoClase = CLASE_ENEMIGO;
    tiempoDisparo = GetTime();
    if (fcuerpo != nullptr)
        Motor::retMotor().retGestorFisicas()->destruirFCuerpo(fcuerpo);
    fcuerpo = Motor::retMotor().retGestorFisicas()->crearFCuerpo(this,
                                                                 FCUERPO_DEFECTO,
                                                                 FMaterial(80.f, 0.0f, 0.0f),
                                                                 FGRUPO_ENEMIGO,
                                                                 (FGrupoColision) (FGRUPO_AUTO | FGRUPO_ENEMIGO | FGRUPO_JUGADOR | FGRUPO_OBSTACULO | FGRUPO_BALA | FGRUPO_EQUIPAMIENTO));
    nombre = "Enemigo";
    estadoAtaque = E_NADA;

    rango.x = espacio.x;
    rango.y = espacio.y;
    rango.width = Config::RANGO_VISION_ENEMIGO;
    rango.height = Config::RANGO_VISION_ENEMIGO;
}

Enemigo::~Enemigo() {}

void Enemigo::actualizar(float dt)
{
    Auto::actualizar(dt);
    // Disparar bot
    int resultado = GetTime() - tiempoDisparo;
    
    if (resultado > 2)
    {
        //disparar();
        tiempoDisparo = GetTime();
    }
    rango.x = posicion.x;
    rango.y = posicion.y;
}

void Enemigo::dibujar()
{
    Rectangle vrango = Convertir::MetrosEnPixeles(rango);
    //DrawRectanglePro(vrango, {vrango.width * 0.5f, vrango.height * 0.5f}, 0.f, RED);
    Auto::dibujar();
    // Dibujar el numero de idenficacion del auto
    std::string identificador = std::to_string(ID);
    DrawText(identificador.c_str(), Convertir::MetrosEnPixeles(espacio.x), Convertir::MetrosEnPixeles(espacio.y), 15, BLACK);

    if (!inventario->estaVacio())
    {
        std::string nbalas = std::to_string(inventario->retActual()->cantidad);
        Vector2 ptexto = Convertir::MetrosEnPixeles((Vector2) {posicion.x, posicion.y + 1});
        DrawText(nbalas.c_str(), ptexto.x, ptexto.y, 12, RED);
    }
}


