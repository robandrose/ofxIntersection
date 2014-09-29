#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    for(int i=0;i<100;i++){
        lines[i].set(ofPoint(ofRandomWidth()-ofGetWidth()/2, ofRandomHeight()-ofGetHeight()/2, ofRandom(-500,500)),ofPoint(ofRandomWidth()-ofGetWidth()/2, ofRandomHeight()-ofGetHeight()/2, ofRandom(-500,500)));
        
    }
   
    cam.setupPerspective();
    cam.setVFlip(false);
    ofEnableAlphaBlending();
    
    
    
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
    ofPoint mousefinal=mouseworld+mousedir.scale(600);
    
    
    cam.begin();
    
    
    Line l1;
    l1.set(ofPoint(-200,-300,-500), ofPoint(300,300,300));
    l1.draw();
    
    p1.set(ofPoint(0,0,0), ofVec3f(1,0,0));
    IntersectionData idatal=is.LinePlaneIntersection(l1, p1);
    
    if(idatal.isIntersection){
        ofDrawBox(idatal.pos, 3);
    }
    
    ofSetColor(10, 200, 50,100);
    p1.draw();
    
    
    IntersectionData idata;
    
    
    for(int i=0;i<100;i++){
        ofSetColor(ofColor::white);
        lines[i].draw();
        
        idata=is.LinePlaneIntersection(lines[i], p1);
        
        if(idata.isIntersection){
            ofSetColor(200, 0, 50);
            ofDrawBox(idata.pos, 5);
        }
        
        idata=is.PointLineDistance(mousefinal, lines[i]);
        if(idata.isIntersection){
            ofPushStyle();
            
            ofSetColor(ofColor::white);
            ofDrawBox(idata.pos, 3);
            ofSetColor(ofColor::yellowGreen);
            ofLine(idata.pos, mousefinal);
            ofPopStyle();
        };
    }
    
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