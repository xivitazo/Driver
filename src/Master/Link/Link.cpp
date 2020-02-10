#include "Link.h"

Link::Link(AudioMod *audLink, int audNLink, MatrixMod *matLink, int matNLink, bool fromAud):
    audLink(audLink),
    audNLink(audNLink),
    matLink(matLink),
    matNLink(matNLink),
    fromAud(fromAud)
{
}

 void Link::update()
 {
     if(!isLinkReady())
         return;
     if (fromAud)
     {
         float val=2*audLink->getLink(audNLink);
         matLink->updateLink(matNLink, val);
         return;
     }
     float val=2*matLink->getLink(matNLink);
     audLink->updateLink(audNLink, val);
 }

 bool Link::isLinkReady()
 {
     if (fromAud)
         return audLink->isLinkReady(audNLink);
     return matLink->isLinkReady(matNLink);
 }
//template <class AudioMod, class MatrixMod>
/*template<> void Link<AudioMod, MatrixMod>::update ()
{
    float value=fromLink->getLink(fromNLink);
    toLink->updateLink(toNLink, value);
}

template<> void Link<MatrixMod, AudioMod>::update ()
{
    float value=fromLink->getLink(fromNLink);
    toLink->updateLink(toNLink, value);
}

template <class FromMod, class ToMod>
Link<FromMod, ToMod>::Link(FromMod * fromLink, int fromNLink, ToMod * toLink, int toNLink):
    fromLink (fromLink),
    fromNLink(fromNLink),
    toLink(toLink),
    toNLink(toNLink)
{

}*/

/*template <>
Link<MatrixMod,AudioMod>::Link(MatrixMod * fromLink, int fromNLink, AudioMod * toLink, int toNLink):
    fromLink (fromLink),
    fromNLink(fromNLink),
    toLink(toLink),
    toNLink(toNLink)
{

}*/
/*template <>
class Link <AudioMod, MatrixMod>
{
    AudioMod* fromLink;
    int fromNLink;

    MatrixMod* toLink;
    int toNLink;


public:
    Link (AudioMod * fromLink, int fromNLink, MatrixMod * toLink, int toNLink):
        fromLink(fromLink),
        fromNLink(fromNLink),
        toLink(toLink),
        toNLink(toNLink)
    {}
    void update()
    {
        float value=fromLink->getLink(fromNLink);
        toLink->updateLink(toNLink, value);
    }

};

template <>
class Link <MatrixMod,  AudioMod>
{
    MatrixMod* fromLink;
    int fromNLink;

    AudioMod* toLink;
    int toNLink;


public:
    Link (MatrixMod * fromLink, int fromNLink, AudioMod * toLink, int toNLink):
        fromLink(fromLink),
        fromNLink(fromNLink),
        toLink(toLink),
        toNLink(toNLink)
    {}
    void update()
    {
        float value=fromLink->getLink(fromNLink);
        toLink->updateLink(toNLink, value);
    }

};*/
