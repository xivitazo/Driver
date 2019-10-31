#include "conexion.h"

Conexion::Conexion(int input [2], int output [2])
{
    this->input[0]=input[0];
    this->input[1]=input[1];
    this->output[0]=output[0];
    this->output[1]=output[1];
    done=false;
}
