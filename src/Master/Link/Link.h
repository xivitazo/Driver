#ifndef LINK_H
#define LINK_H
#include "../Modulos/AudioMod.h"
#include "../Matrix/MatrixMod.h"


class Link
{
    AudioMod* audLink;
    int audNLink;

    MatrixMod* matLink;
    int matNLink;


public:
    Link (AudioMod* audLink, int audNLink, MatrixMod* matLink, int matNLink, bool fromAud);
    void update();
    bool isLinkReady();
    const bool fromAud;

};







#endif // LINK_H
