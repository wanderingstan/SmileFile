#include "ofMain.h"
#include "testApp.h"


//========================================================================
int main(int argc, char* argv[]){
	
	char* smileLogFile;
	char* smileShellCommand;
	if (argc>=2) {
		smileLogFile = argv[1];
	}
	else {
		smileLogFile = NULL;
	}
	if (argc>=3) {
		smileShellCommand = argv[2];
	}
	else {
		smileShellCommand = NULL;
	}

	ofSetupOpenGL(320,300, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	ofRunApp(new testApp(smileLogFile, smileShellCommand));

}
