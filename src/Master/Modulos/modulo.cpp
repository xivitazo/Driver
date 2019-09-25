#include "modulo.h"

Modulo::Modulo(int ninputs, int noutputs):
    ninputs(ninputs),
    noutputs(noutputs)
{
    ready.assign(ninputs,NULL);
    outputs.resize(noutputs*2);
    inputs.resize(ninputs*2);
}
/*
int Modulo::setNext(std::vector<int[2]> next)
{
    if (next.size() != noutputs)
        return -1;
    for (int n=0; n<next.size();n++)
    {
        this->next[n][0]=next[n][0];
        this->next[n][1]=next[n][1];
    }
    return true;
}

int Modulo::setNext(int next[], int noutput)
{
    if(noutput>=noutputs)
        return -1;
    this->next[noutput][0]=next[0];
    this->next[noutput][1]=next[1];
    return true;
}
*/
int Modulo::getOutput(ofSoundBuffer& output)
{
    if (!isOutReady())
        return -1;
    output=outputs;
    return true;
}

int Modulo::getOutput(ofSoundBuffer &output, int noutput)
{
    if (noutput>=noutputs)
        return -1;
    ofSoundBuffer left, right;
    outputs.getChannel(left, 2*noutput);
    outputs.getChannel(right,2*noutput+1);
    output.allocate(this->outputs.size(),2);
    output.setChannel(left,0);
    output.setChannel(right,1);
    return true;
}

bool Modulo::isOutReady()
{
    for (int n=0;n<ninputs;n++)
        if(ready[n]==0)
            return 0;
    return 1;

}

/*int Modulo::getNext(std::vector<int[2]> &next)
{
    for (int n=0;n<this->next.size();n++)
    {
        next[n][0]=this->next[n][0];
        next[n][1]=this->next[n][1];
    }
    if (!isOutReady())
        return 0;
    return 1;
}
*/
int Modulo::processInput (ofSoundBuffer inputs)
{
    return -1;
}
int Modulo::processInput(int ninput, ofSoundBuffer input)
{
    return -1;
}

void Modulo::resetBuff(int numSamples)
{
    outputs.set(0);
    inputs.set(0);
    ready.assign(noutputs,0);
    outputs.allocate(numSamples, 2*noutputs);
    inputs.allocate(numSamples,2*ninputs);
}
