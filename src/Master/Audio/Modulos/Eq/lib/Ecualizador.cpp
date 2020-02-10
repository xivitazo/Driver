//
//  Ecualizador.cpp
//
//  Created by Alonso de la Hera on 27/02/19
//  Etsit UPM
//  Copyright 2019
//
//

#include <math.h>
#include "Ecualizador.h"

Ecualizador::Ecualizador() {

}

Ecualizador::Ecualizador(int numero_bandas) {
    if(numero_bandas>BANDAS_MAX){
        bandas = BANDAS_MAX;
    }else{
        bandas = numero_bandas;
    }
	//std::cout << "Calcula Constantes!\n";
    numero_filtros=(bandas*2)-2;
    aux0=(2.66/8)*(bandas-5);
	//std::cout <<"Aux0 -> "<< aux0 <<" !\n";
    alpha=2-aux0;
	//std::cout << "alpha -> " << alpha << " !\n";
    constant=4-aux0;
	//std::cout << "constant -> " << constant << " !\n";
	aux1 = pow(2, alpha);
	for (int i = 0; i < numero_filtros; i++) {
		filtros[i] = new EstereoBiquad();
	}
    for(int i=0;i< BANDAS_MAX-1;i++){
		if (i < bandas-1) {
			if (i == 0) {
				aux2 = 1;
			}
			else {
				aux2 = pow(constant,i);
			}
			//std::cout << "aux2 -> " << aux2 << " !\n";
			frecuencias_corte[i] = 31.5 * aux1 * (aux2);
		}
		else {
			frecuencias_corte[i] = 0.0;
		}
		//std::cout << "Fc["<< i << "]= " << frecuencias_corte[i] << " !\n";
    }
	Q[0] = 1 / 2;
    for(int i=0;i< BANDAS_MAX-1;i++){
		if(i==bandas-2){
            Q[i]=(20000-frecuencias_corte[i])/(2*frecuencias_corte[i]);
			//std::cout << "Si \n";
        }else if (i<bandas-2){
            Q[i]=(frecuencias_corte[i+1]-frecuencias_corte[i])/(2*frecuencias_corte[i]);
			//std::cout << "No \n";
		}
		else {
			Q[i] = 0.0;
		}
		//std::cout << "Q[" << i << "]= " << Q[i] << " !\n";
    }
	//std::cout << "Numero de Filtros: " << numero_filtros << " \n";
    filtros[0]-> setEstereoBiquad(bq_type_lowshelf, frecuencias_corte[0], Q[0], 0);
	//std::cout << "Set First \n";
    filtros[1]-> setEstereoBiquad(bq_type_highshelf,frecuencias_corte[bandas-1],Q[bandas-1], 0);
	//std::cout << "Set Last \n";
    for (int i=0;i<bandas-2;i++){
		//std::cout << "It " << i << " \n";
        filtros[2*i+2]-> setEstereoBiquad(bq_type_highshelf,frecuencias_corte[i],Q[i], 0);
		//std::cout << "Set "<< 2 * i + 2 <<" \n";
        filtros[2*i+3]-> setEstereoBiquad(bq_type_lowshelf,frecuencias_corte[i+1],Q[i], 0);
		//std::cout << "Set " << 2 * i + 3 << " \n";
    }
	//std::cout << "Done Set \n";
}

Ecualizador::~Ecualizador() {
}


void Ecualizador::setGain(int banda, double gainDB) {
    if(banda==0){
        filtros[0]->setPeakGain(gainDB);
    }else if(banda==bandas - 2){
        filtros[bandas - 2]->setPeakGain(gainDB);
    }else if(banda<bandas - 2){
        filtros[2* banda +2]->setPeakGain(gainDB);
        filtros[2* banda +3]->setPeakGain(gainDB);
    }else{
        return;
    }
}

void Ecualizador::setFc(int banda, double Fc) {
    if(banda==0){
        filtros[0]->setFc(Fc);
    }else if(banda==bandas - 2){
        filtros[bandas - 2]->setFc(Fc);
    }else if(banda<bandas - 2){
        filtros[2* banda +2]->setFc(Fc);
        filtros[2* banda +3]->setFc(Fc);
    }else{
        return;
    }
}
void Ecualizador::setQ(int banda, double Q) {
    if(banda==0){
        filtros[0]->setQ(Q);
    }else if(banda==bandas - 2){
        filtros[bandas - 2]->setQ(Q);
    }else if(banda<bandas - 2){
        filtros[2* banda +2]->setQ(Q);
        filtros[2* banda +3]->setQ(Q);
    }else{
        return;
    }
}
    
/*void Ecualizador::setEcualizador(int type, double Fc, double Q, double peakGainDB) {
    this->type = type;
    this->Q = Q;
    this->Fc = Fc;
    setPeakGain(peakGainDB);
}*/


void Ecualizador::process(float & in1, float & in2) {
	//aux3 = in1;
	//aux4 = in2;
    for (int i=0;i<numero_filtros;i++){
        filtros[i]->process(in1,in2);
    }
    //return aux3;
	return;
}



