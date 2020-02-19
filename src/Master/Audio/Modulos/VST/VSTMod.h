#ifndef VSTMOD_H
#define VSTMOD_H
#include "../AudioMod.h"
#include "ofxVstHost/src/ofxVstHostPluginLoader.h"
#include"ofxVstHost/src/ofxVstHost.h"


class VSTMod: public AudioMod
{
    ofxVstHost vst;
public:
    VSTMod(std::string path);
    void process();
    void in_link(int link, float value);
};

#endif // VSTMOD_H
