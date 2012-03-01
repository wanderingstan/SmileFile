#include "ofMain.h"
#include "testApp.h"


//========================================================================
int main(int argc, char* argv[]){
	char* smileLogFile;
	int delayMicroseconds;
	char* smileShellCommand;
	if (argc>=2) {
		smileLogFile = argv[1];
	}
	else {
		smileLogFile = NULL;
	}
	if (argc>=3) {
		delayMicroseconds = atoi(argv[2]);
	}
	else {
		delayMicroseconds = 0;
	}
	if (argc>=4) {
		smileShellCommand = argv[3];
	}
	else {
		smileShellCommand = NULL;
	}

	ofSetupOpenGL(320,300, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp(smileLogFile, delayMicroseconds, smileShellCommand));
}
