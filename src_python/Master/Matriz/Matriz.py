from MatrizMod.MatrizMod import MatrizMod

#La idea es implementar tu código aqui
# Hacer que cuando salte una evento en la matriz lo pases mediante la funcion MatrizMod.readSerial() que esta preparada para concurrencia
#Puedes modificar todo el tema de argumentos y demas para hacer que funcione como crees, pero estaría bien que la estructura mas o menos se mantuviese
class Matriz :
    modulos=[]
    def __init__ (self, port, baud, shape : []) :
        self.shape=[]
        self.shape[:]= shape

    def addModule (self, modulo : MatrizMod) :
        self.modulos.append(modulo)

    def readSerial (self) :
        #Aqui manejas toda la lectura del puerto y cuando recibes algo lanzas la funcion del modulo correspondiente
        pass

