#include "MatrixMod.h"

MatrixMod::MatrixMod(int pos[2], Tipo_Modulo tp, int nInputLinks, int nOutputLinks):
    tipo(tp),
    nInputLinks(nInputLinks),
    nOutputLinks(nOutputLinks)
{
    posicion[1]=pos[1];
    posicion[2]=pos[2];
}
void MatrixMod::getPos(int *pos[])
{
    *pos[1]=posicion[1];
    *pos [2]=posicion[2];
}
