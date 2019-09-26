#include "MixerMod.h"

MixerMod::MixerMod(int ninputs, bool ch_gain, bool crossfader):
    ch_gain(ch_gain),
    crossfader(crossfader),
    Modulo(ninputs,1)
{
    ch_fader.assign(ninputs,0);
}

int MixerMod::processInput (ofSoundBuffer inputs)
{
    if (inputs.getNumChannels()!=2*ninputs)
        return -1;
    outputs.clear();
    ready.assign(ninputs,0);
    if(ch_gain)
    {
        for(int n=0; n<ninputs;n++)
        {
            inputs[2*n]=inputs[2*n]*gain[n];
            inputs[2*n+1]=inputs[2*n+1]*gain[n];
        }
    }
    if (crossfader)
    {
        for(int n=0; n<ninputs;n++)
        {
            ofSoundBuffer chanel;
            ofSoundBuffer left, right;
            inputs.getChannel(left,2*n);
            inputs.getChannel(right,2*n+1);
            chanel.setChannel(left, 0);
            chanel.setChannel(right,1);
            if(ch_fader[n]==1)
               (chanel*fader).addTo(outputs);
            else if(ch_fader[n]==-1)
                (chanel*(1-fader)).addTo(outputs);
            else if(ch_fader[n]==0)
                chanel.addTo(outputs);
            else
                return -1;
        }
    }

    return 1;
}


int MixerMod::processInput (int ninput,ofSoundBuffer input)
{
    if(ninput>=ninputs || input.getNumChannels()!=2)
        return -1;
   ready[ninput]=1;
   ofSoundBuffer left, right;
   input.getChannel(left,0);
   input.getChannel(right,1);
   inputs.setChannel(left, ninput*2);
   inputs.setChannel(right, ninput*2+1);
   if(isOutReady())
       return processInput(inputs);
   else
       return 0;
}
