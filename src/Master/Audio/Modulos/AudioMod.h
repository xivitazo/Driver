#ifndef _AUDIOMOD_H
#define _AUDIOMOD_H


class AudioMod {
  private:
    pthread_mutex_t mtx;

    bool noMtxOutReady();


  protected:
    ofSoundBuffer outputs;

    ofSoundBuffer inputs;

    //std::vector <int [2]> next;
    
    std::vector<bool> input_lock;

    const int ninputs;

    const int noutputs;

    AudioMod(int ninputs, int noutputs, int nInLinks, int nOutLinks);

    inline virtual void process() {};

    const int nInLinks;

    const int nOutLinks;

    std::vector<bool> linkReady;

    inline virtual float out_link(int link) {return -1;};

    inline virtual void in_link(int link, float value) {};


  public:
    //Procesa todas las entradas guardadas en el buffer que tendra que tener el tamaño adecuado
    //-1 error
    //0 procesado correctamente pero módulo no listo para output
    //>0 procesado y listo para output
    int processInput(ofSoundBuffer inputs);

    //Añade la entrada ninput y si puede procesa el audio
    //-1 error
    //0 valor correcto pero módulo no listo para output
    //>0 procesado y listo para output
    int processInput(int ninput, ofSoundBuffer input);

    int getOutput(ofSoundBuffer & output);

    int getOutput(ofSoundBuffer & output, int noutput);

    inline int getNoutputs() {return noutputs;};

    inline int getNinputs() {return ninputs;};

    void resetBuff(int numSamples);

    bool isOutReady();

    int updateLink(int nlink, float val);

    inline int getNInLinks() {return nInLinks;};

    float getLink(int nlink);

    inline int getNoutLinks() {return nOutLinks;};

    bool isLinkReady(int nlink);

};
#endif
