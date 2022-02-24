#include "Auto.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

Auto::Auto(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::DIM_AUTO.x;
    espacio.height = Config::DIM_AUTO.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite("auto1");
    vida = 0;
    velocidad = {3.0f, 3.0f};
    tipoClase = CLASE_AUTO;
    nombre = "Auto";

    generarFisicasIniciales();
}

Auto::~Auto()
{
    // Borrar las balas
}

void Auto::actualizar(float dt)
{
    if (habilitarProcesadoFisicas == true)
    {
        sincronizarObjetoConFisicas();
        return;
    }

    posicion.x += std::sin(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.x;
    posicion.y -= std::cos(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.y;

    sincronizarFisicasConObjeto();
}

void Auto::dibujar()
{
    Objeto::dibujar();
    for (auto bala : balas)
        bala->dibujar();
    // Debug fisicas
    fcuerpo->dibujar();
}

void Auto::generarFisicasIniciales()
{
    fcuerpo = new FisicasCuerpo(this, FCUERPO_DEFECTO);
    if (fcuerpo == nullptr)
        return;
    fcuerpo->agregarColisionador(FMaterial(80.f, 1.0f, 0.0f), FGRUPO_AUTO, (FGrupoColision) (FGRUPO_AUTO | FGRUPO_JUGADOR | FGRUPO_OBSTACULO | FGRUPO_BALA));
}

void Auto::disparar()
{
    std::vector<Vector2> vertices = Util::retVerticesRectangulo(espacio, (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo);
    Vector2 arribaIzquierda = vertices.at(0);
    Vector2 arribaDerecha = vertices.at(1);
    Vector2 p = {arribaIzquierda.x, arribaIzquierda.y};
    Bala *nueva = new Bala(p);
    nueva->angulo = angulo;
    balas.push_back(nueva);
}

