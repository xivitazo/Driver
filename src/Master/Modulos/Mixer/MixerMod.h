#ifndef MIXER_H
#define MIXER_H
#include "../modulo.h"

class MixerMod : public Modulo
{
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
    virtual int processInput (ofSoundBuffer inputs);
    virtual int processInput (int ninput,ofSoundBuffer input);
};

#endif // MIXER_H
