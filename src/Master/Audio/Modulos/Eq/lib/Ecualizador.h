//
//  Ecualizador.h
//
//  Created by Alonso de la Hera on 27/02/19
//  Etsit UPM
//  Copyright 2019
//
//

#ifndef Ecualizador_h
#define Ecualizador_h

#include "EstereoBiquad.h"
#include <iostream>
//#include <vector>

#define BANDAS_MAX 11

class Ecualizador {
public:
    Ecualizador();
    Ecualizador(int numero_bandas);
    ~Ecualizador();
    void setGain(int banda, double gain);
    void setFc(int banda, double Fc);
    void setQ(int banda, double Q);
    //void setEcualizador(int type, double Fc, double Q, double peakGain);
    void process(float & in1, float & in2);
    int getBandas(){return bandas;}
    
protected:
    int numero_filtros;
    int bandas;
    double aux0,aux1,aux2;
    //float aux3, aux4;
    double alpha, constant;
    double frecuencias_corte[BANDAS_MAX-1];
    double Q[BANDAS_MAX-1];
    //vector<EstereoBiquad*>filtros[(int)(BANDAS_MAX*2)-2];
	EstereoBiquad *filtros[(int)(BANDAS_MAX * 2) - 2];
};


#endif // Ecualizador_h
