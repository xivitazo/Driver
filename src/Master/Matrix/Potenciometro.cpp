#include "Potenciometro.h"

Potenciometro::Potenciometro(int pos[], float val, Tipo_Modulo tipo):
    MatrixMod (pos, tipo,0,1),
    valor (val)
{

}

void Potenciometro::serial_in(int link, float mensaje)
{
    valor=mensaje;
}

/*float Potenciometro::value(int link)
{
    return valor;
}*/
float Potenciometro:: out_link(int link)
{
    return valor;

}
void   Potenciometro::in_link (int link, float value)
{
    valor=value;
}
