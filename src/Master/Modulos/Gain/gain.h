#ifndef GAIN_H
#define GAIN_H
#include "../modulo.h"

class Gain: public Modulo
{
    float gain;
public:
    Gain(float gain);
    virtual int processInput (ofSoundBuffer inputs);
    virtual int processInput (int ninput,ofSoundBuffer input);

};

#endif // GAIN_H
