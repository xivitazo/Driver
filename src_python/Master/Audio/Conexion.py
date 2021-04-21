import numpy as np

#Cada una de la conexiones se compone de un vector input y un vector output.
#Los valores de cada vector representan [idModulo, Numero de entrada/salida]
#Las salidas y entradas del sistema se conectan mediante el idModulo=-1
class Conexion :
    def __init__ (self, input , output) :
        self.input=input
        self.output=output
        self.done=0