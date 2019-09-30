#include "MixerMod.h"

MixerMod::MixerMod(int ninputs, bool ch_gain, bool crossfader):
    ch_gain(ch_gain),
    crossfader(crossfader),
    AudioMod(ninputs,1)
{
    ch_fader.assign(ninputs,0);
}

void MixerMod::process ()
{

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
            else
                chanel.addTo(outputs);
        }
    }
    else
    {
        for(int n=0; n<ninputs;n++)
        {
            ofSoundBuffer chanel;
            ofSoundBuffer left, right;
            inputs.getChannel(left,2*n);
            inputs.getChannel(right,2*n+1);
            chanel.setChannel(left, 0);
            chanel.setChannel(right,1);
            chanel.addTo(outputs);
        }
    }

}
