#include "imageParser.h"



//--------------------------------------------------------------
void imageParser::setup(){
	
	if(USER_INPUT) {
		cout << "Please enter camera resolution (W H)" << endl;
		cin >> camWidth >> camHeight;
		cout << "Please enter workspace resolution (W H)" << endl;
		cin >> worWidth >> worHeight;
	} else {
		camWidth = 640, camHeight = 480;
		worWidth = 640, worHeight = 480;
	}

	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoRemapped 	= new unsigned char[worWidth*worHeight*3];
	videoTexture.allocate(worWidth,worHeight, GL_RGB);

	Mode = ADJUST;
	pointNum = 0;
}


//--------------------------------------------------------------
void imageParser::update(){
	
	ofBackground(100,100,100);
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		unsigned char * pixels = vidGrabber.getPixels();
		remap(pixels, videoRemapped);

		videoTexture.loadData(videoRemapped, worWidth,worHeight, GL_RGB);
	}

}

//--------------------------------------------------------------
void imageParser::draw(){
	ofSetHexColor(0xffffff); // This should be positioned in a more clever way
	vidGrabber.draw(Margin,Margin);
	if(Mode == DISPLAY) videoTexture.draw(Margin+camWidth,Margin,worWidth,worHeight);


	ofNoFill();
	ofSetPolyMode(OF_POLY_WINDING_ODD);
	ofSetColor(0,255,0);

	ofBeginShape();

	for (int i = 0; i < pointNum; ++i) {
		ofVertex(rect[i].x + Margin, rect[i].y + Margin);
	}
	if(pointNum < 4) ofVertex(mouseX, mouseY);

	ofEndShape(true);

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
	
	if ((key == 'a' || key == 'A') && (pointNum == 4)){
		Mode = DISPLAY;
	}
	if (key == 'r' || key == 'R'){
		Mode = ADJUST;
		pointNum = 0;

	}
	
}

void imageParser::remap(unsigned char * from, unsigned char * to) {
	int totalPixels = camWidth*camHeight*3;

	for(int x = 0; x < worWidth; x++) {
		for(int y = 0; y < worHeight; y++) {
			Point coords = getCoords(Point(x, y));
			int coord = (coords.x + coords.y * camWidth) * 3;
			if(coord >= 0 && coord < totalPixels) for(int c = 0; c < 3; c++) {
				to[(x + y* worWidth) * 3 + c] = from[coord + c];
			}
		}
	}
}

Point imageParser::getCoords(Point p) {
	ofVec2f relPos((float)p.x / (float)worWidth, (float)p.y / (float)worHeight);
//	rect[0] = (0,0)
//	rect[1] = (camWidth,0);
//	rect[2] = (camWidth,camHeight);
//	rect[3] = (0,camHeight);

	ofVec2f p1 = rect[0] + (rect[1] - rect[0]) * relPos.x;
	ofVec2f p2 = rect[3] + (rect[2] - rect[3]) * relPos.x;
	ofVec2f p3 = p1 + (p2 - p1) * relPos.y;

//	cout << p.x << ", " << p.y << " to " << p3 << endl;

	return p3;
}


void imageParser::mousePressed(int x, int y, int button){
	if(button == 0) {
		if(pointNum < 4) {
			rect[pointNum++] = ofVec2f(x - Margin, y - Margin);
		}
	}
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
