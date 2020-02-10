#include "EqMod.h"

EqMod::EqMod(int n_bandas):AudioMod(1,1,20,0),
    eq(n_bandas)
{
}

void EqMod::process()
{
    std::vector <float> outLeft, outRight;

    for (int n=0; n<inputs.getNumFrames();n++)
    {
        float L,R;
        L=inputs.getSample(n,0);
        R=inputs.getSample(n,1);
        eq.process(L,R);
        outLeft.push_back(L);
        outRight.push_back(R);
    }
    std::vector <float> out;
    for (int n=0;n<inputs.getNumFrames();n++)
    {
        out.push_back(outLeft[n]);
        out.push_back(outRight[n]);
    }
    outputs.copyFrom(out.data(),inputs.getNumFrames(),2,inputs.getSampleRate());
}
//Los links 0-9 refieren a la ganania de cada banda
//los links 10-19 reieren a la frecuencia de cada ganancia
void EqMod::in_link(int link, float value)
{
    if (link%10>=eq.getBandas())
        return;
    if((link-(link%10))/10==1)
    {
        eq.setFc(link%10,value);
    }
    else
    {
        eq.setGain(link%10,value);
    }
}
