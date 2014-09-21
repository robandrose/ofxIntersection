//
//  ofxInersection.h
//  emptyExample
//
//  Created by Matthias Rohrbach on 16.09.14.
//
//


#pragma once
#include "ofMain.h"
#define EPS 1.0E-6


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
    Ray(){};
    Ray(ofPoint _p0, ofVec3f _vec){
        set(_p0, _vec);
    }
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
    Line(){};
    Line(ofPoint _p0, ofPoint _p1){
        this->set(_p0, _p1);
    }
    
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
    Plane(){};
    Plane(ofPoint _p0, ofVec3f _normal){
        set(_p0, _normal);
    }
    
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
    
    void draw(){
        ofQuaternion rot;
        rot.makeRotate(ofVec3f(0,0,1), getNormal());
        ofPushMatrix();
        ofMatrix4x4 rotmat;
        rot.get(rotmat);
        ofMultMatrix(rotmat);
        
        ofDrawPlane(p0, 1000, 1000);
        ofPopMatrix();
    }
    
private:
    ofPoint p0;
    ofVec3f normal;
};


class Triangle
{
public :
    Triangle(){};
    Triangle(ofPoint _p0, ofPoint _p1, ofPoint _p2){
        set(_p0,_p1, _p2);
    }

    void set(ofPoint _p0, ofPoint _p1, ofPoint _p2){
        p0=_p0;
        p1=_p1;
        p2=_p2;
        
        seg0.set(p0, p1);
        seg1.set(p1, p2);
        seg2.set(p2, p0);
        
    }
    
    ofPoint getP0(){
        return p0;
    }
    ofPoint getP1(){
        return p1;
    }
    ofPoint getP2(){
        return p2;
    }
    Line getSeg0(){
        return seg0;
    }
    Line getSeg1(){
        return seg1;
    }
    Line getSeg2(){
        return seg2;
    }

    void draw(){
        ofTriangle(p0,p1,p2);
    }
    
private:
    ofPoint p0;
    ofPoint p1;
    ofPoint p2;
    ofVec3f normal;
    
    Line seg0;
    Line seg1;
    Line seg2;
    
    
    
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

    // Ray
    IntersectionData RayPlaneIntersection(Ray& ray, Plane& plane);
    IntersectionData RayTriangleIntersection(Triangle& triangle, Ray& ray);

    // Line
    IntersectionData LinePlaneIntersection(Line& line, Plane& plane);
    IntersectionData LineLineIntersection(Line& line1, Line& line2);
    IntersectionData PointLineDistance(ofPoint& point, Line& line);
    
    // Plane
    IntersectionData PlanePlaneIntersection(Plane& plane1, Plane& plane2);
    IntersectionData PlaneTriangleIntersection(Plane& plane, Triangle& triangle);
    
    
    
private:
    
    
    
};

