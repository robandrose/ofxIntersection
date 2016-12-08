//
//  ofxInersection.h
//  emptyExample
//
//  Created by Matthias Rohrbach on 16.09.14.
//
//


#pragma once
#include "ofMain.h"
#define EPS 1.0E-10


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


class IsLine
{
public:
    IsLine(){
        set(ofPoint(0,0,0), ofPoint(100,0,0));
    };
    IsLine(ofPoint _p0, ofPoint _p1){
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

class IsRay{
public:
    IsRay(){
        set(ofPoint(0,0,0),ofVec3f(1,0,0));
    };
    IsRay(ofPoint _p0, ofVec3f _vec){
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
        return p0+vec*dist;
    }
    ofPoint p0;
    ofVec3f vec;
    
    void draw(float length){
        ofDrawLine(p0-vec*length/2,p0+vec*length/2);
    }
    
    IsLine asLine(float length){
        IsLine line(ofPoint(p0-vec*length/2.0f), ofPoint(p0+vec*length/2.0f));
        return line;
    }
};



class IsPlane{
public:
    IsPlane(){
        p0.set(0,0,0);
        normal.set(0,0,1);
    };
    IsPlane(ofPoint _p0, ofVec3f _normal){
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
    float getDCoeff(){
        return d;
    }
    float updateDCoeff(){
         d=normal.dot(p0);
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


class IsTriangle
{
    
public :
    IsTriangle(){};
    
    IsTriangle(ofPoint _p0, ofPoint _p1, ofPoint _p2){
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
    IsLine getSeg0(){return seg0;}
    IsLine getSeg1(){return seg1;}
    IsLine getSeg2(){return seg2;}
    ofVec3f getNormal(){return normal;}

    // Draw for Debug:
    void draw(){
        ofDrawTriangle(p0,p1,p2);
    }

private:
    ofPoint p0;
    ofPoint p1;
    ofPoint p2;
    ofVec3f normal;
    
    IsLine seg0;
    IsLine seg1;
    IsLine seg2;
    
    IsLine* segments[3];
    
};


class IsRectangle{

    public :
    IsRectangle(){
        p0.set(0,0,0);
        width=100;
        height=100;
        rect.set(p0.x, p0.y,width,height);
        normal.set(0,0,1);
    };
    IsRectangle(ofPoint _p0, ofVec3f _normal, float _width, float _height){
        set(_p0, _normal, _width, _height);
    }
    void set(ofPoint _p0, ofVec3f _normal, float _width, float _height){
        p0=_p0;
        width=_width;
        height=_height;
        rect.set(p0.x, p0.y, width,height);
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
    float getDCoeff(){
        return d;
    }
    float updateDCoeff(){
        d=normal.dot(p0);
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
        ofDrawPlane(width,height);
        ofPopMatrix();
        ofPopMatrix();

    }
    
    private:
    float width;
    float height;
    ofRectangle rect;
    ofPoint p0;
    ofVec3f normal;
    float d;
};

class IsPolygon{
    void set(vector<ofPoint> points){
        
    }
    void addPoint(ofPoint _p){
        points.push_back(_p);
        
    }
    
private:
    vector<ofPoint>points;
    vector<IsTriangle>triangles;
    IsPlane plane;
    ofVec3f normal;
    
};

class IsEllipse{
private:
    ofPoint center;
    float radiusX;
    float radiusY;
    
};

class IsCircle{
    
};

class IsSphere{
    // TODO: Create Sphere Class to intersect with
    // –ray
    // – closest point to other point
    // Plane
    // etc.
    
    
};


class IsAABB{
    
};

class IsTerrain{
    
};


class ofxIntersection
{
public:
    ofxIntersection();
    virtual ~ofxIntersection(){};

    // Ray
    IntersectionData RayPlaneIntersection(IsRay& ray, IsPlane& plane);
    IntersectionData RayTriangleIntersection(IsTriangle& triangle, IsRay& ray);

    // Line
    IntersectionData LinePlaneIntersection(IsLine& line, IsPlane& plane);
    IntersectionData LineLineIntersection(IsLine& line1, IsLine& line2);
    IntersectionData PointLineDistance(ofPoint& point, IsLine& line);
    
    // Plane
    IntersectionData PlanePlaneIntersection(IsPlane& plane1, IsPlane& plane2);
    IntersectionData PlanePlanePlaneIntersection(IsPlane& plane1, IsPlane& plane2, IsPlane& plane3);
    
    IntersectionData PlaneTriangleIntersection(IsPlane& plane, IsTriangle& triangle);
    float PointPlaneDistance(ofPoint& point, IsPlane& plane);
    
    IntersectionData PlaneRectangleIntersection(IsPlane &plane, IsRectangle& rect);
    
    
    
    // Triangle
    IntersectionData TriangleTriangleIntersection(IsTriangle& triangle1, IsTriangle& triangle2){};
    
    
    
    
private:
    
    bool containsValue(vector<ofPoint>* points, ofPoint point);
    ofVec3f LinePlaneIntersectionFast(ofPoint& p0, ofPoint& p1, IsPlane& plane);
    
    
    
    
};

