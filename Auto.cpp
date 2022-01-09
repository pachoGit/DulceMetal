#include "Auto.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"

Auto::Auto(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::auto_espacio.width;
    espacio.height = Config::auto_espacio.height;

    sprite = Motor::retMotor().retGestorSprites()->retSprite("auto1");
    vida = 0;
    velocidad = 60.f;
}

Auto::~Auto()
{
    // Borrar las balas
}

void Auto::actualizar(float dt)
{
    posicion.x += std::sin(angulo * DEG2RAD) * dt * velocidad;
    posicion.y -= std::cos(angulo * DEG2RAD) * dt * velocidad;
}

void Auto::dibujar()
{
    Objeto::dibujar();
    for (auto bala : balas)
        bala->dibujar();
}

void Auto::disparar()
{
    std::vector<Vector2> vertices = Util::retVerticesRectangulo(Util::arreglarPosicion(espacio), (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo);
    Vector2 arribaIzquierda = vertices.at(0);
    Vector2 arribaDerecha = vertices.at(1);
    Vector2 p = {arribaIzquierda.x, arribaIzquierda.y};
    Bala *nueva = new Bala(p);
    nueva->angulo = angulo;
    balas.push_back(nueva);
}
