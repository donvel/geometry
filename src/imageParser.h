#pragma once

#include "ofMain.h"
#include "ofGraphics.h"
#include "ofVec2f.h"
#include "parameters.h"
#include "point.h"

class imageParser : public ofBaseApp {
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoRemapped;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;

		// Stuff added to the testApp by me
		int 				worWidth;
		int 				worHeight;

		enum mode {ADJUST, DISPLAY};
		mode Mode;
		void remap(unsigned char * from, unsigned char * to);
		Point getCoords(Point p);
		ofVec2f rect[4];
		int pointNum;
};
