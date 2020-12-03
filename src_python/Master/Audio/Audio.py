import threading
import numpy as np
from .AudioMod.AudioMod import AudioMod
from .Conexion import Conexion

class Audio :
    def __init__ (self, ninputs : int, noutputs : int):
        self.ninputs=ninputs
        self.noutputs=noutputs
        self.outputBuff=np.empty ([0, 2*noutputs])
        self.modulos=[]
        self.conexiones=[]
        self.testLayout()
    def getOutput (self):
        if not self.isOutReady() :
            return -1
        return self.outputBuff
    def processInput (self, input):
        if (input.shape[1] != 2*self.ninputs):
            return -1
        #Reseteo y preparacion de todos los buffer y conexiones para una nueva ronda de procesado
        for x in self.modulos :
            x.resetBuff(input.shape[0])
        self.outputBuff.resize(input.shape[0], 2*self.noutputs)
        self.outputBuff[:,:]=0
        for x in self.conexiones :
            x.done = 0

        
        #Bucle de procesamiento para cada uno de los modulos individuales de audio a traves de sus conexiones
        #Primero buscamos todas las conexiones con los canales de entrada y se realizan, así como los procesamuientos posibles
        threads = []
        while True :
            
            #Primero se hace una pasada por las conexiones entre los modulos
            #Realiza todas las que puede y lanza cada uno de los threads a los modulos correspondientes
            for x in self.conexiones:
                if x.done == 0:
                    #En caso de que la conexion venga de una entrada general del sistema, la conexion se reliza directamente
                    # se intenta procesar el audio en un nuevo thread y se guarda el id de este
                    if x.input[0] == -1 :
                        x.done=1
                        if x.output[0] == -1 :

                            self.outputBuff [:,2*x.output[1]:2*x.output[1]+2]=self.modulos[x.input[0]].getOutput(x.input[1])
                            continue

                        e=threading.Event()
                        t= threading.Thread (target=self.modulos[x.output[0]].processInput, args=(input[:,x.input[1]:x.input[1]+2], x.output[1], e))
                        threads.append([t,e])
                        t.start()
                        continue
                    #En caso de que la conexion venga de un modulo habra que comprobar si el modulo de entrada tiene el buffer listo
                    #Si es asi se añade el nuevo buffer al módulo y se intenta procesar el audio
                    #Si no no se ejecuta la conexion y se sigue en la busqueda de conexiones realizables
                    elif x.input[0] >=0 :
                        if  not self.modulos[x.input[0]].isOutReady() :
                            continue
                        #Se comprueba si la salida de la conexion actual va a las salidas del sistema
                        #Si es asi se copia el buffer de la entrada de la conexion al buffer de la salida del sistema
                        if x.output[0] == -1 :
                            x.done=1

                            self.outputBuff [:,2*x.output[1]:2*x.output[1]+2]=self.modulos[x.input[0]].getOutput(x.input[1])
                            continue
                        #En caso de que sea una conexion entre modulos de audio se realiza la conexion del buffer y se procesa el audio si es poosible
                        x.done=1

                        e=threading.Event()
                        t=threading.Thread (target=self.modulos[x.output[0]].processInput, args=(self.modulos[x.input[0]].getOutput(x.input[1]), x.output[1], e))
                        threads.append([t,e])
                        t.start()
                        continue
            
            #A continuacion se gestiona la comunicacion con los threads para no dejar ningun hijo a medias y asegurar que todos los modulos conectados procesan audio
            processed=0
            #TO DO: Faltaria gestionar si algun proceso se queda vivo mas de lo normal, para asi intentar resetearlo o mandar mensaje de error
            #TO DO: Faltaría gestionar los returns de cada modulo para confirmar que se ha realizado correctamente

            for x in threads :
                if x[1].isSet() :
                    x[0].join()
                    threads.remove(x)
                    processed+=1
                    continue
            
            if processed==0 and len(threads)==0 and self.isOutReady() :
                
                break
            
         
        return True
    def getModulo (self, pos : int) :
        if pos >= len(self.modulos):
            return -1
        return self.modulos[pos]
    def addModulo (self, modulo : AudioMod):
        self.modulos.append(modulo)
    def addConexion (self, input :[], output : []):
        if  input[0] == -1 and input[1] >= self.ninputs :
            return -1
        elif input[0] >= len(self.modulos):
            return -1
        elif input[1] >= self.modulos[input[0]].noutputs:
            return -1
        self.conexiones.append(Conexion(input,output))
        return True
    def isOutReady (self):
        for x in self.conexiones:
            if x.output[0]==-1 and x.done==0 :
                return False
        return True



    def testLayout (self):
        self.addModulo(AudioMod(2,2,0,0))
        self.addConexion([-1,0],[0,0])
        self.addConexion([-1,1],[0,1])
        self.addConexion([0,0],[-1,0])
        self.addConexion([0,1],[-1,1])