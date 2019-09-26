#include "GainMod.h"

GainMod::GainMod(float gain):
    Modulo(1,1),
    gain(gain)
{

}

int GainMod::processInput (ofSoundBuffer inputs)
{
    if (inputs.getNumChannels()!=2)
        return -1;
    outputs=inputs*gain;
    return true;

}
int GainMod::processInput(int ninput, ofSoundBuffer input)
{
    if (ninput!=0 || input.getNumChannels()!=2)
        return -1;

    outputs=inputs*gain;
    return true;
}
