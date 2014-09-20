//
//  ofxInersection.h
//  emptyExample
//
//  Created by Matthias Rohrbach on 16.09.14.
//
//


#pragma once
#include "ofMain.h"


class IntersectionData{
public:
    
    bool isIntersection;
    float dist;
    ofPoint pos;
    ofVec3f dir;
    ofVec3f normal;
    
    string toString(){
        string s="isec: "+ofToString(isIntersection);
        if(isIntersection){
            s += " at:" + ofToString(pos) + " dist:" + ofToString(dist) + "normal:" + ofToString(normal);
        }
        return s;
    }
};



class Ray{
public:
    void set(ofPoint _p0, ofVec3f _vec){
        p0=_p0;
        vec=_vec;
    }
    ofPoint getP0(){
        return p0;
    }
    ofVec3f getVec(){
        return vec;
    }
    ofPoint p0;
    ofVec3f vec;
};


class Line
{
public:
    void set(ofPoint _p0, ofPoint _p1){
        p0=_p0;
        p1=_p1;
        vec.set(p1-p0);
    }
    
    float magintude(){
        return vec.length();
    }
    
    ofPoint getP0(){
        return p0;
    }
    ofPoint getP1(){
        return p1;
    }
    ofVec3f getVec(){
        return vec;
    }
    void draw(){
        ofLine(p0,p1);
    }

protected:
    ofPoint p0;
    ofPoint p1;
    ofVec3f vec;
    
};

class Plane{
public:
    
    void set(ofPoint _p0, ofVec3f _normal){
        p0=_p0;
        normal=_normal;
        normal.normalize();
    }
    ofPoint getP0(){
        return p0;
    }
    ofVec3f getNormal(){
        return normal;
    }
    
private:
    ofPoint p0;
    ofVec3f normal;
};


class Triangle
{
public :
    void set(ofPoint _p0, ofPoint _p1, ofPoint _p2){
        p0=_p0;
        p1=_p1;
        p2=_p2;
    }

    
private:
    ofPoint p0;
    ofPoint p1;
    ofPoint p2;
    ofVec3f normal;
    
};

class Ellipse{
    
};

class Circle{
    
};

class Terrain{
    
};


class ofxIntersection
{
public:
    ofxIntersection();
    virtual ~ofxIntersection(){};
    
    IntersectionData* LinePlaneIntersection(Line* line, Plane* plane);
    IntersectionData* PointLineDistance(ofPoint* point, Line* line);
    IntersectionData* TriangleRayIntersection(Triangle* triangle, Ray* ray);
    
private:
    
    IntersectionData idata;
    
    
};

