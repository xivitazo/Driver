#include "AudioMod.h"

AudioMod::AudioMod(int ninputs, int noutputs):
    ninputs(ninputs),
    noutputs(noutputs)
{
    pthread_mutex_init(&mtx,NULL);
    pthread_mutex_lock(&mtx);

    ready.assign(ninputs,NULL);
    outputs.resize(noutputs*2);
    inputs.resize(ninputs*2);

    pthread_mutex_unlock(&mtx);
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
int AudioMod::getOutput(ofSoundBuffer& output)
{
    if (!isOutReady())
        return -1;
    pthread_mutex_lock(&mtx);
    ready.assign(ninputs,false);
    output=outputs;
    pthread_mutex_unlock(&mtx);
    return true;
}

int AudioMod::getOutput(ofSoundBuffer &output, int noutput)
{
    if (noutput>=noutputs)
        return -1;
    pthread_mutex_lock(&mtx);
    ofSoundBuffer left, right;
    outputs.getChannel(left, 2*noutput);
    outputs.getChannel(right,2*noutput+1);
    output.allocate(this->outputs.size(),2);
    output.setChannel(left,0);
    output.setChannel(right,1);
    pthread_mutex_unlock(&mtx);
    return true;
}

bool AudioMod::isOutReady()
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
int AudioMod::processInput (ofSoundBuffer inputs)
{
    if (inputs.getNumChannels()!=2*ninputs)
        return -1;
    pthread_mutex_lock(&mtx);
    resetOutBuff(inputs.size());
    process();
    resetInBuff(inputs.size());
    pthread_mutex_unlock(&mtx);
    return true;

}
int AudioMod::processInput(int ninput, ofSoundBuffer input)
{
    if(ninput>=ninputs || input.getNumChannels()!=2)
        return -1;
   pthread_mutex_lock(&mtx);
   ready[ninput]=1;
   ofSoundBuffer left, right;
   input.getChannel(left,0);
   input.getChannel(right,1);
   inputs.setChannel(left, ninput*2);
   inputs.setChannel(right, ninput*2+1);
   if(isOutReady())
   {
       resetOutBuff(inputs.size());
       process();
       resetInBuff(input.size());
       pthread_mutex_unlock(&mtx);
       return true;
   }
   else
   {
       pthread_mutex_unlock(&mtx);
       return 0;
   }
}

void AudioMod::resetOutBuff(int numSamples)
{
    outputs.allocate(numSamples, 2*noutputs);
    outputs.set(0);
}

void AudioMod::resetInBuff(int numSamples)
{
    inputs.allocate(numSamples,2*ninputs);
    inputs.set(0);

}
