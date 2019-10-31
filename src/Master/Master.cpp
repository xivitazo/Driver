
#include "Master.h"
#include "Audio.h"
#include "Matriz.h"
#include "AudioMod.h"

Master::Master() {

    audio=new Audio (ninputs,noutputs);
    matriz=new Matriz(mat_port,baud, 4,6);
    createModules();
    createLinks();
    links.update();
}

Master::~Master() {

     delete matriz;
     delete audio;
}

void Master::update() {

     matriz->update();
     links.updateFromMatr();
}

int Master::processInput() {

     int out=audio->processInput(input);
     links.updateFomAud();
     return out;
}

int Master::getOutput() {

     if (audio->getOutput(output)==-1)
         return -1;
     return true;
}

int Master::addAudMod() {

    return audio->addModulo( modulo);
}

int Master::addLinkFromMatr() {

    //return matriz->addLink(pos,link,nAudlink, nMatrlink);
     MatrixMod* mat_link = matriz->getModulo(x, y);
     AudioMod* toLink = audio->getModulo(toLinkPos);
     if (mat_link==0 || toLink==0)
         return -1;
     links.addFromMatr(mat_link,nMatrlink,toLink,nAudlink);
     return true;
}

void Master::createLinks() {

    int pos[2]={1,4};

    addLinkFromMatr(pos[0], pos[1],0,0,0);
}

void Master::createModules() {

    addAudMod (new GainMod (1.0));
    addAudMod (new GainMod (1.0));
    addAudMod (new MixerMod (2));

    //int conexion1[2]={-1,0}, conexion2[2]={0,0}, conexion3[2]={-2,0};

    int entrada0[2]={-1,0}, entrada1[2]={-1,1};
    int salida0[2]={-2,0}, salida1[2]={-2,1};
    int modulo0_0[2]={0,0}, modulo1_0[2]={1,0};
    int modulo2_0[2]={2,0}, modulo2_1[2]={2,1};

    addAudConexion(entrada0, modulo0_0);
    addAudConexion(modulo0_0,modulo2_0);
    addAudConexion(entrada1, modulo1_0);
    addAudConexion(modulo1_0,modulo2_1);
    addAudConexion(modulo2_0, salida0);
    addAudConexion(modulo2_0, salida1);
}

