#include "Matriz.h"
#include "Potenciometro.h"
#include "Boton.h"

Matriz::Matriz(char* port, int baud)
{
    //pthread_mutex_init(&mtx, NULL);
    //pthread_mutex_lock(&mtx);
    ofSerialDeviceInfo device;

    //serial.listDevices();
    serial.setup(port,baud);
    //pthread_mutex_unlock(&mtx);
    char prueba[128];
    serial.readBytes(prueba, 128);
    serial.close();
    serial.setup(port, baud);

}
Matriz::Matriz()
{
    //pthread_mutex_init(&mtx, NULL);
}
void Matriz::setup(char *port, int baud)
{

    //pthread_mutex_lock(&mtx);
    ofSerialDeviceInfo device;

    serial.listDevices();
    serial.setup(port,baud);
    //pthread_mutex_unlock(&mtx);
}

int Matriz::addModule(int pos[], char *message)
{
    char init[128];
    int tipo ;
    sscanf(message,"%d %s", &tipo, init);
    float valor;
    int boton;
    switch (tipo) {
    case FADER:
        sscanf(init,"%f",&valor);
        modulos.push_back(new Potenciometro (pos , valor, FADER));
        return true;
        break;
    case KNOB:
        float valor;
        sscanf(init,"%f",&valor);
        modulos.push_back(new Potenciometro (pos , valor, KNOB));
        return true;
        break;
    case BOTON:
        sscanf(init,"%d",&boton);
        modulos.push_back(new Boton (pos , boton));
        return true;
    default:
        break;
    }
    return -1;
}


void Matriz::update()
{
    //pthread_mutex_lock(&mtx);
    int nread=0;
    int x,y;
    char bytes_serial[256], *info_mod;
    while ((nread=serial.readBytes(bytes_serial,256))>0)
    {
        sscanf(bytes_serial,"%d %d ,%s",&x, &y,info_mod);
        while(info_mod != "\0")
        {
            int n;
            int *pos[2];
            for (n=0; n<modulos.size();n++)
            {
                modulos[n]->getPos(pos);
                if (*pos[1]==x && *pos[2]==y)
                {
                    modulos[n]->serial_in(&info_mod);
                    break;
                }
            }
            if(n>=modulos.size())
            {
                addModule(*pos, info_mod);
                break;
            }
        }
    }
    //pthread_mutex_unlock(&mtx);
}

int Matriz::addLink(int pos[], AudioMod *Link, int nAudlink, int nMatrlink)
{
    for (int n=0;n<modulos.size();n++)
    {
        int *npos;
        modulos[n]->getPos(&npos);
        if (npos[0]==pos[0] && npos[1]==pos[1])
        {
            return modulos[n]->addInputLink(Link, nAudlink, nMatrlink);
        }
    }
    return -1;
}

/*void Matriz::writeSerial()
{
    //pthread_mutex_lock(&mtx);
   char* message;
   for (int n=0; n<modulos.size();n++)
   {
       modulos[n]->serial_out(&message);
   }
   if (message[0]=='\0')
   {
       //pthread_mutex_unlock(&mtx);
       return;
   }
   serial.writeBytes(message, sizeof(message));
   //pthread_mutex_unlock(&mtx);

}*/
