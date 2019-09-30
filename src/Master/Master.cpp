#include "Master.h"

Master::Master(int ninputs, int noutputs):
    ninputs(ninputs),
    noutputs(noutputs)
{
    output.setNumChannels(2*noutputs);
}

 Master::~Master()
 {
     for (int n=0;n<modulos.size();n++)
         delete modulos[n];
     for (int n=0;n<conexiones.size();n++)
         delete conexiones[n];
 }


 int Master::getOutput(ofSoundBuffer &output)
 {
     if (!isOutReady())
         return -1;
     output=this->output;
     return true;
 }

int Master::processInput (ofSoundBuffer input)
{
    std::vector <ofSoundBuffer*> inputs;

    //Guardamos cada canal de entrada en un buffer distinto
    for (int n=0;n<ninputs;n++)
    {
        inputs.push_back(new ofSoundBuffer);
        ofSoundBuffer left, right;
        input.getChannel(left,2*n);
        input.getChannel(right,2*n+1);
        inputs[n]->allocate(input.size(),2);
        inputs[n]->setChannel(left,0);
        inputs[n]->setChannel(right,1);
    }

    //procesamos el audio de módulo a módulo empezando por las entradas
    //outbuff.assign(modulos.size(),0);


    for (int i=0;i<conexiones.size();i++)
    {
        if(conexiones[i]->input[0]==-1)
        {
            int ok;
            int modulo=conexiones[i]->output[0];
            int puerto=conexiones[i]->output[1];
            ok=modulos[modulo]->processInput(conexiones[i]->output[1],*inputs[conexiones[i]->input[1]]);
            conexiones[i]->done=1;
            while(ok>0)
            {
                for (int j=0;j<conexiones.size();j++)
                {
                    if(conexiones[j]->input[0]==modulo && conexiones[j]->output[0]!=-2)
                    {
                        ofSoundBuffer buff;
                        modulos[modulo]->getOutput(buff,puerto);
                        ok=modulos[conexiones[j]->output[0]]->processInput(conexiones[j]->output[1],buff);
                        modulo=conexiones[j]->output[0];
                        conexiones[j]->done=1;
                        break;
                    }
                    else if (conexiones[j]->input[0]==modulo)
                    {
                        ofSoundBuffer buff;
                        ofSoundBuffer left, right;
                        modulos[modulo]->getOutput(buff,puerto);
                        buff.getChannel(left,0);
                        buff.getChannel(right,1);
                        output.setChannel(left,2*conexiones[j]->output[1]);
                        output.setChannel(right,2*conexiones[j]->output[1]+1);
                        ok=0;
                        conexiones[j]->done=1;

                    }
                }
            }
        }
    }

    while(isOutReady())
    {
        for (int i=0;i<conexiones.size();i++)
        {
            if(conexiones[i]->done==0)
            {
                if (modulos[conexiones[i]->input[0]]->isOutReady())
                {
                    ofSoundBuffer buff;
                    int ok;
                    int modulo=conexiones[i]->output[0];
                    int puerto=conexiones[i]->output[1];
                    modulos[conexiones[i]->input[0]]->getOutput(buff);
                    ok=modulos[modulo]->processInput(conexiones[i]->output[1],buff);
                    conexiones[i]->done=1;
                    while(ok>0)
                    {
                        for (int j=0;j<conexiones.size();j++)
                        {
                            if(conexiones[j]->input[0]==modulo && conexiones[j]->output[0]!=-2)
                            {
                                ofSoundBuffer buff;
                                modulos[modulo]->getOutput(buff,puerto);
                                ok=modulos[conexiones[j]->output[0]]->processInput(conexiones[j]->output[1],buff);
                                modulo=conexiones[j]->output[0];
                                conexiones[j]->done=1;
                                break;
                            }
                            else if (conexiones[j]->input[0]==modulo)
                            {
                                ofSoundBuffer buff;
                                ofSoundBuffer left, right;
                                modulos[modulo]->getOutput(buff,puerto);
                                buff.getChannel(left,0);
                                buff.getChannel(right,1);
                                output.setChannel(left,2*conexiones[j]->output[1]);
                                output.setChannel(right,2*conexiones[j]->output[1]+1);
                                ok=0;
                                conexiones[j]->done=1;

                            }
                        }
                    }
                }
            }
        }
    }


    /*for(int n=0;n<ninputs;n++)
    {
        std::vector <int [2]> next ;
        //entramos en el primer bloque después de las entradas
        int a=modulos[inputlink[n][0]]->processInput(inputlink[n][1],inputs[n]);
        while(next[0][0]>=1)
        {
            *//*if(next.size>1)
            {
                for (int n=0;n<next.size();n++)
                {

                }
            }*//*
            modulos[next[0][0]]->process(next[0][1],outbuff[0], outbuff, next);

        }
        if (next[0][0]==1)
        {
            ofSoundBuffer left, right;
            outbuff[0].getChannel(left,0);
            outbuff[0].getChannel(right,1);
            output.setChannel(left,next[0][1]*2);
            output.setChannel(right,next[0][1]*2+1);
        }

    }*/
    for (int n=0;n<ninputs;n++)
    {
        delete inputs[n];
    }
    return true;
}

bool Master::isOutReady()
{
    /*for (int n=0;n<noutputs;n++)
        if(out_ready[n]==0)
            return 0;*/
    for (int n=0;n<conexiones.size();n++)
        if (conexiones[n]->output[0]==-2 && conexiones[n]->done==1)
            return false;
    return true;
}

int Master::addModulo (AudioMod *modulo)
{
    modulos.push_back(modulo);
    return modulos.size()-1;
}

int Master::addConexion(int input[2], int output[2])
{
    if(input[0]==-1 &&
            input[1]>=ninputs)
        return -1;
    else if (input[0]==-1);
    else if(input[0]>=modulos.size() &&
            input[1]>=modulos[input[0]]->getNoutputs())
        return -1;
    if(output[0]==-2&&
                output[1]>=noutputs)
            return -1;
    else if(output[0]==-2);
    else if(output[0]>=modulos.size()&&
            output[1]>=modulos[output[0]]->getNinputs() &&
            output[0]!=-2)
        return -1;
    conexiones.push_back(new Conexion(input,output));
    return true;
}
