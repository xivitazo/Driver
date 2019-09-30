#ifndef POTENCIOMETRO_H
#define POTENCIOMETRO_H
#include "MatrixMod.h"


class Potenciometro: public MatrixMod
{
    float valor;
public:
    Potenciometro(int pos[], float val, Tipo_Modulo tipo);
};

#endif // POTENCIOMETRO_H
