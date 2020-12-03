from .AudioMod import AudioMod


#Solo sería necesario esto para hacer un efecto de audio
#Faltaría todo el tema de los links y configurar que hacen que eso si será un poco más de lío
class Gain (AudioMod):
    def __init__ (self):
        AudioMod (1,1,1,1)

    def process (self) :
        self.outputBuff[:,:] = self.inputBuff