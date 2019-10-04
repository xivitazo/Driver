#ifndef AUDIOMOD_H
#define AUDIOMOD_H

#include "ofSoundBuffer.h"

class AudioMod
{
private:
    pthread_mutex_t mtx;
protected:
    ofSoundBuffer outputs;
    ofSoundBuffer inputs;
    //std::vector <int [2]> next;
    std::vector <bool> input_lock;
    const int ninputs, noutputs;
    AudioMod(int ninputs, int noutputs, int nlinks);
    virtual void process (){}


    const int nlinks;
    virtual void update(int nlink, float val){}

public:
    //Procesa todas las entradas guardadas en el buffer que tendra que tener el tamaño adecuado
    //-1 error
    //0 procesado correctamente pero módulo no listo para output
    //>0 procesado y listo para output
    int processInput (ofSoundBuffer inputs);
    //Añade la entrada ninput y si puede procesa el audio
    //-1 error
    //0 valor correcto pero módulo no listo para output
    //>0 procesado y listo para output
    int processInput (int ninput,ofSoundBuffer input);
    int update_link (int nlink, float val);
    int getOutput(ofSoundBuffer& output);
    int getOutput(ofSoundBuffer &output, int noutput);
    bool isOutReady();
    int getNoutputs(){return noutputs;}
    int getNinputs(){return ninputs;}
    void resetBuff(int numSamples);
    int getNLinks(){return nlinks;}
};

#endif // AUDIOMOD_H
