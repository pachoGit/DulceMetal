#include "Objeto.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

#include <iostream>

Objeto::Objeto(Vector2 _posicion)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    espacio.width = Config::DIM_OBJETO.x;
    espacio.height = Config::DIM_OBJETO.y;
    posicion = _posicion;
    velocidad = {0.f, 0.f};
    sprite = nullptr;
    angulo = 0.f;
    visible = true;
    fcuerpo = nullptr;
    habilitarProcesadoFisicas = false;
    tipoClase = CLASE_BASE;
    nombre = "Objeto";
}

Objeto::~Objeto()
{
    if (sprite != nullptr)
        sprite = nullptr;
    if (fcuerpo != nullptr)
    {
        Motor::retMotor().retGestorFisicas()->destruirFCuerpo(fcuerpo);
        fcuerpo = nullptr;
    }
}

void Objeto::actualizar(float dt)
{
}

void Objeto::dibujar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;
    Rectangle vespacio = Convertir::MetrosEnPixeles(espacio);
    if (sprite != nullptr && visible)
        DrawTexturePro(sprite->textura, sprite->espacio, vespacio, (Vector2) {vespacio.width/2.f, vespacio.height/2.f}, angulo, RAYWHITE);
    //Util::DrawRectangleLinesPro(Util::arreglarPosicion(espacio), (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo, GREEN);
}

void Objeto::generarFisicasIniciales()
{
}

void Objeto::ingFCuerpo(FisicasCuerpo *_fcuerpo)
{
    if (fcuerpo != nullptr)
    {
        Motor::retMotor().retGestorFisicas()->destruirFCuerpo(fcuerpo);
        fcuerpo = nullptr;
    }
    fcuerpo = _fcuerpo;
    fcuerpo->limpiarFuerzas();
    fcuerpo->transformar(posicion, angulo);
}

void Objeto::sincronizarFisicasConObjeto()
{
    fcuerpo->transformar(posicion, angulo);
    fcuerpo->ingVelocidadLineal(velocidad);
}

void Objeto::sincronizarObjetoConFisicas()
{
    posicion = fcuerpo->retPosicion();
    angulo = fcuerpo->retAngulo();
    // TODO: Al actualizar la velocidad, logra malos resultados al jugador
    //velocidad = fcuerpo->retVelocidadLineal();
}

void Objeto::mostrar() const
{
    std::cout << "Objeto - P: (" << posicion.x << ", " << posicion.y << ") - A: " << angulo << std::endl;
}

