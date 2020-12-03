#ifndef MATRIXMOD_H
#define MATRIXMOD_H
#include <vector>
//#include "../Modulos/AudioMod.h"
//#include "../Link.h"
enum Tipo_Modulo{
    FADER,
    KNOB,
    BOTON
};

using namespace std;
#include <pthread.h>

class MatrixMod
{

    pthread_mutex_t mtx;
protected:
    int posicion [2];
    Tipo_Modulo tipo;
    MatrixMod(int pos[2], Tipo_Modulo tp, int nInLinks, int nOutLinks);

    //parte de variables que interactuan con el link
    //numero de links de entrada
    const int nInLinks;
    //numero de links de salida
    const int nOutLinks;
    //links de salida listos para ser procesados
    vector <bool> linkReady;
    virtual float out_link(int link){return -1;}
    virtual void  in_link (int link, float value){}
    virtual void serial_in (int link,float mensaje){}

public:
    //bool change;
    void getPos(int &x, int&y);
    void readSerial (int link, float mensaje);


    //parte de los metodos que interactuan con el link
    float getLink (int link);
    void setLink (int link, float val);
    int updateLink (int nlink, float value);
    bool isLinkReady (int nlink);
};

#endif // MATRIXMOD_H
