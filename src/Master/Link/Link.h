#ifndef _LINK_H
#define _LINK_H


class AudioMod;
class MatrixMod;

class Link {
  private:
    AudioMod * audLink;

    int audNLink;

    MatrixMod * matLink;

    int matNLink;


  public:
    Link(AudioMod * audLink, int audNLink, MatrixMod * matLink, int matNLink, bool fromAud);

    void update();

    bool isLinkReady();

    const bool fromAud;

};
#endif
