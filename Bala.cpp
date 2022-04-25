#include "Bala.hpp"
#include "Motor.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

Bala::Bala(Vector2 _posicion, TipoBala _tipo, unsigned _autor) : Objeto(_posicion)
{ 
    tipo = _tipo;
    autor = _autor;
    auto data = dataBala.at(tipo);
    espacio.width = data.dimension.x;
    espacio.height = data.dimension.y;
    efecto = data.efecto;
    distanciaMaxima = data.distanciaMaxima;
    sprite = Motor::retMotor().retGestorSprites()->retSprite(data.nombre);
    velocidad = data.velocidad;
    angulo = 0.f; // Para que este a la misma direccion de la textura del auto :D
    tipoClase = CLASE_BALA;
    fcuerpo = Motor::retMotor().retGestorFisicas()->crearFCuerpo(this,
                                                                 (FCuerpoBanderas) (FCUERPO_DEFECTO | FCUERPO_PROYECTIL),
                                                                 FMaterial(1.f, 1.f, 0.1f), 
                                                                 FGRUPO_BALA,
                                                                 (FGrupoColision) (FGRUPO_AUTO | FGRUPO_ENEMIGO | FGRUPO_JUGADOR | FGRUPO_OBSTACULO));
    nombre = "Bala";
    posicionAnterior = _posicion;
    distanciaRecorrida = 0.0f;
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
    // Calculamos la distancia recorrida hasta el momento por la bala
    distanciaRecorrida += Util::distancia(posicionAnterior, posicion);
    posicionAnterior = posicion;
    if (distanciaRecorrida > distanciaMaxima)
        explotar();
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

void Bala::explotar()
{
    if (animacion != nullptr)
    {
        delete animacion;
        animacion = nullptr;
    }
    animacion = new Animacion(posicion, dataBala.at(tipo).texplosion);
    marcadoParaBorrar = true;
}

float Bala::retDistanciaRecorrida() const
{
    return distanciaRecorrida;
}
