#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
 
    mesh.load("lofi-bunny.ply");
    
    ofEnableDepthTest();
    cam.setupPerspective();
    cam.setVFlip(false);
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofVec3f dir(1,1,0);
    
    for(int i=0;i<NUM_PLANES;i++){
        planes[i].set(ofPoint(0,0,0), dir);
        dir.rotate(360.0f/NUM_PLANES, ofVec3f(1,0,0));
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
    
    for(int i=0;i<NUM_PLANES;i++){
        ofVec3f normal=planes[i].getNormal();
        normal.rotate(1, ofVec3f(1,1,0));
        planes[i].setNormal(normal);
        
    }
    
    cam.begin();
    ofSetColor(255, 0, 0);
    ray.draw();
    //plane.draw();
    ofSetColor(ofColor::gray);
    
    
    mesh.drawWireframe();
    
    mat.begin();
    
    IntersectionData id;
    
    mesh.getUniqueFaces().size();;
    
    planecut.clear();
    planecut.setMode(OF_PRIMITIVE_LINES);
    
    for(int i=0;i<mesh.getUniqueFaces().size();i++){
        IsTriangle triangle;
        ofMeshFace face=mesh.getUniqueFaces().at(i);
        triangle.set(face);
        
        id=is.RayTriangleIntersection(triangle, ray);
        if(id.isIntersection){
            ofSetColor(255, 0, 0);
            ofDrawSphere(id.pos,5);
            ofSetColor(200, 200, 200,150);
        }else{
            ofSetColor(100, 200, 100,80);
        }
        
        triangle.draw();
        for(int pi=0;pi<NUM_PLANES;pi++){
        id=is.PlaneTriangleIntersection(planes[pi], triangle);
        if(id.isIntersection){
            planecut.addVertex(id.pos);
            planecut.addVertex(id.pos+id.dir);
        }
        }
        
        
        
    }
    ofSetLineWidth(2);
    ofSetColor(ofColor::red);
   
    planecut.draw();
    ofSetLineWidth(1);
    
    
    mat.end();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        ofToggleFullscreen();
    }
    if(key=='r'){
        
        ofVec3f dir(1,1,0);
        
        for(int i=0;i<NUM_PLANES;i++){
            planes[i].set(ofPoint(0,0,0), dir);
            dir.rotate(360.0f/NUM_PLANES, ofVec3f(1,0,0));
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