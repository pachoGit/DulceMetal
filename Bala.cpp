#include "Bala.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Convertir.hpp"

Bala::Bala(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::DIM_BALA.x;
    espacio.height = Config::DIM_BALA.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite("bala1");
    velocidad = {8.0f, 8.0f};
    angulo = 0.f; // Para que este a la misma direccion de la textura del auto :D
    tipoClase = CLASE_BALA;
    nombre = "Bala";
    
    generarFisicasIniciales();
}

Bala::~Bala()
{
    
}

void Bala::actualizar(float dt)
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

void Bala::dibujar()
{
    Objeto::dibujar();
}

void Bala::generarFisicasIniciales()
{
    fcuerpo = new FisicasCuerpo(this, (FCuerpoBanderas) (FCUERPO_DEFECTO | FCUERPO_PROYECTIL));
    if (fcuerpo == nullptr)
        return;
    fcuerpo->agregarColisionador(FMaterial(1.f, 1.f, 0.1f), FGRUPO_BALA, (FGrupoColision) (FGRUPO_AUTO | FGRUPO_OBSTACULO));
}
