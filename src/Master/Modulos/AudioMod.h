#ifndef AUDIOMOD_H
#define AUDIOMOD_H

#include "ofSoundBuffer.h"

class AudioMod
{
private:
    pthread_mutex_t mtx;
    void resetOutBuff(int numSamples);
    void resetInBuff(int numSamples);
protected:
    ofSoundBuffer outputs;
    ofSoundBuffer inputs;
    //std::vector <int [2]> next;
    std::vector <bool> ready;
    const int ninputs, noutputs;
    AudioMod(int ninputs, int noutputs);
    virtual void process (){}

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
    virtual void update (char* argv, int argc){}
    int getOutput(ofSoundBuffer& output);
    int getOutput(ofSoundBuffer &output, int noutput);
    bool isOutReady();
    int getNoutputs(){return noutputs;}
    int getNinputs(){return ninputs;}
};

#endif // AUDIOMOD_H
