#ifndef _TEST_APP
#define _TEST_APP

// http://www.cplusplus.com/doc/tutorial/files/

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>

#include "ofMain.h"
#include "computerVision.h"
#include "ofxSmile.h"

class testApp : public ofSimpleApp{
	
	public:
		testApp(char* smileLogFile, char* smileShellCommand);
		
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
	void doSmily();
	
		ofImage img;
        computerVision vision;
		
		float smilePct;
		float lastTime;
		float smoothPct;
		
		ofTrueTypeFont ttf;
		ofTrueTypeFont ttfSmall;
	
		char* smileLogFile;
		char* smileShellCommand;
};

#endif

