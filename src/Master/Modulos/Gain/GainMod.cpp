#include "GainMod.h"

GainMod::GainMod(float gain):
    AudioMod(1,1,1,0),
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
void  GainMod::in_link (int link, float value)
{
    gain=value;
}
