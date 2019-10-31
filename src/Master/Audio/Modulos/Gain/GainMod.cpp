
#include "GainMod.h"

void GainMod::process() {

    outputs=inputs*gain;
}

void GainMod::update() {

    gain=val;
}

void GainMod::in_link() {

    gain=value;
}

GainMod::GainMod(float gain):
    AudioMod(1,1,1,0),
    gain(gain)
{


}

