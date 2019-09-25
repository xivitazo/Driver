#ifndef MODULO_H
#define MODULO_H

#include "ofSoundBuffer.h"

class Modulo
{
protected:
    ofSoundBuffer outputs;
    ofSoundBuffer inputs;
    //std::vector <int [2]> next;
    std::vector <bool> ready;
    const int ninputs, noutputs;
public:
    Modulo(int ninputs, int noutputs);
    //Procesa todas las entradas guardadas en el buffer que tendra que tener el tamaño adecuado
    //-1 error
    //0 procesado correctamente pero módulo no listo para output
    //>0 procesado y listo para output
    virtual int processInput (ofSoundBuffer inputs);
    //Añade la entrada ninput yc si puede procesa el audio
    //-1 error
    //0 procesado correctamente pero módulo no listo para output
    //>0 procesado y listo para output
    virtual int processInput (int ninput,ofSoundBuffer input);
    virtual void update (char* argv, int argc){}
    /*int setNext (std::vector <int [2]> next);
    int setNext(int next[2], int noutput);
    int getNext(std::vector <int [2]> & next);*/
    int getOutput(ofSoundBuffer& output);
    int getOutput(ofSoundBuffer &output, int noutput);
    bool isOutReady();
    void resetBuff(int numSamples);
    int getNoutputs(){return noutputs;}
    int getNinputs(){return ninputs;}
};

#endif // MODULO_H
