#ifndef EQMOD_H
#define EQMOD_H
#include "../AudioMod.h"
#include "lib/Ecualizador.h"


class EqMod : public AudioMod
{
    Ecualizador eq;
public:
    EqMod(int n_bandas);
    void process();
    void in_link(int link, float value);
};

#endif // EQMOD_H
