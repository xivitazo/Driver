#include "Master.h"
#include "Link/Link.h"
#include "Modulos/AllAudioMod.h"

Master::Master(int ninputs, int noutputs, string mat_port, int baud):
    ninputs(ninputs),
    noutputs(noutputs)
{
    output.setNumChannels(2*noutputs);
    matriz=new Matriz(mat_port,baud, 4,6);
    createModules();
    createLinks();
    links.update();
}

 Master::~Master()
 {
     for (int n=0;n<modulos.size();n++)
         delete modulos[n];
     for (int n=0;n<conexiones.size();n++)
         delete conexiones[n];
 }


 void Master::update()
 {
     matriz->update();
     links.updateFromMatr();
 }

 int Master::addLinkFromMatr(int x,int y, AudioMod *toLink, int nAudlink, int nMatrlink)
 {
    //return matriz->addLink(pos,link,nAudlink, nMatrlink);
     MatrixMod* mat_link = matriz->getModulo(x, y);
     if (mat_link==0)
         return -1;
     links.addFromMatr(mat_link,nMatrlink,toLink,nAudlink);
     return true;
 }

 int Master::addLinkFromAud(AudioMod* fromLink, int toPos[], int nAudLink, int nMatrLink)
 {
    //return matriz->addLink(pos,link,nAudlink, nMatrlink);
     MatrixMod* mat_link = matriz->getModulo(toPos[0], toPos[1]);
     if (mat_link==0)
         return -1;
     links.addFromAud(fromLink,nAudLink,mat_link,nMatrLink);
     return true;
 }

AudioMod *Master::getModulo(int pos)
{
    if (pos>=modulos.size())
        return 0;
    return modulos[pos];
}

 int Master::getOutput(ofSoundBuffer &output)
 {
     if (!isOutReady())
         return -1;
     output=this->output;
     return true;
 }

 int Master::processInput (ofSoundBuffer & input)
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

     for (int n=0; n<modulos.size();n++)
     {
         modulos[n]->resetBuff(inputs.size());
     }
     for (int n=0;n<conexiones.size();n++)
     {
         conexiones[n]->done=false;
     }


     for (int i=0;i<conexiones.size();i++)
     {
         if(conexiones[i]->input[0]==-1)
         {
             int ok;
             //Respresenta el modulo del que coges el buffer, si puede continuar, este pasará el testigo al siguiente módulo
             int modulo=-1;
             ok=modulos[conexiones[i]->output[0]]->processInput(conexiones[i]->output[1],*inputs[conexiones[i]->input[1]]);
             conexiones[i]->done=1;
             modulo=conexiones[i]->output[0];
             while(ok>0)
             {
                 for (int n=0;n<conexiones.size();n++)
                 {
                     if(conexiones[n]->input[0]==modulo && conexiones[n]->output[0]==-2)
                     {
                         ofSoundBuffer buff;
                         ofSoundBuffer left, right;
                         modulos[modulo]->getOutput(buff,conexiones[n]->input[1]);
                         buff.getChannel(left,0);
                         buff.getChannel(right,1);
                         output.setChannel(left,2*conexiones[n]->output[1]);
                         output.setChannel(right,2*conexiones[n]->output[1]+1);
                         ok=0;
                         conexiones[n]->done=1;
                     }
                     else if (conexiones[n]->input[0]==modulo )
                     {
                         ofSoundBuffer buff;
                         modulos[modulo]->getOutput(buff,conexiones[n]->input[1]);
                         ok=modulos[conexiones[n]->output[0]]->processInput(conexiones[n]->output[1],buff);
                         conexiones[n]->done=1;
                         modulo=conexiones[n]->output[0];
                         break;
                     }
                 }
             }
         }
     }



     while(!isOutReady())
     {
         for (int i=0;i<conexiones.size();i++)
         {
             if(conexiones[i]->done==0 && modulos[conexiones[i]->input[0]]->isOutReady())
             {
                 int ok;
                 int modulo=conexiones[i]->input[0];
                 do
                 {
                     for (int j=0;j<conexiones.size();j++)
                     {
                         if(conexiones[j]->input[0]==modulo && conexiones[j]->output[0]==-2)
                         {

                             ofSoundBuffer buff;
                             ofSoundBuffer left, right;
                             modulos[modulo]->getOutput(buff,conexiones[j]->input[1]);
                             buff.getChannel(left,0);
                             buff.getChannel(right,1);
                             output.setChannel(left,2*conexiones[j]->output[1]);
                             output.setChannel(right,2*conexiones[j]->output[1]+1);
                             conexiones[j]->done=1;
                             ok=0;
                             break;
                         }
                         else if (conexiones[j]->input[0]==modulo)
                         {
                             ofSoundBuffer buff;
                             modulos[modulo]->getOutput(buff,conexiones[j]->input[1]);
                             ok=modulos[conexiones[j]->output[0]]->processInput(conexiones[j]->output[1],buff);
                             modulo=conexiones[j]->output[0];
                             conexiones[j]->done=1;
                             break;
                         }
                     }
                 }while(ok>0);
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
     links.updateFomAud();
     return true;
 }

bool Master::isOutReady()
{
    /*for (int n=0;n<noutputs;n++)
        if(out_ready[n]==0)
            return 0;*/
    for (int n=0;n<conexiones.size();n++)
        if (conexiones[n]->output[0]==-2 && conexiones[n]->done==0)
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


void Master::createLinks()
{
    AudioMod* tolink =getModulo(0);
    //MatrixMod* fromlink = matriz->getModulo(1,6);
    int pos[2]={1,4};

    addLinkFromMatr(pos[0], pos[1],tolink,0,0);
}

void Master::createModules ()
{
   addModulo (new GainMod (1.0));
    addModulo (new GainMod (1.0));
    addModulo (new MixerMod (2));

    //int conexion1[2]={-1,0}, conexion2[2]={0,0}, conexion3[2]={-2,0};

    int entrada0[2]={-1,0}, entrada1[2]={-1,1};
    int salida0[2]={-2,0}, salida1[2]={-2,1};
    int modulo0_0[2]={0,0}, modulo1_0[2]={1,0};
    int modulo2_0[2]={2,0}, modulo2_1[2]={2,1};

    addConexion(entrada0, modulo0_0);
    addConexion(modulo0_0,modulo2_0);
    addConexion(entrada1, modulo1_0);
    addConexion(modulo1_0,modulo2_1);
    addConexion(modulo2_0, salida0);
    addConexion(modulo2_0, salida1);
}
