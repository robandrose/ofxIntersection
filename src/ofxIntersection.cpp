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


IntersectionData* ofxIntersection::LinePlaneIntersection(Line* line, Plane* plane){
    float u=0;
    u= plane->getNormal().dot(plane->getP0()-line->getP0())/plane->getNormal().dot(line->getVec());
    if(u>1 || u<0){
        idata.isIntersection=false;
        return &idata;
    }
    idata.pos.set(line->getP0()+line->getVec()*u);
    return &idata;
}


IntersectionData* ofxIntersection::PointLineDistance(ofPoint* point, Line* line){
    float u;
    ofVec3f dist;
    
    u = ( ( ( point->x - line->getP0().x ) * ( line->getVec().x ) +
         ( ( point->y - line->getP0().y ) * ( line->getVec().y) ) +
         ( ( point->z - line->getP0().z ) * ( line->getVec().z) ) ) /
    ( line->getVec().lengthSquared()));
    
    if( u < 0.0f || u > 1.0f ){
        idata.isIntersection=false;
        return &idata;
    }
    
    idata.isIntersection=true;
    idata.pos.x = line->getP0().x + u * ( line->getVec().x );
    idata.pos.y = line->getP0().y + u * ( line->getVec().y );
    idata.pos.z = line->getP0().z + u * ( line->getVec().z );
    idata.dir.set(idata.pos- *point);
 
    return &idata;
    
}
