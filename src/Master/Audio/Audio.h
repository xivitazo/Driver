#ifndef AUDIO_H
#define AUDIO_H
#include "Modulos/AudioMod.h"
#include "conexion.h"


class Audio
{
    int ninputs, noutputs;
    //Los módulos empiezan a partir del 2, el 0 son las entradas y el 1 las salidas
    std::vector <AudioMod *> modulos;
    ofSoundBuffer output;
    //std::vector <int [2] > inputlink;

    std::vector <Conexion *> conexiones;
    bool conexionesListas();
public:
    Audio(int ninputs, int noutputs);
    ~Audio();
    int processInput(ofSoundBuffer & input);
    int getOutput(ofSoundBuffer& output);
    int addModulo (AudioMod *modulo);
    int addConexion(int input[2], int output[2]);
    AudioMod* getModulo(int pos);
    bool isOutReady();
};

#endif // AUDIO_H
