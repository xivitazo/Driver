import sounddevice as sd
import numpy as np
import sys
from Audio.Audio import Audio

#device=sd.query_devices('MAYA44')
duration = 5 #seconds
print(sd.query_devices())
print (device)

def callback(indata, outdata, frames, time, status):
    if status:
        print(status)

    #print(sys.getsizeof(indata))
    audio.processInput(indata)
    outdata [:]=audio.getOutput()
    #print(indata)
    #outdata[:] = indata
    #print(str(outdata.shape))
    #print()

stream=sd.Stream(   samplerate=device['default_samplerate'], 
                    device=device['name'], 
                    channels=(device['max_input_channels'],device['max_output_channels']), 
                    latency=(device['default_low_input_latency'],device['default_low_output_latency']+(device['default_high_output_latency']-device['default_low_output_latency'])/5), 
                    never_drop_input=True,
                    callback=callback
                )

#audio=Audio(2,2)
#with stream:
    #for x in range(2):
        #print(sd.get_status())
        #sd.sleep(int(duration*1000))
