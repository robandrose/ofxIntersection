//
//  ofxInersection.cpp
//  emptyExample
//
//  Created by Matthias Rohrbach on 16.09.14.
//
//

#include "ofxIntersection.h"

ofxIntersection::ofxIntersection(){
    
}


int ofxIntersection::LinePlaneIntersection(Line* line, Plane* plane, ofPoint* intersect){
    plane->normal=plane->normal.normalize();
    float u=0;
    ofVec3f linedelta=line->p1-line->p0;
    u= plane->normal.dot(plane->p0-line->p0)/plane->normal.dot(linedelta);
    if(u>1 || u<0){
        return 0;
    }
    intersect->set(line->p0+linedelta*u);
    return 1;
}