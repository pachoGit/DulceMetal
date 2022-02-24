#ifndef FISICASCOLISIONADOR_HPP
#define FISICASCOLISIONADOR_HPP

#include "FisicasDefs.hpp"
#include "FisicasCuerpo.hpp"

class FisicasCuerpo;

class FisicasColisionador
{
  private:
    
    b2Fixture *accesorioBox2D;

    FMaterial fmaterial;

  public:

    FisicasCuerpo *fcuerpo;

  public:
    
    FisicasColisionador(FisicasCuerpo *_fcuerpo, const FMaterial &_fmaterial, FGrupoColision miGrupo, FGrupoColision colisionarCon);

    ~FisicasColisionador();

    void ingMaterial(const FMaterial &material);

    FMaterial retMaterial() const;

    b2Fixture *retAccesorioBox2D() const;
};


#endif /* FISICASCOLISIONADOR_HPP */
