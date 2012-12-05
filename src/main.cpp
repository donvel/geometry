/* Interactive CV-driven geometry environment */

#include "ofMain.h"
#include "imageParser.h"
#include "ofAppGlutWindow.h"
#include <cstdio>

int sWidth, sHeight;

//========================================================================
int main() {

	if(USER_INPUT) {
		cout << "Please enter window resolution (W H)" << endl;
		cin >> sWidth >> sHeight;
	} else {
		sWidth = 1024, sHeight = 768;
	}

    ofAppGlutWindow window;

	ofSetupOpenGL(&window, sWidth, sHeight, OF_WINDOW);

	// can be OF_WINDOW or OF_FULLSCREEN

	ofRunApp( new imageParser());

}
