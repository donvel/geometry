#pragma once
#include "ofVec2f.h"

struct Point {
	int x, y;
	Point();
	Point(int _x, int _y);
	Point(ofVec2f p);
};

