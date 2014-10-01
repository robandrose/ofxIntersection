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
        isIntersection=false;
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
    
    
    ofVec3f getPointAtDistance(float dist){
        return p0+vec.getScaled(dist);
    }
    
    
    ofPoint p0;
    ofVec3f vec;
    
    void draw(){
        ofLine(p0,p0+vec.getScaled(1000));
    }
};


class Line
{
public:
    Line(){};
    Line(ofPoint _p0, ofPoint _p1){
        set(_p0, _p1);
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
    Plane(){
        p0.set(0,0,0);
        normal.set(0,0,1);
        
    };
    Plane(ofPoint _p0, ofVec3f _normal){
        set(_p0, _normal);
    }
    void set(ofPoint _p0, ofPoint _p1, ofPoint _p2){
        ofVec3f seg0, seg1;
        seg0.set(_p1-_p0);
        seg1.set(_p2-_p0);
        seg0.cross(seg1);
        normal.set(seg0.cross(seg1));
        normal.normalize();
        set(normal, _p0);
    }
    void set(ofPoint _p0, ofVec3f _normal){
        p0=_p0;
        normal=_normal;
        normal.normalize();
        updateDCoeff();
    }
    
    void setNormal(ofVec3f _normal){
        normal=_normal;
        normal.normalize();
        updateDCoeff();
    }
    
    void setPosition(ofVec3f _p0){
        p0=_p0;
        updateDCoeff();    
    }
    
    ofPoint getP0(){
        return p0;
    }
    ofVec3f getNormal(){
        return normal;
    }
    float updateDCoeff(){
         d=normal.dot(p0);
    }
    float getDCoeff(){
        return d;
    }
    void draw(){
        ofQuaternion rot;
        rot.makeRotate(ofVec3f(0,0,1), this->getNormal());
        ofMatrix4x4 rotmat;
        rot.get(rotmat);
        ofPushMatrix();
        ofTranslate(p0);
        ofPushMatrix();
        ofMultMatrix(rotmat);
        ofDrawPlane(1000, 1000);
        ofPopMatrix();
        ofPopMatrix();
    }
   
    
    private:
    
    ofPoint p0;
    ofVec3f normal;
    float d;
    
    
};


class Triangle
{
    
public :
    Triangle(){};
    
    
    
    Triangle(ofPoint _p0, ofPoint _p1, ofPoint _p2){
        set(_p0,_p1, _p2);
    }
    
    void set(ofMeshFace _face){
        
        set(_face.getVertex(0), _face.getVertex(1), _face.getVertex(2));
        
    }
    
    void setRandom(ofPoint _pos, float _radius){
        ofVec3f indexa(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1));
        indexa.normalize();
        ofVec3f index(1,0,0);
        index.cross(indexa);
        index.scale(_radius);
        
        p0.set(_pos+index);
        index.rotate(120, indexa);
        p1.set(_pos+index);
        index.rotate(120, indexa);
        p2.set(_pos+index);
        
        set(p0,p1,p2);
        
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
        
        computeNormal();
    }
    
    bool containsPoint(ofPoint p){
        ofVec3f v0 = p2-p0;
        ofVec3f v1 = p1-p0;
        ofVec3f v2 = p-p0;
        
        // Compute dot products
        float dot00 = v0.dot(v0);
        float dot01 = v0.dot(v1);
        float dot02 = v0.dot(v2);
        float dot11 = v1.dot(v1);
        float dot12 = v1.dot(v2);
        
        // Compute barycentric coordinates
        float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
        float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
        
        // Check if point is in triangle
        return (u >= 0.0) && (v >= 0.0) && (u + v <= 1.0);
    }
    
    ofVec3f computeNormal(){
        normal = seg2.vec.getCrossed(seg0.vec).normalize();
        return normal;
    }
    
    // Getters:
    ofPoint getP0(){return p0;}
    ofPoint getP1(){return p1;}
    ofPoint getP2(){return p2;}
    Line getSeg0(){return seg0;}
    Line getSeg1(){return seg1;}
    Line getSeg2(){return seg2;}
    ofVec3f getNormal(){return normal;}

    // Draw for Debug:
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
    ofVec3f LinePlaneIntersectionFast(ofPoint& p0, ofPoint& p1, Plane& plane);
    
    
    
    
};

