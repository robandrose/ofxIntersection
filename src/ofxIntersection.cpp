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
    float u=0;
    u= plane->getNormal().dot(plane->getP0()-line->getP0())/plane->getNormal().dot(line->getVec());
    if(u>1 || u<0){
        return 0;
    }
    intersect->set(line->getP0()+line->getVec()*u);
    return 1;
}


int ofxIntersection::PointLineDistance(ofPoint* point, Line* line, ofPoint* intersect, ofVec3f* distance){
    
    float u;
    ofVec3f dist;
    
    u = ( ( ( point->x - line->getP0().x ) * ( line->getVec().x ) +
         ( ( point->y - line->getP0().y ) * ( line->getVec().y) ) +
         ( ( point->z - line->getP0().z ) * ( line->getVec().z) ) ) /
    ( line->getVec().lengthSquared()));
    
    if( u < 0.0f || u > 1.0f ){
        return 0;   // closest point does not fall within the line segment
    }

    intersect->x = line->getP0().x + u * ( line->getVec().x );
    intersect->y = line->getP0().y + u * ( line->getVec().y );
    intersect->z = line->getP0().z + u * ( line->getVec().z );
    
    distance->set(*intersect- *point);
    
    return 1;
    
}
