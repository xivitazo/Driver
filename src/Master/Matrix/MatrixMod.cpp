
#include "MatrixMod.h"

void MatrixMod::getPos() {

    x=posicion[0];
    y=posicion[1];
}

void MatrixMod::readSerial() {

    if (link >=nOutLinks)
        return;
    /*float val;
    sscanf((const char *)mensaje,"%f", &val);*/
    pthread_mutex_lock(&mtx);
    serial_in(link,mensaje);
    linkReady[link]=1;
    pthread_mutex_unlock(&mtx);
}

//int MatrixMod::addInputLink(AudioMod *Mod, int nAudLink, int nMatrLink)
//{
//if (nMatrLink>=nInputLinks && Mod->getNLinks()>=nAudLink)
//return -1;
//inputLinks.push_back(new Link(Mod,nAudLink));
//return true;
//
//}

float MatrixMod::getLink(int link) {

    if (link>=nOutLinks)
        return -1;

    pthread_mutex_lock(&mtx);
    float val= out_link(link);
    linkReady[link]=0;
    pthread_mutex_unlock(&mtx);
    return val;
}

void MatrixMod::setLink() {

    if (link>=nInLinks)
        return;
    pthread_mutex_lock(&mtx);
     in_link(link,val);
    pthread_mutex_unlock(&mtx);
}

int MatrixMod::updateLink() {

    if (nlink>=nInLinks && linkReady[nlink]==0)
        return -1;
    pthread_mutex_lock(&mtx);
    linkReady[nlink]=0;
    in_link(nlink,value);
    pthread_mutex_unlock(&mtx);
    return true;
}

bool MatrixMod::isLinkReady() {

    if (nlink>=nOutLinks)
        return false;
    return linkReady[nlink];
}

