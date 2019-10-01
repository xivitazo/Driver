#include "GainMod.h"

GainMod::GainMod(float gain):
    AudioMod(1,1,1),
    gain(gain)
{

}

void GainMod::process ()
{
    outputs=inputs*gain;
}

void GainMod::update(int nlink, float val)
{
    gain=val;
}
