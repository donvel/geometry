#include "point.h"

Point::Point() {}
Point::Point(int _x, int _y) : x(_x), y(_y) {}
Point::Point(ofVec2f p) : x(p.x), y(p.y) {}

