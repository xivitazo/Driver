#include "gain.h"

Gain::Gain(float gain):
    Modulo(1,1),
    gain(gain)
{

}

int Gain::processInput (ofSoundBuffer inputs)
{
    if (inputs.getNumChannels()!=2)
        return -1;
    outputs=inputs*gain;
    return true;

}
int Gain::processInput(int ninput, ofSoundBuffer input)
{
    if (ninput!=0 || input.getNumChannels()!=2)
        return -1;

    outputs=inputs*gain;
    return true;
}
