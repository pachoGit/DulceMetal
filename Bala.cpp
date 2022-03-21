#include "Bala.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Convertir.hpp"
#include "Animacion.hpp"

Bala::Bala(Vector2 _posicion, TipoBala _tipo) : Objeto(_posicion)
{
    espacio.width = Config::DIM_BALA_NORMAL.x;
    espacio.height = Config::DIM_BALA_NORMAL.y;
    tipo = _tipo;
    std::string nombre;
    switch (tipo)
    {
        case BALA_BASICA:
            nombre = "balaBasica";
            break;
        case BALA_FUEGO:
            nombre = "balaFuego";
            break;
        case BALA_ELECTRICO:
            nombre = "balaBasica";
            break;
        case BALA_AURA:
            nombre = "balaAura";
            break;
        case BALA_FURIA:
            nombre = "balaFuria";
            break;
        case BALA_FLOREAL:
            nombre = "balaFloreal";
            break;
    }
    sprite = Motor::retMotor().retGestorSprites()->retSprite(nombre);
    velocidad = {8.0f, 8.0f};
    angulo = 0.f; // Para que este a la misma direccion de la textura del auto :D
    tipoClase = CLASE_BALA;
    nombre = "Bala";
    efecto = (tipo == BALA_BASICA ? 10 : 20);
        
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
    /*
    posicion.x += std::sin(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.x;
    posicion.y -= std::cos(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.y;
    */
    procesarFisicas();
    sincronizarObjetoConFisicas();
}

void Bala::procesarFisicas()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    
    b2Vec2 vactual = cuerpo->GetLinearVelocity();
    // Dar el impulso para su movimiento
    if (vactual.x == 0 && vactual.y == 0) // No tiene velocidad :D
    {
        // Dar el impulso inicial
        float longitud = 1.0f; // Esto es para obtener la direccion de la bala
        b2Vec2 direccion(longitud * std::sin(cuerpo->GetAngle()), longitud * std::cos(cuerpo->GetAngle()) * -1);
        b2Vec2 impulso = 0.5f * direccion;
        cuerpo->ApplyLinearImpulse(impulso, cuerpo->GetWorldCenter(), true);
    }
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
    TipoAnimacion tanimacion;
    switch (tipo)
    {
        case BALA_BASICA:
            tanimacion = ANIM_EXPLOSION_BALA_AMARILLA;
            break;
        case BALA_FUEGO:
            tanimacion = ANIM_EXPLOSION_BALA_AMARILLA;
            break;
        case BALA_ELECTRICO:
            tanimacion = ANIM_EXPLOSION_BALA_AMARILLA;
            break;
        case BALA_AURA:
            tanimacion = ANIM_EXPLOSION_BALA_AZUL;
            break;
        case BALA_FURIA:
            tanimacion = ANIM_EXPLOSION_BALA_ROJA;
            break;
        case BALA_FLOREAL:
            tanimacion = ANIM_EXPLOSION_BALA_VERDE;
            break;
    }
    animacion = new Animacion(Convertir::MetrosEnPixeles(posicion), tanimacion, 10);
    marcadoParaBorrar = true;
}
