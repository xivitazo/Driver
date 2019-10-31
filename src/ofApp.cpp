#include "ofApp.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h> //para mmap
#include <fstream> //para open
#include <fcntl.h> //para O_RDWR
#include "Master/Audio/Modulos/AllAudioMod.h"



//--------------------------------------------------------------




//--------------------------------------------------------------
void ofApp::setup(){

    //soundcardIN = "MAYA44";

    soundcardIN = "MAYA44";
    soundcardOUT="MAYA44";
    nInput = 4;
    nOutput = 4;
    mat_port="/dev/ttyACM0";
    baud=115200;

    soundStream.printDeviceList();

    ofSoundStreamSettings settings;


    //Inicializacion de Audio para Linux mediante nombre

    auto device1 = soundStream.getMatchingDevices(soundcardIN);
    auto device2 = soundStream.getMatchingDevices(soundcardOUT);

    if (!device1.empty()){
        settings.setInDevice(device1[0]);
    }
    if (!device2.empty()){
        settings.setOutDevice(device2[0]);
    }
    settings.numOutputChannels = nOutput;
    settings.numInputChannels = nInput;
    settings.setInListener(this);
    settings.setOutListener(this);
    int bufferSize = soundStream.getBufferSize();
     //mixer = new Mixer(nInput/2, nOutput/2, 44100,bufferSize);


   // auto devices = soundStream.getDeviceList();
    //settings.device = devices[4];
   /* settings.setInDevice(devices[0]);
    settings.setOutDevice(devices[0]);*/


    master=new Master (nInput/2,nOutput/2, mat_port, baud);
     //int fd;
     /*fd=open("var/Mixer.txt", O_RDWR, 0777);
     ftruncate(fd,sizeof(Mixer));
     mixer = (Mixer *)mmap(NULL, sizeof(Mixer), PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);*/




     soundStream.setup(settings);


}

//--------------------------------------------------------------
void ofApp::update(){
    master->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	
		
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){

    master->processInput(input);
	
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & output){


    master->getOutput(output);
	
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofApp :: ~ofApp(){

}

