#ifndef _POTENCIOMETRO_H
#define _POTENCIOMETRO_H


#include "MatrixMod.h"

class Potenciometro : public MatrixMod {
  private:
    float valor;

    //virtual float value(int link);
    virtual float out_link(int link);

    virtual void in_link(int link, float value);

    virtual void serial_in(int link, float mensaje);


  public:
    Potenciometro(int pos[], float val, Tipo_Modulo tipo);

};
#endif
