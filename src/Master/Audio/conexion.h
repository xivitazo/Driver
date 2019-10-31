#ifndef CONEXION_H
#define CONEXION_H
#include <vector>


class Conexion
{
public:
    Conexion(int input [2], int output [2]);
   // Conexion(int input [2], std::vector <int [2]> outputs);
    //Valor de la posicion del modulo en el vector
    //Entradas del sistema -1
    //Salidas del sistema -2
    int  input [2];
    int output [2];
    bool done;
};

#endif // CONEXION_H
