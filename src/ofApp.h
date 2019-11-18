#pragma once

#include "ofMain.h"
#include "Master/Master.h"
//#include "Master/Matrix/Matriz.h"

class ofApp : public ofBaseApp{
	
    public:
		
		void setup();
		void update();
        //void draw();
				
		void keyPressed(int key);
		void keyReleased(int key);
        /*void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);*/
        ~ofApp();

		
		void audioIn(ofSoundBuffer & input);
		void audioOut (ofSoundBuffer & output);
	
		string soundcardIN, soundcardOUT;
        string mat_port;
        int baud;


        Master* master;

        void createModules (Master* master);
        void createLinks(Master* master);


		int nOutput, nInput;

		
		ofSoundStream soundStream;
        //std :: mutex mtx;
};
