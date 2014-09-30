#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 

    
    
    cam.setupPerspective();
    cam.setVFlip(false);
    ofEnableAlphaBlending();
    
    for(int i=0;i<50;i++){
        triangles[i].setRandom(ofPoint(ofRandom(-500,500),ofRandom(-500,500),ofRandom(-500,500)), ofRandom(50,200));
    }
    
    
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
    ray.set(mouseworld, mousedir);
    
    cam.begin();
    ofSetColor(255, 0, 0);
    ray.draw();
    mat.begin();
    IntersectionData id;
    for(int i=0;i<50;i++){
        id=is.RayTriangleIntersection(triangles[i], ray);
        if(id.isIntersection){
            ofSetColor(255, 0, 0);
            ofDrawSphere(id.pos,5);
            ofSetColor(200, 200, 200,100);
        }else{
            ofSetColor(100, 200, 100,100);
        }
        triangles[i].draw();
    }
    mat.end();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        ofToggleFullscreen();
    }
    if(key=='r'){
        for(int i=0;i<50;i++){
            triangles[i].setRandom(ofPoint(ofRandom(-500,500),ofRandom(-500,500),ofRandom(-500,500)), ofRandom(50,200));
        }
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