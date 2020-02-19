#include "VSTMod.h"

VSTMod::VSTMod(std::string path): AudioMod(1,1,20,0)
{
    vst.setup(inputs.getSampleRate(),inputs.getNumFrames());
    std::string vst_path=ofToDataPath(path);
    vst_path+=".so";
    vst.load(vst_path);
    //nInLinks=vst.getNumParameters(0);


    std::cout<<vst.getNumParameters(0)<<endl;
    for (int n=0;n<vst.getNumParameters(0);n++)
    {
        cout<<vst.getParameterName(0,n)<<endl;
    }
}

void VSTMod::process()
{
    ofSoundBuffer buff;
    buff=inputs;
    vst.process(0,buff);
    outputs=buff;
}

void VSTMod::in_link(int link, float value)
{
    if (link>=vst.getNumParameters(0))
        return;
    vst.setParameterValue(0,link,value);
}
