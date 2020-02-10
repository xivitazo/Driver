//
//  EstereoBiquad.cpp
//
//  Created by Alonso de la Hera on 27/02/19
//  Etsit UPM
//  Copyright 2019
//
//
//

#include <math.h>
#include "EstereoBiquad.h"
EstereoBiquad::EstereoBiquad() {
	filtros[0]= new Biquad();
	filtros[1]= new Biquad();
    
}

EstereoBiquad::EstereoBiquad(int type, double Fc, double Q, double peakGainDB) {
	filtros[0] = new Biquad(type, Fc, Q, peakGainDB);
	filtros[1] = new Biquad(type, Fc, Q, peakGainDB);
}

EstereoBiquad::~EstereoBiquad() {

}

void EstereoBiquad::setType(int type) {
    filtros[0]->setType(type);
    filtros[1]->setType(type);
}

void EstereoBiquad::setQ(double Q) {
    filtros[0]->setQ(Q);
    filtros[1]->setQ(Q);
}

void EstereoBiquad::setFc(double Fc) {
    filtros[0]->setFc(Fc);
    filtros[1]->setFc(Fc);
}

void EstereoBiquad::setPeakGain(double peakGainDB) {
    filtros[0]->setPeakGain(peakGainDB);
    filtros[1]->setPeakGain(peakGainDB);
}
    
void EstereoBiquad::setEstereoBiquad(int type, double Fc, double Q, double peakGainDB) {
    filtros[0]->setBiquad(type, Fc, Q, peakGainDB);
    filtros[1]->setBiquad(type, Fc, Q, peakGainDB);
}

void EstereoBiquad::process(float & in1, float & in2) {
   in1=filtros[0]->process(in1);
   in2=filtros[1]->process(in2);
   return;
}
