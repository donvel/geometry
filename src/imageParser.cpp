#include "imageParser.h"


//--------------------------------------------------------------
void imageParser::setup(){
	
	if(USER_INPUT) {
		cout << "Please enter camera resolution (W H)" << endl;
		cin >> camWidth >> camHeight;
	} else {
		camWidth = 640, camHeight = 480;
	}

	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoRemapped 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	

	Mode = ALIGN;
}


//--------------------------------------------------------------
void imageParser::update(){
	
	ofBackground(100,100,100);
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		unsigned char * pixels = vidGrabber.getPixels();
		remap(videoRemapped, pixels);

		videoTexture.loadData(videoRemapped, camWidth,camHeight, GL_RGB);
	}

}

//--------------------------------------------------------------
void imageParser::draw(){
	ofSetHexColor(0xffffff); // This should be positioned in a more clever way
	vidGrabber.draw(20,20);
	if(Mode == DISPLAY) videoTexture.draw(20+camWidth,20,camWidth,camHeight);
}


//--------------------------------------------------------------
void imageParser::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings(); // doesn't work at all, anyway
	}
	
	if (key == 'a' || key == 'A'){
		Mode = DISPLAY;
	}
	
}

void imageParser::remap(unsigned char * from, unsigned char * to) {
	int totalPixels = camWidth*camHeight*3;
}


// OBSOLETE The rest of functions is not needed.

//--------------------------------------------------------------
void imageParser::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void imageParser::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void imageParser::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void imageParser::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void imageParser::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void imageParser::windowResized(int w, int h){

}

//--------------------------------------------------------------
void imageParser::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void imageParser::dragEvent(ofDragInfo dragInfo){ 

}
