#ifndef MIXER_H
#define MIXER_H
#include "Modulos/AudioMod.h"
#include "Matrix/Matriz.h"
#include "ofSoundBuffer.h"
#include "conexion.h"

class Master
{
    int ninputs, noutputs;
    //Los módulos empiezan a partir del 2, el 0 son las entradas y el 1 las salidas
    std::vector <AudioMod *> modulos;
    ofSoundBuffer output;
    Matriz matriz;
    //std::vector <int [2] > inputlink;

    std::vector <Conexion *> conexiones;
    bool conexionesListas();




public:
    bool isOutReady();
    Master(int ninputs, int noutputs);
    ~Master();
    void update();
    int processInput(ofSoundBuffer & input);
    int getOutput(ofSoundBuffer& output);
    int addModulo (AudioMod *modulo);
    int addConexion(int input[2], int output[2]);
};

#endif // MIXER_H
