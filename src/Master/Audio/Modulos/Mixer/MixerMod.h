#ifndef MIXERMOD_H
#define MIXERMOD_H
#include "../AudioMod.h"

class MixerMod : public AudioMod
{

    virtual void process();
    virtual void update(int nlink, float val);

    //Activacion de crossfader y de gain por canal
    bool crossfader, ch_gain;
    //Gain de cada canal independiente
    std::vector <float> gain;
    //Valor de 0-1 donde 1 es totalmente canal A y 0 totalmente canal B
    //Los canales no asociados a ningun canal se suman sin ponderacion
    float fader;
    //1 - Canal A
    //-1 - Canal B
    //0 No canal
    std::vector <int> ch_fader;
public:
    MixerMod(int ninputs,bool ch_gain=0, bool crossfader=0);
};

#endif // MIXERMOD_H
