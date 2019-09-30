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
protected:
    int posicion [2];
    Tipo_Modulo tipo;
    Modulo(int pos[2], Tipo_Modulo tp);
public:
    void getPos(int *pos[]);
    virtual void serial_in (char ** mensaje){}
    virtual void serial_out(char ** mensaje){}
};

#endif // MODULO_H
