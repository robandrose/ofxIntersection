#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    sphere.set(200, 10,OF_PRIMITIVE_TRIANGLES);
    mesh=sphere.getMesh();
    ofEnableDepthTest();
    cam.setupPerspective();
    cam.setVFlip(false);
    
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    
    ray.set(ofPoint(0,0,0), ofPoint(400,400,400));
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ray.vec.rotate(1, ofVec3f(1,1,0));
    
    cam.begin();
    ofSetColor(255, 0, 0);
    ray.draw();
 
    
    
    mesh.drawWireframe();
    
    
    IntersectionData id;
    
    mesh.getUniqueFaces().size();;
    
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
            ofSetColor(0,0,0,0);
        }
        
        triangle.draw();
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