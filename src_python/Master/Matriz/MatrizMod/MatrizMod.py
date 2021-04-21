from threading import Lock, Event
import numpy as np

class MatrizMod :
    #El tema de los links es lo que se usa para comunicar entre modulos linkeables.
    #Es lo que te explicaba que tenfo que hacer la clase megapadre con todas las funciones y sobrecargarlas en cada clase base de módulo
    def __init__ (self, pos : [], tipoModulo, ninlinks, noutlinks) :
        self.mtx=Lock()
        self.pos = []
        self.pos[:]=pos
        self.tipoModulo=tipoModulo
        self.ninlinks=ninlinks
        self.noutlinks=noutlinks
        self.linkReady=np.zeros([self.noutlinks])

    #Esta es la funcion que se programa en el hijo de cada modulo
    #la idea es que la creacion de un modulo sea sencilla y solo tengas que programar lo que quieres que haga, que no te tengas que meter a nada de concurrencia ni de puertos serie ni nada
    def serial_in (self, link :int, mensaje):
        return mensaje

    def readSerial (self, link :int, mensaje, e =0):
        self.mtx.acquire()
        if link >= self.ninlinks :
            self.mtx.release()
            if e != 0:
                e.set()
            return -1
        response=self.serial_in(link, mensaje)
        self.linkReady[link]=1
        self.mtx.release()
        if e != 0:
            e.set()
        return response    
