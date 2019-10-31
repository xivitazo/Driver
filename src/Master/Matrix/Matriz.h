#ifndef _MATRIZ_H
#define _MATRIZ_H


#include <string>
using namespace std;

class MatrixMod;

//#include "../Link.h"
class Matriz {
  private:
    std::vector<MatrixMod*> modulos;

    ofSerial serial;

    int addModule(int pos[2], char message[]);

    void onNewMessage(string & mensaje);

    void readSerial(__useconds_t delay);

    int tam[2];


  public:
    Matriz(string port, int baud, int xmax, int ymax);

    Matriz(int xmax, int ymax);

    void setup(char * port, int baud);

    void update();

    //int addLink(int pos[], AudioMod *Link, int nAudlink, int nMatrlink);
    MatrixMod * getModulo(int x, int y);

};
#endif
