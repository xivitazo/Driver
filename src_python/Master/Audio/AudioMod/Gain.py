from .AudioMod import AudioMod


#Solo sería necesario esto para hacer un efecto de audio
#Faltaría todo el tema de los links y configurar que hacen que eso si será un poco más de lío
class Gain (AudioMod):
    def __init__ (self):
        AudioMod.__init__ (self,1,1,1,0)
        self.multiply=1.0

    def process (self) :
        self.outputBuff[:,:] = self.multiply*self.inputBuff[:,:]

    def linkIn (self,nlink :int, value):
        self.multiply=value
          
    def linkOut (self, nlink:int):
        return -1