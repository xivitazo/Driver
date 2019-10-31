#ifndef _BOTON_H
#define _BOTON_H


#include "MatrixMod.h"

class Boton : public MatrixMod {
  public:
    Boton(int posicion[2], bool bot);

    bool boton;

    int led;

};
#endif
