
#include "Potenciometro.h"

//float Potenciometro::value(int link)
//{
//return valor;
//}

float Potenciometro::out_link(int link) {

    return valor;

}

void Potenciometro::in_link() {

    valor=value;
}

void Potenciometro::serial_in() {

    valor=mensaje;
}

