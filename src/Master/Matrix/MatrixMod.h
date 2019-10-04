#ifndef MATRIXMOD_H
#define MATRIXMOD_H
#include <vector>
#include "Link.h"
#include "../Modulos/AudioMod.h"
enum Tipo_Modulo{
    FADER,
    KNOB,
    BOTON
};

using namespace std;

class MatrixMod
{
protected:
    int posicion [2];
    Tipo_Modulo tipo;
    MatrixMod(int pos[2], Tipo_Modulo tp, int nInputLinks, int nOutputLinks);
    const int nInputLinks, nOutputLinks;
    std::vector<Link *> inputLinks;
    std::vector<Link *> outputLinks;
public:
    void getPos(int *pos[]);
    virtual void serial_in (char ** mensaje);
    //virtual void serial_out(char ** mensaje);
    int addInputLink (AudioMod* Mod, int nAudLink, int nMatrLink);
    //int addOutputLink (AudioMod* Mod, int nAudLink, int nMatrLink);
};

#endif // MATRIXMOD_H
