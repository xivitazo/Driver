#include "MatrixMod.h"

MatrixMod::MatrixMod(int pos[2], Tipo_Modulo tp, int nInLinks, int nOutLinks):
    tipo(tp),
    nInLinks(nInLinks),
    nOutLinks(nOutLinks)
{
    pthread_mutex_init(&mtx,NULL);
    pthread_mutex_lock(&mtx);

    posicion[0]=pos[0];
    posicion[1]=pos[1];
    linkReady.assign(nOutLinks,1);

    pthread_mutex_unlock(&mtx);
}
void MatrixMod::getPos(int &x, int &y)
{
    x=posicion[0];
    y=posicion[1];
}

void MatrixMod::readSerial(int link, float mensaje)
{
    if (link >=nOutLinks)
        return;
    /*float val;
    sscanf((const char *)mensaje,"%f", &val);*/
    pthread_mutex_lock(&mtx);
    serial_in(link,mensaje);
    linkReady[link]=1;
    pthread_mutex_unlock(&mtx);
}

/*int MatrixMod::addInputLink(AudioMod *Mod, int nAudLink, int nMatrLink)
{
    if (nMatrLink>=nInputLinks && Mod->getNLinks()>=nAudLink)
        return -1;
    inputLinks.push_back(new Link(Mod,nAudLink));
    return true;

}*/

float MatrixMod::getLink(int link)
{
    if (link>=nOutLinks)
        return -1;

    pthread_mutex_lock(&mtx);
    float val= out_link(link);
    linkReady[link]=0;
    pthread_mutex_unlock(&mtx);
    return val;
}
void MatrixMod::setLink (int link, float val)
{
    if (link>=nInLinks)
        return;
    pthread_mutex_lock(&mtx);
     in_link(link,val);
    pthread_mutex_unlock(&mtx);
}

int MatrixMod::updateLink(int nlink, float value)
{
    if (nlink>=nInLinks && linkReady[nlink]==0)
        return -1;
    pthread_mutex_lock(&mtx);
    linkReady[nlink]=0;
    in_link(nlink,value);
    pthread_mutex_unlock(&mtx);
    return true;
}

bool MatrixMod::isLinkReady (int nlink)
{
    if (nlink>=nOutLinks)
        return false;
    return linkReady[nlink];
}
