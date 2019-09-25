#include "Modulo.h"

Modulo::Modulo(int pos[2], Tipo_Modulo tp):
    tipo(tp)
{
    posicion[1]=pos[1];
    posicion[2]=pos[2];
}
void Modulo::getPos(int *pos[])
{
    *pos[1]=posicion[1];
    *pos [2]=posicion[2];
}
