#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i=0;i<200;i++){
        lines[i].set(ofPoint(ofRandomWidth(), ofRandomHeight(), ofRandom(-500,500)),ofPoint(ofRandomWidth(), ofRandomHeight(), ofRandom(-500,500)));
        
    }
    cam.setVFlip(true);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofPoint mouse(ofGetMouseX(), ofGetMouseY(),0);
    ofPoint intersect;
    ofVec3f distance;
    
    
    cam.begin();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
  
    for(int i=0;i<200;i++){
    
        lines[i].draw();
    
        if(is.PointLineDistance(&mouse, &lines[i], &intersect, &distance)){
            ofEllipse(intersect.x, intersect.y, intersect.z, 5,5);
            ofPushStyle();
            ofSetColor(ofColor::red);
            ofLine(intersect.x, intersect.y, intersect.z, mouse.x, mouse.y, 0);
            ofPopStyle();
        };
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}