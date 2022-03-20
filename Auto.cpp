#include "Auto.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

#include <algorithm>
#include <iostream>

Auto::Auto(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::DIM_AUTO.x;
    espacio.height = Config::DIM_AUTO.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite("autoAzul");
    velocidad = {3.0f, 3.0f};
    tipoClase = CLASE_AUTO;
    vida = Config::MAX_VIDA;
    nombre = "Auto";

    generarFisicasIniciales();
    iniciarBarraVida();
}

Auto::~Auto()
{
    // Borrar las balas
    if (balas.size() > 0)
    {
        for (auto &bala : balas)
            delete bala;
        balas.clear();
    }
    if (barraVida != nullptr)
    {
        delete barraVida;
        barraVida = nullptr;
    }
}

void Auto::actualizar(float dt)
{
    if (animacion != nullptr)
    {
        animacion->actualizar(dt);
        return;
    }
    procesarFisicas();
    sincronizarObjetoConFisicas();
    actualizarBarraVida();
    eliminarBalasDeMemoria();
}

void Auto::procesarFisicas()
{
    
}

void Auto::dibujar()
{
    Objeto::dibujar();
    barraVida->dibujar();
    for (auto bala : balas)
        bala->dibujar();
    // Debug fisicas
    //fcuerpo->dibujar();
}

void Auto::generarFisicasIniciales()
{
    fcuerpo = new FisicasCuerpo(this, FCUERPO_DEFECTO);
    if (fcuerpo == nullptr)
        return;
    fcuerpo->agregarColisionador(FMaterial(80.f, 0.0f, 0.0f), FGRUPO_AUTO, (FGrupoColision) (FGRUPO_AUTO | FGRUPO_JUGADOR | FGRUPO_OBSTACULO | FGRUPO_BALA));
}

b2Vec2 Auto::retVelocidadLateral()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return b2Vec2();
    b2Vec2 normal = cuerpo->GetWorldVector(b2Vec2(1.0f, 0.0f));
    return b2Dot(normal, cuerpo->GetLinearVelocity()) * normal;
}

b2Vec2 Auto::retVelocidadDelantera()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return b2Vec2();
    b2Vec2 normal = cuerpo->GetWorldVector(b2Vec2(0.0f, 1.0f));
    return b2Dot(normal, cuerpo->GetLinearVelocity()) * normal;
}

void Auto::detenerRotacion()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    cuerpo->ApplyAngularImpulse(0.1f * cuerpo->GetInertia() * -cuerpo->GetAngularVelocity(), true);
}

void Auto::detenerAuto()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    b2Vec2 v = cuerpo->GetLinearVelocity();
    // TODO: No detener el auto al seco :D
    cuerpo->ApplyLinearImpulse(/* 1.0f * */cuerpo->GetMass() * -v, cuerpo->GetWorldCenter(), true);
}

void Auto::actualizarFriccion()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    // Velocidad lateral
    b2Vec2 impulso = cuerpo->GetMass() * -retVelocidadLateral();
    cuerpo->ApplyLinearImpulse(impulso, cuerpo->GetWorldCenter(), true);

    detenerRotacion();
    
    // Velocidad delantera
    b2Vec2 vdelantera = retVelocidadDelantera();
    float v = vdelantera.Normalize();
    float arrastre = -2 * v;
    cuerpo->ApplyLinearImpulse(arrastre * vdelantera, cuerpo->GetWorldCenter(), true);
}

void Auto::iniciarBarraVida()
{
    Vector2 np = Convertir::MetrosEnPixeles(posicion);
    np.x -= Convertir::MetrosEnPixeles(espacio.width) * 0.5;
    np.y -= Convertir::MetrosEnPixeles(espacio.height) * 0.5 + 10;
    barraVida = new BarraVida(np, vida);
}

void Auto::actualizarBarraVida()
{
    Vector2 np = Convertir::MetrosEnPixeles(posicion);
    np.x -= Convertir::MetrosEnPixeles(espacio.width) * 0.5;      
    np.y -= Convertir::MetrosEnPixeles(espacio.height) * 0.5 + 10;
    barraVida->actualizar(np, vida);
}

void Auto::disparar()
{
    std::vector<Vector2> vertices = Util::retVerticesRectangulo(espacio, (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo);
    Vector2 arribaIzquierda = vertices.at(0);
    Vector2 arribaDerecha = vertices.at(1);
    Vector2 p = {arribaIzquierda.x, arribaIzquierda.y};
    Bala *nueva = new Bala(p, BALA_AURA);
    nueva->angulo = angulo;
    balas.push_back(nueva);
}

void Auto::explotar()
{
    if (marcadoParaBorrar == true)
        return;
    if (animacion != nullptr)
    {
        delete animacion;
        animacion = nullptr;
    }
    animacion = new Animacion(Convertir::MetrosEnPixeles(posicion), ANIM_EXPLOSION_NARANJA, 10);
    marcadoParaBorrar = true;
}

void Auto::eliminarBalasDeMemoria()
{
    balas.erase(std::remove_if(balas.begin(), balas.end(), [] (Bala *bala) {
                if (bala->marcadoParaBorrar == true)
                {
                    if (bala->animacion->estaCorriendo == false)
                    {
                        delete bala;
                        return true;
                    }
                }
                return false;
            }), balas.end());
}

