from Audio.Audio import Audio

#print(Audio.getDevices("NACON"))
audio=Audio(ioDevice="MAYA44")
audio.testLayout()
audio.run()