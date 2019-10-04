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

void MatrixMod::serial_in(char **mensaje)
{
    float val;
    sscanf((const char *)mensaje,"%f", &val);
    inputLinks[0]->update(val);
}

int MatrixMod::addInputLink(AudioMod *Mod, int nAudLink, int nMatrLink)
{
    if (nMatrLink>=nInputLinks && Mod->getNLinks()>=nAudLink)
        return -1;
    inputLinks.push_back(new Link(Mod,nAudLink));
    return true;

}
