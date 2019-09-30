#ifndef LINK_H
#define LINK_H
#include "../Modulos/AudioMod.h"


class Link
{
private:
    AudioMod* link_mod;
    int link;
public:
    Link (AudioMod* link, int nlink);
    void update(float &val);
};

#endif // LINK_H
