#include "Bala.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Convertir.hpp"
#include "Animacion.hpp"

Bala::Bala(Vector2 _posicion, const std::string &_nombreBala) : Objeto(_posicion)
{
    espacio.width = Config::DIM_BALA_NORMAL.x;
    espacio.height = Config::DIM_BALA_NORMAL.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite(_nombreBala);
    velocidad = {8.0f, 8.0f};
    angulo = 0.f; // Para que este a la misma direccion de la textura del auto :D
    tipoClase = CLASE_BALA;
    nombre = "Bala";
    efecto = (_nombreBala == "balaBasica" ? 10 : 20);
        
    generarFisicasIniciales();
}

Bala::~Bala()
{
    
}

void Bala::actualizar(float dt)
{
    // La animacion es la explosion
    if (animacion != nullptr)
    {
        animacion->actualizar(dt);
        return;
    }
    posicion.x += std::sin(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.x;
    posicion.y -= std::cos(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.y;
    sincronizarFisicasConObjeto();
}

void Bala::procesarFisicas()
{
    
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

void Bala::explotar()
{
    if (animacion != nullptr)
    {
        delete animacion;
        animacion = nullptr;
    }
    animacion = new Animacion(Convertir::MetrosEnPixeles(posicion), "explosionBlanca", 10);
    marcadoParaBorrar = true;
}
