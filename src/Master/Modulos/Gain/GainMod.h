#ifndef GAIN_H
#define GAIN_H
#include "../AudioMod.h"

class GainMod: public AudioMod
{
    float gain;
    virtual void process();
    virtual void update(int nlink, float val);
public:
    GainMod(float gain);

};

#endif // GAIN_H
