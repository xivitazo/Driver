#include "GainMod.h"

GainMod::GainMod(float gain):
    AudioMod(1,1),
    gain(gain)
{

}

void GainMod::process ()
{
    outputs=inputs*gain;
}
