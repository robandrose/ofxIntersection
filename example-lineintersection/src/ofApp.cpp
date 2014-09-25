#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    for(int i=0;i<10000;i++){
        lines[i].set(ofPoint(ofRandomWidth()-ofGetWidth()/2, ofRandomHeight()-ofGetHeight()/2, ofRandom(-500,500)),ofPoint(ofRandomWidth()-ofGetWidth()/2, ofRandomHeight()-ofGetHeight()/2, ofRandom(-500,500)));
        
    }
   
    cam.setupPerspective();
    cam.setVFlip(false);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    planenormal.set(1, 0,1);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    //planenormal.rotate(0.1, ofVec3f(1,1,0));
    
    
    ofPoint mouse(ofGetMouseX(), ofGetMouseY(),-1);
    ofPoint mouseworld=cam.screenToWorld(mouse);
    ofPoint mouseworld2=cam.screenToWorld(ofPoint(mouse.x, mouse.y, 1));
    ofVec3f mousedir=mouseworld2-mouseworld;
    mousedir.normalize();
    ofPoint mousefinal=mouseworld+mousedir.scale(600);
    
    cam.begin();
    
    Plane p1, p2,p3;
    ofVec3f n1, n2, n3;
    
    n1.set(1, 1,1);
    n2.set(n1);
    n3.set(n1);
    n2.rotate(30, ofVec3f(1,0,0));
    n3.rotate(60, ofVec3f(1,0,0));
    
    p1.set(ofPoint(0,0,0), n1);
    p2.set(ofPoint(ofGetMouseX(),0,0), n2);
    p3.set(ofPoint(0,0,ofGetMouseY()),n3);
    
    IntersectionData id2=is.PlanePlanePlaneIntersection(p1, p2, p3);
    
    ofSetColor(255, 0, 0,100);
    p1.draw();
    
    /*p2.draw();
    p3.draw();
    */
    /*
    if(id2.isIntersection){
        ofSetColor(ofColor::yellow);
        ofDrawBox(id2.pos,5);
    }
    
    */
    
    Line l1;
    l1.set(ofPoint(-200,-300,-500), ofPoint(300,300,300));
    l1.draw();
    
    IntersectionData idatal=is.LinePlaneIntersection(l1, p1);
    
    if(idatal.isIntersection){
        ofDrawBox(idatal.pos, 3);
    }
    
    ofSetColor(255, 0, 0,100);
    p1.draw();
    
    
    ofSetColor(ofColor::white,100);
    Triangle tri;
    tri.set(ofPoint(-150,-50,-30), mousefinal, ofPoint(-20,100,40));
    tri.draw();
    
    IntersectionData idata=is.PlaneTriangleIntersection(p1, tri);
    
    if(idata.isIntersection){
        ofLine(idata.pos, idata.pos+idata.dir);
        ofDrawBox(idata.pos, 3);
    }
    
    
    
    
    ofSetColor(255, 255,255);
    for(int i=0;i<1000;i++){
        lines[i].draw();
        idata=is.LinePlaneIntersection(lines[i], p1);
        if(idata.isIntersection){
            ofRect(idata.pos, 2,2);
        }
        idata=is.PointLineDistance(mousefinal, lines[i]);
        if(idata.isIntersection){
            ofRect(idata.pos, 3,3);
            ofPushStyle();
            ofSetColor(ofColor::red);
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