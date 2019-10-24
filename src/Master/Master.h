#ifndef MIXER_H
#define MIXER_H
#include "Modulos/AudioMod.h"
#include "Matrix/Matriz.h"
#include "ofSoundBuffer.h"
#include "conexion.h"
#include "Link/LinkStack.h"

class Master
{
    int ninputs, noutputs;
    //Los módulos empiezan a partir del 2, el 0 son las entradas y el 1 las salidas
    std::vector <AudioMod *> modulos;
    ofSoundBuffer output;
    //std::vector <int [2] > inputlink;

    std::vector <Conexion *> conexiones;
    bool conexionesListas();

    LinkStack links;


    Matriz* matriz;

public:
    bool isOutReady();
    Master(int ninputs, int noutputs, string mat_port, int baud);
    ~Master();
    void update();
    int processInput(ofSoundBuffer & input);
    int getOutput(ofSoundBuffer& output);
    int addModulo (AudioMod *modulo);
    int addConexion(int input[2], int output[2]);
    AudioMod* getModulo(int pos);


    int addLinkFromMatr(int x, int y, AudioMod *toLink, int nAudlink, int nMatrlink);
    int addLinkFromAud(AudioMod* fromLink, int toPos[], int nAudLink, int nMatrLink);


    void createLinks();
    void createModules ();
};

#endif // MIXER_H
