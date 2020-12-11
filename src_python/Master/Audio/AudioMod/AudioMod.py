from threading import  Lock, Event
import numpy as np
from .BaseMod import BaseMod

class AudioMod (BaseMod) :
    
    def __init__ (self, ninputs : int , noutputs : int, nInlinks : int, nOutLinks:int):
         
        BaseMod.__init__ (self,nInlinks, nOutLinks)
        self.ninputs=ninputs
        self.noutputs=noutputs
        self.inputLock=np.zeros([ninputs],bool)
        self.outputBuff=np.empty([0,2*self.noutputs])
        self.inputBuff=np.empty([0,2*self.noutputs])

    #Procesa todas las entradas guardadas en el buffer que tendra que tener el tamaño adecuado
    #-1 error
    #0 procesado correctamente pero módulo no listo para output
    #>0 procesado y listo para output 
    def processInputs (self, inputs : np, e=0) : 
        self.mtx.acquire()
        if (inputs.shape[1]==2*self.ninputs):   
            self.inputBuff=inputs
            self.inputLock[:]=1
            self.process()
            self.mtx.release()
            if e!= 0 :
                e.set()
            return 1
        self.mtx.release()
        if e!= 0 :
            e.set()
        return -1 
    def processInput (self, input : np, ninput:int, e=0) :
        self.mtx.acquire()
        if (ninput >= self.ninputs or input.shape[1] != 2 or input.shape[0] != self.inputBuff.shape[0] or self.inputLock[ninput] == 1):
            self.mtx.release()
            if e!= 0 :
                e.set()
            return -1
        self.inputLock[ninput]=1
        self.inputBuff[:,2*ninput:2*ninput+2]=input[:,:]
        for x in self.inputLock :
            if x == 0:
                self.mtx.release()
                if e!= 0 :
                    e.set()
                return 0
        self.process()
        if e!= 0 :
            e.set()
        self.mtx.release()
        return 1  
    def getOutputs (self):
        self.mtx.acquire()
        outputs= np.zeros(self.outputBuff.shape)
        outputs [:]=self.outputBuff
        self.mtx.release()
        return outputs
    def getOutput (self, noutput : int):
        output=np
        self.mtx.acquire()
        output.empty ([self.outputBuff.shape[0], 2])
        output = self.outputBuff[:,2*noutput:2*noutput+2]
        self.mtx.release()
        return output
    def resetBuff (self, numSamples : int) :
        self.mtx.acquire()
        self.outputBuff.resize(numSamples, 2*self.noutputs)
        self.inputBuff.resize(numSamples, 2*self.ninputs)
        self.outputBuff[:,:]=0
        self.inputBuff[:,:]=0
        self.inputLock[:]=0
        self.mtx.release()
    def process (self):
        if self.ninputs == self.noutputs :
            self.outputBuff [:,:] =self.inputBuff[:,:]
    def isOutReady (self):
        self.mtx.acquire()
        for x in self.inputLock :
            if x == 0:
                self.mtx.release()
                return False
        self.mtx.release()
        return True
