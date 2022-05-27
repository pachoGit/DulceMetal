#include "Equipamiento.hpp"
#include "Motor.hpp"

Equipamiento::Equipamiento(Vector2 _posicion, TipoEquipamiento _tipo) : Objeto(_posicion)
{
    tipo = _tipo;
    auto data = dataEquipamiento[_tipo];
    tipoBala = data.tipoBala;
    ganancia = data.ganancia;
    fcuerpo = Motor::retMotor().retGestorFisicas()->crearFCuerpo(this,
                                                                 FCUERPO_ESTATICO,
                                                                 FMaterial(1.f, 1.0f, 1.0f),
                                                                 FGRUPO_EQUIPAMIENTO,
                                                                 (FGrupoColision) (FGRUPO_AUTO | FGRUPO_JUGADOR));
    animacion = new Animacion(_posicion, data.tanimacion);
    animacion->enBucle = true;
    tipoClase = CLASE_EQUIPAMIENTO;
    nombre = "Equipamiento";
    tiempoAnterior = GetTime();
}

Equipamiento::~Equipamiento()
{
    if (animacion)
    {
        delete animacion;
        animacion = nullptr;
    }
}

#include "Convertir.hpp"

void Equipamiento::actualizar(float dt)
{
    if (visible)
    {
        Objeto::actualizar(dt);
        tiempoAnterior = GetTime();
        return;
    }

    int tiempoTranscurrido = GetTime() - tiempoAnterior;
    if (tiempoTranscurrido > dataEquipamiento[tipo].tiempoNoVisible)
        visible = true;
    std::string t = std::to_string(tiempoTranscurrido);
    DrawText(t.c_str(), Convertir::MetrosEnPixeles(posicion.x), Convertir::MetrosEnPixeles(posicion.y), 3, RED);
}

void Equipamiento::procesarFisicas()
{
}

void Equipamiento::dibujar()
{
    if (visible)
        Objeto::dibujar();
}

void Equipamiento::desaparecer()
{
    if (visible)
        visible = false;
}
