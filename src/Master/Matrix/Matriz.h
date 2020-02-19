#ifndef MATRIZ_H
#define MATRIZ_H
#include "MatrixMod.h"
#include <vector>
#include <thread>
#include "ofSerial.h"
#include "ofUtils.h"
//#include "../Link.h"


class Matriz
{
   std::vector <MatrixMod*> modulos;
   ofSerial serial;
   int addModule(int pos[2], char message[]);
   void onNewMessage (string & mensaje);
   void readSerial (__useconds_t delay);
   int tam[2];
public:
    Matriz(string port, int baud, int xmax, int ymax);
    Matriz(int xmax, int ymax);
    ~Matriz();
    void setup (char* port, int baud);
    void update();
    //int addLink(int pos[], AudioMod *Link, int nAudlink, int nMatrlink);
    MatrixMod* getModulo(int x, int y);
    //void writeSerial();
};

#endif // MATRIZ_H
