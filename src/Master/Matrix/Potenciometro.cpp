#include "Potenciometro.h"

Potenciometro::Potenciometro(int pos[], float val, Tipo_Modulo tipo):
    MatrixMod (pos, tipo,1,0),
    valor (val)
{

}
