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
    IntersectionData(){
        isIntersection=true;
        dist=0;
        pos.set(0,0,0);
        dir.set(0,0,0);
        normal.set(0,0,0);
    }
    
    bool isIntersection;
    float dist;
    ofPoint pos;
    ofVec3f dir;
    ofVec3f normal;
    
    string toString(){
        string s="isec: "+ofToString(isIntersection);
        if(isIntersection){
            s += " at:" + ofToString(pos) +" dir:"+ofToString(dir)+ " dist:" + ofToString(dist) + "normal:" + ofToString(normal);
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

    ofPoint p0;
    ofPoint p1;
    ofVec3f vec;
protected:

    
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
    void set(ofPoint _p0, ofPoint _p1, ofPoint _p2){
        ofVec3f seg0, seg1;
        seg0.set(_p1-_p0);
        seg1.set(_p2-_p0);
        seg0.cross(seg1);
        normal.set(seg0.cross(seg1));
        normal.normalize();
        p0.set(_p0);
        
    }
    
    ofPoint getP0(){
        return p0;
    }
    ofVec3f getNormal(){
        return normal;
    }
    
    float getDCoeff(){
        return normal.dot(p0);
    }

    void draw(){
        ofQuaternion rot;
        rot.makeRotate(ofVec3f(0,0,1), this->getNormal());
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
        
        segments[0]=&seg0;
        segments[1]=&seg1;
        segments[2]=&seg2;
    }
    
    ofPoint getP0(){return p0;}
    ofPoint getP1(){return p1;}
    ofPoint getP2(){return p2;}
    Line getSeg0(){return seg0;}
    Line getSeg1(){return seg1;}
    Line getSeg2(){return seg2;}

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
    
    Line* segments[3];
    
    
};


class Rectangle{
    
};

class Ellipse{
private:
    ofPoint center;
    float radiusX;
    float radiusY;
    
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
    IntersectionData PlanePlanePlaneIntersection(Plane& plane1, Plane& plane2, Plane& plane3);
    
    IntersectionData PlaneTriangleIntersection(Plane& plane, Triangle& triangle);
    float PointPlaneDistance(ofPoint& point, Plane& plane);
    
    
    // Triangle
    IntersectionData TriangleTriangleIntersection(Triangle& triangle1, Triangle& triangle2){};
    
    
    
    
private:
    
    bool containsValue(vector<ofPoint>* points, ofPoint point);
    
    
    
    
    
};

