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
}

Equipamiento::~Equipamiento()
{
}

void Equipamiento::actualizar(float dt)
{
    Objeto::actualizar(dt);
}

void Equipamiento::procesarFisicas()
{
}

void Equipamiento::dibujar()
{
    Objeto::dibujar();
}

void Equipamiento::desaparecer()
{
    if (!marcadoParaBorrar)
        marcadoParaBorrar = true;
}
