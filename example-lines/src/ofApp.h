#pragma once

#include "ofMain.h"
#include "ofxIntersection.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxIntersection is;
    Line lines[100];
    ofEasyCam cam;
    ofVec3f n1,n2,n3;
    Plane p1, p2,p3;
    
    ofLight light1;
    ofMaterial mat1;
    
};
