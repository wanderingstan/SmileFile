#include "testApp.h"

testApp::testApp(char* smileLogFile, int delayMicroseconds, char* smileShellCommand) {
	this->smileLogFile = smileLogFile;
	this->delayMicroseconds = delayMicroseconds;
	this->smileShellCommand = smileShellCommand;
}

//--------------------------------------------------------------
void testApp::setup() {
	ofBackground(30,30,30);

    vision.setupCamera(0, 320, 240);
	
	//lets load the font from our app bundle
	ofSetDataPathRoot("./");
	ttf.loadFont("MONACO.TTF", 48);
	ttfSmall.loadFont("MONACO.TTF", 14);

	//lets restore it
	ofSetDataPathRoot("../../../");

	img.allocate(320, 240, OF_IMAGE_GRAYSCALE);
	
	lastTime = ofGetElapsedTimef()- 10.0;
		
	smilePct = 0.0;
	smoothPct = 0.0;
}

//--------------------------------------------------------------
// http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
    }
    pclose(pipe);
    return result;
}

//--------------------------------------------------------------
void testApp::doSmily() {

	struct passwd *pw = getpwuid(getuid());	
	const char *homedir = pw->pw_dir;

	// make the directory if it's not there
	std::string dir_command_result = exec("mkdir -p ~/smilefile");
	
	// C/C++ sucks hairy balls
	this->smileLogFile = new char[strlen(homedir)+strlen("/smilefile/smilelog.csv")+2];
	sprintf(this->smileLogFile,"%s%s",homedir,"/smilefile/smilelog.csv");
	
	// save our smiling picture
	img.setFromPixels(vision.color.getPixels(), vision.color.width, vision.color.height, OF_IMAGE_COLOR);
	img.saveImage("/tmp/latest-smile.jpg"); // this will get renamed in our script
	
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	char timebuffer [20];
	
	// write to log file
	FILE * pFile;
	pFile = fopen (this->smileLogFile ,"a");
	if (!pFile) {
		fprintf(stderr,"Could not open log file.\n");
		return;
	}
	// output timestamp
	strftime(timebuffer, 20, "%Y-%m-%dT%H:%M:%S", timeinfo);
	fprintf (pFile, "%d\t%s", (int) time (NULL), timebuffer );
	
	// output results of shell command
	if (this->smileShellCommand) {
		// execute command
		std::string command_result = exec(this->smileShellCommand);
		fprintf (pFile, "%s", (char*) command_result.c_str());
	}
	fprintf(pFile, "\n");
	fclose(pFile);
	
	
	/*
	//from http://74.125.47.132/search?q=cache:OtbdKJ8MQToJ:www.realsoftware.com/listarchives/realbasic-nug/2001-11/msg01823.html+CGKeyCode+shift&cd=2&hl=en&ct=clnk&gl=us&client=safari
	//codes from - http://ritter.ist.psu.edu/projects/RUI/macosx/rui.c
	
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, true );		// - SPACE down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, false );		// - SPACE down
	
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)56, true );		// - SHIFT down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)41, true );		// - : key down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)41, false );		// - : up down


	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)29, true );		// - ) key down  
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)29, false );		// - ) up down  
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)56, false );		// - SHIFT up

	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, true );		// - ENTER down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)49, false );		// - ENTER down
	
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)52, true );		// - ENTER down
	CGPostKeyboardEvent( (CGCharCode)0, (CGKeyCode)52, false );		// - ENTER up
	*/
	
		
	//also
	//- http://stackoverflow.com/questions/2379867/simulating-key-press-events-in-mac-osx
//	CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
//	CGEventRef saveCommandDown = CGEventCreateKeyboardEvent(source, (CGKeyCode)1, YES);
//	CGEventSetFlags(saveCommandDown, kCGEventFlagMaskCommand);
//	CGEventRef saveCommandUp = CGEventCreateKeyboardEvent(source, (CGKeyCode)1, NO);
//
//	CGEventPost(kCGAnnotatedSessionEventTap, saveCommandDown);
//	CGEventPost(kCGAnnotatedSessionEventTap, saveCommandUp);
//
//	CFRelease(saveCommandUp);
//	CFRelease(saveCommandDown);
//	CFRelease(source);
}

//--------------------------------------------------------------
void testApp::update(){
    vision.update();
	
	img.setFromPixels(vision.gray.getPixels(), vision.gray.width, vision.gray.height, OF_IMAGE_GRAYSCALE);
		
	ofxSmile::getSmile(img, smilePct);
	
	smoothPct *= 0.8;
	smoothPct += MAX(0, smilePct) * 0.2;
	
	if( ofGetElapsedTimef() - lastTime > 3.0 ){
		if( smoothPct > 0.50 ){
			doSmily();
			
			lastTime = ofGetElapsedTimef();
		}
	}
	// SLEEP! Important to avoid taking too much of processor
	usleep(this->delayMicroseconds); // sleep for 500 milliseconds
}

//--------------------------------------------------------------
void testApp::draw() {
	ofSetColor(0xffffff);
    vision.color.draw(0,0);
	
	ofDrawBitmapString("smile        = " + ofToString(smilePct, 2), 20, 20);
	ofDrawBitmapString("smile smooth = " + ofToString(smoothPct, 2), 20, 36);
	ofDrawBitmapString("delay        = " + ofToString(this->delayMicroseconds, 0), 20, 52);
	
	// if smile was detected in last second, display our notification
	if( ofGetElapsedTimef() - lastTime < 1.0 ){
		ofSetColor(255, 255, 255, 100);
		ttf.drawString(":)", -50 + img.width/2, 30 + img.height/2);
	}
	float alpha = ofMap(  ofGetElapsedTimef() - lastTime, 1.0, 1.3, 255, 0.0, true);
	ofSetColor(255, 255, 255, alpha);
	ttfSmall.drawString("saving a smile :)", 10, 270);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    if(key == ' '){
        vision.togglePlayback();
    }

    //if you need to adjust the camera properties
    if(key == 's'){
        vision.camera.videoSettings();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased() {
}
