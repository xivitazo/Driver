#ifndef _GAINMOD_H
#define _GAINMOD_H


#include "AudioMod.h"

class GainMod : public AudioMod {
  private:
    float gain;

    virtual void process();

    virtual void update(int nlink, float val);

    virtual void in_link(int link, float value);


  public:
    GainMod(float gain);

};
#endif
