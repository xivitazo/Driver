#include "Matriz.h"
#include "Potenciometro.h"
#include "Boton.h"
#include "ofFileUtils.h"
#include <unistd.h>

Matriz::Matriz(string port, int baud, int xmax, int ymax)
{
    tam[0]=xmax;
    tam[1]=ymax;
    //pthread_mutex_init(&mtx, NULL);
    //pthread_mutex_lock(&mtx);
    //ofSerialDeviceInfo device;

    //serial.listDevices();
    serial.setup(port,baud);
    //serial.startContinuousRead();
    //ofAddListener(serial.NEW_MESSAGE,this,&Matriz::onNewMessage);
    //pthread_mutex_unlock(&mtx);
    usleep(1000000);
    readSerial(500000);
    //usleep(1000000);

}
Matriz::Matriz(int xmax, int ymax)
{
    tam[0]=xmax;
    tam[1]=ymax;
    //pthread_mutex_init(&mtx, NULL);
}

void Matriz::onNewMessage (string & mensaje)
{
    int x,y;
    int val;
    //sscanf(line.data(),"%d %d , %d", &x, &y, &val );
    vector <string> input=ofSplitString(mensaje, ",");
    if (input.size() >= 3)
    {
        x=atoi(&input[0][0]);
        y=atoi(&input[1][0]);
        val=atoi(&input[2][0]);

        /*x= input.at(0);
        y= input.at(1);
        val= input.at(2);*/
    }
    else
        return;
    if  (x>tam[0] || y>tam[1])
    {
        printf ("error de lectura en el puerto serie\n");
        return;
    }

    int n;
    int pos[2];
    float f_val=(float)val/1024;
    for(n=0; n<modulos.size();n++)
    {
        modulos[n]->getPos(pos[0],pos[1]);
        if(pos[0]==x && pos[1]==y)
        {
            modulos[n]->readSerial(0,f_val);
            cout<<"Lectura correcta, escrito sobre el modulos posicion "<<pos[0]<<","<<pos[1]<<", numero "<<n<<" en lista con valor "<<f_val<<endl;
            break;
        }
    }
    if (n>=modulos.size())
    {

        pos[0]=x;
        pos[1]=y;
        modulos.push_back(new Potenciometro(pos,f_val, KNOB));
    }
}
void Matriz::setup(char *port, int baud)
{



    serial.setup(port,baud);
    //serial.startContinuousRead();
    //ofAddListener(serial.NEW_MESSAGE,this,&Matriz::onNewMessage);
    //pthread_mutex_unlock(&mtx);
}

int Matriz::addModule(int pos[], char message[])
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

void Matriz::readSerial (__useconds_t delay)
{
    serial.writeByte('r');
    int nread;
    ofBuffer buff;
    buff.allocate(512);
    usleep(delay);
    while(nread=serial.readBytes(buff, 512)>0)
    {
        string linea;
        do
        {
            linea=buff.getNextLine();
            onNewMessage(linea);

        }while(!buff.isLastLine());
    }
}

MatrixMod* Matriz::getModulo(int x, int y)
{
    for (int n=0; n<modulos.size();n++)
    {
        int pos[2];
        modulos[n]->getPos(pos[0],pos[1]);
        if (pos[0]==x && pos [1]==y)
            return modulos[n];
    }
    return 0;
}

void Matriz::update()
{

    readSerial(100);

    //pthread_mutex_lock(&mtx);
    /*int nread=0;
    int x,y;
    char bytes_serial[256], info_mod[128];
    while ((nread=serial.readBytes(bytes_serial,256))>0)
    {
        sscanf(bytes_serial,"%d %d ,%s\n",&x, &y,info_mod);
        while(info_mod != "\0")
        {
            int n;
            int *pos[2];
            for (n=0; n<modulos.size();n++)
            {
                modulos[n]->getPos(pos);
                if (*pos[1]==x && *pos[2]==y)
                {
                    modulos[n]->serial_in(&info_mod[0]);
                    break;
                }
            }
            if(n>=modulos.size())
                addModule(*pos, info_mod);
        }
    }*/
    //pthread_mutex_unlock(&mtx);
}

/*int Matriz::addLink(int pos[], AudioMod *Link, int nAudlink, int nMatrlink)
{
    for (int n=0;n<modulos.size();n++)
    {
        int npos[2];
        modulos[n]->getPos(npos[0], npos[1]);
        if (npos[0]==pos[0] && npos[1]==pos[1])
        {
            return modulos[n]->addInputLink(Link, nAudlink, nMatrlink);
        }
    }
    return -1;
}*/

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
