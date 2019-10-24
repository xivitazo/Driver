#ifndef POTENCIOMETRO_H
#define POTENCIOMETRO_H
#include "MatrixMod.h"


class Potenciometro: public MatrixMod
{
    float valor;
    //virtual float value(int link);
    virtual float out_link(int link);
    virtual void  in_link (int link, float value);
    virtual void serial_in(int link, float mensaje);
public:
    Potenciometro(int pos[], float val, Tipo_Modulo tipo);

};

#endif // POTENCIOMETRO_H
