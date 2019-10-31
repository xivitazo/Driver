#ifndef MIXER_H
#define MIXER_H
#include "Matrix/Matriz.h"
#include "ofSoundBuffer.h"
#include "Link/LinkStack.h"
#include "Audio/Audio.h"

class Master
{

    Audio* audio;

    LinkStack links;


    Matriz* matriz;

public:
    Master(int ninputs, int noutputs, string mat_port, int baud);
    ~Master();
    void update();


    int processInput(ofSoundBuffer & input);
    int getOutput(ofSoundBuffer& output);
    int addAudMod (AudioMod* modulo);
    int addAudConexion(int input[2], int output[2]);

    int addLinkFromMatr(int x, int y, int toLinkPos, int nAudlink, int nMatrlink);
    int addLinkFromAud(int fromLink, int toPos[], int nAudLink, int nMatrLink);


    void createLinks();
    void createModules ();
};

#endif // MIXER_H
