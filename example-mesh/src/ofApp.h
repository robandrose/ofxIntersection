#pragma once

#include "ofMain.h"
#include "ofxIntersection.h"

#define NUM_PLANES 100
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
    
    ofMesh mesh;
    ofMesh planecut;
    
    Ray ray;
    Plane planes[NUM_PLANES];
    
    ofEasyCam cam;
    
    ofLight light;
    ofMaterial mat;
};
