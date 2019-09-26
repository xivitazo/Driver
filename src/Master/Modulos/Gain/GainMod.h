#ifndef GAIN_H
#define GAIN_H
#include "../modulo.h"

class GainMod: public Modulo
{
    float gain;
public:
    GainMod(float gain);
    virtual int processInput (ofSoundBuffer inputs);
    virtual int processInput (int ninput,ofSoundBuffer input);

};

#endif // GAIN_H
