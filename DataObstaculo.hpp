#ifndef DATAOBSTACULO_HPP
#define DATAOBSTACULO_HPP

#include "FisicasDefs.hpp"


struct InfoObstaculo
{
    std::string nombre;
    Vector2 dimension;
    
    DataObstaculo(_nombre, _dimension)
    {
        nombre = _nombre;
        dimension = _dimension;
    }
};

#endif /* DATAOBSTACULO_HPP */
