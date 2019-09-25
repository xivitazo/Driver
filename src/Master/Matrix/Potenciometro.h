#ifndef POTENCIOMETRO_H
#define POTENCIOMETRO_H
#include "Modulo.h"


class Potenciometro: public Modulo
{
    float valor;
public:
    Potenciometro(int pos[], float val, Tipo_Modulo tipo);
};

#endif // POTENCIOMETRO_H
