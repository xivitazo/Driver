
#include "Matriz.h"
#include "MatrixMod.h"

void Matriz::onNewMessage() {

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

void Matriz::readSerial() {

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

Matriz::Matriz() {

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

Matriz::Matriz() {

    tam[0]=xmax;
    tam[1]=ymax;
    //pthread_mutex_init(&mtx, NULL);
}

void Matriz::setup() {




    serial.setup(port,baud);
    //serial.startContinuousRead();
    //ofAddListener(serial.NEW_MESSAGE,this,&Matriz::onNewMessage);
    //pthread_mutex_unlock(&mtx);
}

void Matriz::update() {


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

//int addLink(int pos[], AudioMod *Link, int nAudlink, int nMatrlink);
MatrixMod Matriz::getModulo() {

    for (int n=0; n<modulos.size();n++)
    {
        int pos[2];
        modulos[n]->getPos(pos[0],pos[1]);
        if (pos[0]==x && pos [1]==y)
            return modulos[n];
    }
    return 0;
}

