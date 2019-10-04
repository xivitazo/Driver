#ifndef MATRIZ_H
#define MATRIZ_H
#include "MatrixMod.h"
#include <vector>
#include <thread>
#include "ofSerial.h"


class Matriz
{
   std::vector <MatrixMod*> modulos;
   ofSerial serial;
   int addModule(int pos[2], char* message);
public:
    Matriz(char* port, int baud);
    Matriz();
    void setup (char* port, int baud);
    void update();
    int addLink(int pos[], AudioMod *Link, int nAudlink, int nMatrlink);
    //void writeSerial();
};

#endif // MATRIZ_H
