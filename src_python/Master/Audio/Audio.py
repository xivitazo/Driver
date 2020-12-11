import threading
import numpy as np
from .AudioMod.AudioMod import AudioMod
from .Conexion import Conexion
import sounddevice as sd
import time

class Audio :

    #Indica el estado de funcionamiento del Audio
    # == 0 Full Duplex - Mismo dispositivo de entrada que de salida (RECOMENDADO)
    # == 1 Asyncronous I/O - Dispositivos diferentes de entrada y salida
    status : bool


    # Inicializador de la clase Audio, para ello hay que meter los nombres de las tarjetas de sonido deseadas.
    # En caso de usar la misma para entrada y salida completar el argumento ioDevice para que se abra un stream full duplex
    # En caso de no rellenar los datos de canales se utilizarán los máximos canales estereo  permitidos del dispositivo de audio
    def __init__ (self, ioDevice = None, iDevice=None, oDevice=None, iChannels = None, oChannels=None, blockSize = None):
        if ioDevice !=None :
            self.device=sd.query_devices(ioDevice)
            print (self.device)

            self.status = 0

            if iChannels != None and 2*iChannels <= self.device['max_input_channels']:
                self.ninputs=iChannels
            elif True :
                self.ninputs=int(self.device['max_input_channels']/2)

            if oChannels != None and 2*oChannels <= self.device['max_output_channels']:
                self.noutputs=oChannels
            elif True :
                self.noutputs=int(self.device['max_output_channels']/2)

                              
            self.stream=sd.Stream(  device= self.device['name'],
                                    channels= (2*self.ninputs,2*self.noutputs),
                                    latency= (self.device['default_low_input_latency'],self.device['default_low_output_latency']),
                                    callback= self.ioCallback,
                                    blocksize = blockSize)
        elif ioDevice == None and iDevice != None and oDevice != None :
            self.idevice=sd.query_devices(iDevice)
            self.odevice=sd.query_devices(oDevice)

            self.status = 1

            if iChannels != None and 2*iChannels <= self.idevice['max_input_channels']:
                self.ninputs=iChannels
            elif True :
                self.ninputs=int(self.idevice['max_input_channels']/2)

            if oChannels != None and 2*oChannels <= self.odevice['max_output_channels']:
                self.noutputs=oChannels
            elif True :
                self.noutputs=int(self.odevice['max_output_channels']/2)
                
            if self.idevice['default_samplerate'] <= self.odevice['default_samplerate']:
                samplerate = int(self.idevice['default_samplerate'])
            elif self.idevice['default_samplerate'] > self.odevice['default_samplerate']:
                samplerate = int(self.idevice['default_samplerate'])

            if blockSize == None:
                blockSize = 255
            

            sd.default.device=iDevice,oDevice
            sd.default.samplerate=samplerate
            sd.default.channels=2*self.ninputs,2*self.noutputs
            sd.default.latency='low','low'
            sd.default.blocksize=blockSize
            sd.default.never_drop_input=True


            self.istream = sd.InputStream(device= iDevice ,callback= self.iCallback)
            self.ostream = sd.OutputStream(device= iDevice, callback=self.oCallback)
            
            self.iEvent=threading.Event()
            self.oEvent=threading.Event()
            self.oEvent.set()
        
        
        self.runEvent=threading.Event()
        self.outputBuff=np.empty ([0, 2*self.noutputs])
        self.modulos=[]
        self.conexiones=[]
    def __del__(self):
        if self.status == 0:
            self.stream.close()
        elif self.status == 1:
            self.istream.close()
            self.ostream.close()
    def run (self) :
        if self.status == 0 :
            self.runEvent.clear()
            self.stream.start()
            while True:
                time.sleep(0.5)
                if self.runEvent.is_set():
                    break
            self.stream.stop()
        elif self.status == 1 :
            self.runEvent.clear()
            self.istream.start()
            self.ostream.start()
            while True:
                time.sleep(0.5)
                if self.runEvent.is_set():
                    break  
            self.istream.stop()
            self.ostream.stop()

    def getDevices (device = None) :
        return sd.query_devices(device)

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
    
    def ioCallback (self, indata, outdata, frames, time, status) :
        if status :
            print(status)
        print("ioCallback")
        self.processInput(indata)
        outdata[:]=self.getOutput()[:]
    def iCallback (self, indata, frames, time, status):
        if status :
            print(status)
        print("iCallback")
        self.oEvent.wait()
        self.oEvent.clear()
        self.processInput(indata)
        self.iEvent.set()
    def oCallback(self, outdata, frames, time, status):
        if status :
            print(status)
        
        print("oCallback")
        self.iEvent.wait()
        self.iEvent.clear()
        outdata[:]=self.getOutput()[:]
        self.oEvent.set()
    
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

                            self.outputBuff [:,2*x.output[1]:2*x.output[1]+2]=input[:,2*x.input[1]:2*x.input[1]+2]
                            continue

                        e=threading.Event()
                        t= threading.Thread (target=self.modulos[x.output[0]].processInput, args=(input[:,2*x.input[1]:2*x.input[1]+2], x.output[1], e))
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
    def getOutput (self):
        if not self.isOutReady() :
            return -1
        return self.outputBuff
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