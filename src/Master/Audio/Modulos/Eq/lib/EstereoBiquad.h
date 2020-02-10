//
//  EstereoBiquad.h
//
//  Created by Alonso de la Hera on 27/02/19
//  Etsit UPM
//  Copyright 2019
//
//
//

#ifndef EstereoBiquad_h
#define EstereoBiquad_h
#include <vector>
#include "Biquad.h"
class EstereoBiquad {
public:
    EstereoBiquad();
    EstereoBiquad(int type, double Fc, double Q, double peakGainDB);
    ~EstereoBiquad();
    void setType(int type);
    void setQ(double Q);
    void setFc(double Fc);
    void setPeakGain(double peakGainDB);
    void setEstereoBiquad(int type, double Fc, double Q, double peakGain);
	void process(float & in1, float & in2);
    
protected:
    Biquad *filtros[2];
};


#endif // EstereoBiquad_h