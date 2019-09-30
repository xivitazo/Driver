#ifndef GAIN_H
#define GAIN_H
#include "../AudioMod.h"

class GainMod: public AudioMod
{
    float gain;
    virtual void process();
public:
    GainMod(float gain);

};

#endif // GAIN_H
