#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
   
    cam.setupPerspective();
    cam.setVFlip(false);
    ofEnableAlphaBlending();
    
    triangle1.set(ofPoint(-100,-200,-50), ofPoint(200,300,100),ofPoint(0,200,30));
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofPoint mouse(ofGetMouseX(), ofGetMouseY(),-1);
    ofPoint mouseworld=cam.screenToWorld(mouse);
    ofPoint mouseworld2=cam.screenToWorld(ofPoint(mouse.x, mouse.y, 1));
    ofVec3f mousedir=mouseworld2-mouseworld;
    mousedir.normalize();
    
    
    ofPoint mousefinal=mouseworld+mousedir*600;
    
    
    ray1.set(mouseworld, mousedir);
    
    ofPushMatrix();
    ofTranslate(200,200);
    ray1.draw();
    triangle1.draw();
    ofPopMatrix();
    
    cam.begin();
    
    ray1.draw();
    IntersectionData id1=is.RayTriangleIntersection(triangle1, ray1);
    
    
    
    if(id1.isIntersection){
        ofDrawSphere(id1.pos,5);
    }
    ofSetColor(100, 200, 100,100);
    triangle1.draw();
   cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        ofToggleFullscreen();
    }
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