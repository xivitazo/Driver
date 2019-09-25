#ifndef MODULO_H
#define MODULO_H
enum Tipo_Modulo{
    FADER,
    KNOB,
    BOTON
};

using namespace std;

class Modulo
{
    int posicion [2];
    Tipo_Modulo tipo;
public:
    Modulo(int pos[2], Tipo_Modulo tp);
    void getPos(int *pos[]);
    virtual void serial_in (char ** mensaje){}
    virtual void serial_out(char ** mensaje){}
};

#endif // MODULO_H
