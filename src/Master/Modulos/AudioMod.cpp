#include "AudioMod.h"

AudioMod::AudioMod(int ninputs, int noutputs, int nInLinks, int nOutLinks):
    ninputs(ninputs),
    noutputs(noutputs),
    nInLinks(nInLinks),
    nOutLinks(nOutLinks)
{
    pthread_mutex_init(&mtx,NULL);
    pthread_mutex_lock(&mtx);

    input_lock.assign(ninputs,NULL);
    outputs.resize(noutputs*2);
    inputs.resize(ninputs*2);
    linkReady.assign(nOutLinks,1);

    pthread_mutex_unlock(&mtx);
}

int AudioMod::getOutput(ofSoundBuffer& output)
{
    if (!isOutReady())
        return -1;
    pthread_mutex_lock(&mtx);
    output=outputs;
    pthread_mutex_unlock(&mtx);
    return true;
}

int AudioMod::getOutput(ofSoundBuffer &output, int noutput)
{
    if (noutput>=noutputs || !isOutReady())
        return -1;
    pthread_mutex_lock(&mtx);
    ofSoundBuffer left, right;
    outputs.getChannel(left, 2*noutput);
    outputs.getChannel(right,2*noutput+1);
    //output.allocate(this->outputs.size(),2);
    output.setNumChannels(2);
    output.setChannel(left,0);
    output.setChannel(right,1);
    pthread_mutex_unlock(&mtx);
    return true;
}

bool AudioMod::isOutReady()
{
    pthread_mutex_lock(&mtx);
    for (int n=0;n<ninputs;n++)
        if(input_lock[n]==0)
        {
            pthread_mutex_unlock(&mtx);
            return 0;
        }
    pthread_mutex_unlock(&mtx);
    return 1;
}

bool AudioMod::noMtxOutReady()
{
    for (int n=0;n<ninputs;n++)
        if(input_lock[n]==0)
        {
            pthread_mutex_unlock(&mtx);
            return 0;
        }
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
    input_lock.assign(ninputs,true);
    process();
    pthread_mutex_unlock(&mtx);
    return true;

}
int AudioMod::processInput(int ninput, ofSoundBuffer input)
{
    if(ninput>=ninputs || input.getNumChannels()!=2 ||input_lock[ninput]==1)
        return -1;
   pthread_mutex_lock(&mtx);
   input_lock[ninput]=1;
   ofSoundBuffer left, right;
   input.getChannel(left,0);
   input.getChannel(right,1);
   inputs.setChannel(left, ninput*2);
   inputs.setChannel(right, ninput*2+1);
   if(noMtxOutReady())
   {
       process();
       pthread_mutex_unlock(&mtx);
       return true;
   }
   else
   {
       pthread_mutex_unlock(&mtx);
       return 0;
   }
}


void AudioMod::resetBuff(int numSamples)
{
    pthread_mutex_lock(&mtx);
    outputs.allocate(numSamples, 2*noutputs);
    outputs.set(0);
    inputs.allocate(numSamples,2*ninputs);

    inputs.set(0);
    input_lock.assign(ninputs,NULL);
    pthread_mutex_unlock(&mtx);
}



int AudioMod::updateLink (int nlink, float val)
{
    if (nlink>=nInLinks)
        return -1;
    pthread_mutex_lock(&mtx);
    in_link(nlink,val);
    pthread_mutex_unlock(&mtx);
    return true;
}

float AudioMod::getLink (int nlink)
{
    if (nlink >= nOutLinks)
        return -1;
    pthread_mutex_lock(&mtx);
    float val= out_link(nlink);
    linkReady[nlink]=0;
    pthread_mutex_unlock(&mtx);
    return val;
}

bool AudioMod::isLinkReady(int nlink)
{
    if (nlink>=nOutLinks)
        return false;
    pthread_mutex_lock(&mtx);
    int val= linkReady[nlink];
    pthread_mutex_unlock(&mtx);
    return val;
}
