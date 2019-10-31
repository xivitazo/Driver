
#include "Link.h"
#include "AudioMod.h"
#include "MatrixMod.h"

Link::Link(AudioMod * audLink, int audNLink, MatrixMod * matLink, int matNLink, bool fromAud):
    audLink(audLink),
    audNLink(audNLink),
    matLink(matLink),
    matNLink(matNLink),
    fromAud(fromAud)
{

}

void Link::update() {

     if(!isLinkReady())
         return;
     if (fromAud)
     {
         float val=audLink->getLink(audNLink);
         matLink->updateLink(matNLink, val);
         return;
     }
     float val=matLink->getLink(matNLink);
     audLink->updateLink(audNLink, val);
}

bool Link::isLinkReady() {

     if (fromAud)
         return audLink->isLinkReady(audNLink);
     return matLink->isLinkReady(matNLink);
}

