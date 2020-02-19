#ifndef FILTERMOD_H
#define FILTERMOD_H

#include "../AudioMod.h"
#include "Filtro.h"


class FilterMod : public AudioMod
{
    Filter filtro[2];
public:
    FilterMod(FilterMode modo);
    void process() ;
    void in_link(int link, float value) ;
};

#endif // FILTERMOD_H
