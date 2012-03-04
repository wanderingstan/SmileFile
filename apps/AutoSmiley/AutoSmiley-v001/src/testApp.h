#ifndef _TEST_APP
#define _TEST_APP

// http://www.cplusplus.com/doc/tutorial/files/

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <pwd.h>

#include "ofMain.h"
#include "computerVision.h"
#include "ofxSmile.h"
#include "sys/stat.h" 

class testApp : public ofSimpleApp{
	
public:
	testApp(char* smileLogFile, int delayMicroseconds, char* smileShellCommand);

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
	float smoothPct;
	float lastTime; // when was the last smile detected
	int totalSmiles; // how many smiles have we detected
	ofTrueTypeFont ttf;
	ofTrueTypeFont ttfSmall;

	char* smileDirectory;
	char* smileLogFile;
	int delayMicroseconds;
	char* smileShellCommand;
};

#endif

