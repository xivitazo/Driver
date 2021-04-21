import sounddevice as sd
import numpy as np
import sys

device=sd.query_devices('MAYA44')
duration = 5 #seconds
print (device)
def callback(indata, outdata, frames, time, status):
    if status:
        print(status)
    #print(indata)
    outdata[:] = indata
    #print(outdata)
    #print(sys.getsizeof(indata))
    #print()

stream=sd.Stream(   samplerate=device['default_samplerate'], 
                    device=device['name'], 
                    channels=(device['max_input_channels'],device['max_output_channels']), 
                    latency=(device['default_low_input_latency'],device['default_low_output_latency']), 
                    never_drop_input=True,
                    callback=callback
                )

with stream:
    for x in range(5):
        #print(sd.get_status())
        sd.sleep(int(duration*1000))
    
 
#sd.Stream.start()