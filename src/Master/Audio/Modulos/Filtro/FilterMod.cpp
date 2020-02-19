#include "FilterMod.h"

FilterMod::FilterMod(FilterMode modo): AudioMod(1,1,2,0)
{
    filtro[0].setFilterMode(modo);
    filtro[1].setFilterMode(modo);
}

void FilterMod::process()
{
    for (int n=0;n<inputs.getNumFrames();n++)
    {
        outputs[2*n]=filtro[0].process(inputs[2*n]);
        outputs[2*n+1]=filtro[1].process(inputs[2*n+1]);
    }
}

void FilterMod::in_link(int link, float value)
{
    if (link==0)
    {
        filtro[0].setCutoff(value*20000);
        filtro[1].setCutoff(value*20000);
    }
    else if (link ==1)
    {
        filtro[0].setResonance(value);
        filtro[1].setResonance(value);
    }
}
