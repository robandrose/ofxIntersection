//
//  ofxInersection.h
//  emptyExample
//
//  Created by Matthias Rohrbach on 16.09.14.
//
//


#pragma once
#include "ofMain.h"


class Line
{
public:
    void set(ofPoint _p0, ofPoint _p1){
        p0=_p0;
        p1=_p1;
    }
    ofPoint p0;
    ofPoint p1;
};

class Plane{
public:
    void set(ofPoint _p0, ofVec3f _normal){
        p0=_p0;
        normal=_normal;
        normal.normalize();
    }
    ofPoint p0;
    ofVec3f normal;
};


class Triangle
{
public:
    ofPoint v0;
    ofPoint v1;
    ofPoint v2;
};


class ofxIntersection
{
public:
    ofxIntersection();
    virtual ~ofxIntersection(){};
    
    int LinePlaneIntersection(Line* line, Plane* plane, ofPoint* intersect);
    
    
private:
    
    
    
};

