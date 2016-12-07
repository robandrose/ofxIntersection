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

/************** Ray  ************/
IntersectionData ofxIntersection::RayPlaneIntersection(IsRay&ray, IsPlane &plane){
    IntersectionData idata;
    
    float u=0;
    float denom = plane.getNormal().dot(ray.getVec());

    // check if ray is paralles to plane:
    if (fabs(denom) > EPS) {
        u= plane.getNormal().dot(plane.getP0()-ray.getP0())/denom;
        idata.isIntersection=true;
        idata.pos.set(ray.getP0()+ray.getVec()*u);
        return idata;
    }else{
        idata.isIntersection=false;
        return idata;
    }
    
}

IntersectionData ofxIntersection::RayTriangleIntersection(IsTriangle& triangle, IsRay& ray){
    
    // Copied from ofxRayTriangleIntersection
    
    IntersectionData idata;
    ofVec3f rayStart=ray.getP0();
    ofVec3f rayDir=ray.getVec();
    ofVec3f triNorm = triangle.getNormal();
    float vn = rayDir.dot(triNorm);
    
    ofVec3f aa = rayStart - triangle.getP0();
    float xpn = aa.dot(triNorm);
    float distance = -xpn / vn;
    
    if (distance < 0) return idata; // behind ray origin. fail
    
    ofPoint hitPos(rayDir.x * distance + rayStart.x,
                   rayDir.y * distance + rayStart.y,
                   rayDir.z * distance + rayStart.z);
    
    ofVec3f hit00 = hitPos - triangle.getP0();
    ofVec3f hit01 = triangle.getP1() - triangle.getP0();
    ofVec3f cross0 = hit00.cross(hit01);
    if (cross0.dot(triNorm) > EPS) return idata; // not in triangle. fail
    
    ofVec3f hit10 = hitPos - triangle.getP1();
    ofVec3f hit11 = triangle.getP2() - triangle.getP1();
    ofVec3f cross1 = hit10.cross(hit11);
    if (cross1.dot(triNorm) > EPS) return idata; // not in triangle. fail
    
    ofVec3f hit20 = hitPos - triangle.getP2();
    ofVec3f hit21 = triangle.getP0() - triangle.getP2();
    ofVec3f cross2 = hit20.cross(hit21);
    if (cross2.dot(triNorm) > EPS) return idata;; // not in triangle. fail
    
    idata.isIntersection=true;
    idata.pos=hitPos;
    idata.dist=distance;

}



float ofxIntersection::PointPlaneDistance(ofPoint &point, IsPlane &plane){
    return plane.getNormal().dot((point-plane.getP0()));
}



/************** Line  ************/

IntersectionData ofxIntersection::LinePlaneIntersection(IsLine& line, IsPlane& plane){
    IntersectionData idata;
    
    float dist1=PointPlaneDistance(line.p0, plane);
    float dist2=PointPlaneDistance(line.p1, plane);
    int pos1=ofSign(dist1);
    int pos2=ofSign(dist2);
    
    if(pos1==pos2){
        idata.isIntersection=false;
        return idata;
    };
    
    float u=0;
    float denom = plane.getNormal().dot(line.getVec());
    
    // check if ray is paralles to plane:
    
    if (fabs(denom) > EPS) {
        u= plane.getNormal().dot(plane.getP0()-line.getP0())/denom;
        // check if intersection is within line-segment:
        if(u>1.0 || u<0){
            idata.isIntersection=false;
            return idata;
        }
        idata.isIntersection=true;
        idata.pos.set(line.getP0()+line.getVec()*u);
        return idata;
    }else{
        idata.isIntersection=false;
        return idata;
    }
}



IntersectionData ofxIntersection::LineLineIntersection(IsLine& line1, IsLine& line2){
    IntersectionData idata;
    
    ofPoint p13,p43,p21;
    
    ofPoint p1=line1.getP0();
    ofPoint p2=line1.getP1();
    ofPoint p3=line2.getP0();
    ofPoint p4=line2.getP1();
    
    
    double d1343,d4321,d1321,d4343,d2121;
    double numer,denom;
    double mua, mub;
    ofPoint pa, pb;
    
    p13.x = p1.x - p3.x;
    p13.y = p1.y - p3.y;
    p13.z = p1.z - p3.z;
    p43.x = p4.x - p3.x;
    p43.y = p4.y - p3.y;
    p43.z = p4.z - p3.z;
    if (ABS(p43.x) < EPS && ABS(p43.y) < EPS && ABS(p43.z) < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    p21.x = p2.x - p1.x;
    p21.y = p2.y - p1.y;
    p21.z = p2.z - p1.z;

    if (ABS(p21.x) < EPS && ABS(p21.y) < EPS && ABS(p21.z) < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    d1343 = p13.x * p43.x + p13.y * p43.y + p13.z * p43.z;
    d4321 = p43.x * p21.x + p43.y * p21.y + p43.z * p21.z;
    d1321 = p13.x * p21.x + p13.y * p21.y + p13.z * p21.z;
    d4343 = p43.x * p43.x + p43.y * p43.y + p43.z * p43.z;
    d2121 = p21.x * p21.x + p21.y * p21.y + p21.z * p21.z;
    
    denom = d2121 * d4343 - d4321 * d4321;
    if (ABS(denom) < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    numer = d1343 * d4321 - d1321 * d4343;
    mua = numer / denom;
    mub = (d1343 + d4321 * (mua)) / d4343;
    
    pa.x = p1.x + mua * p21.x;
    pa.y = p1.y + mua * p21.y;
    pa.z = p1.z + mua * p21.z;
    pb.x = p3.x + mub * p43.x;
    pb.y = p3.y + mub * p43.y;
    pb.z = p3.z + mub * p43.z;
    
    idata.isIntersection=true;
    idata.pos.set(pa);
    idata.dir.set(pb-pa);
    return idata;
    
}


IntersectionData ofxIntersection::PointLineDistance(ofPoint& point, IsLine& line){
    float u;
    ofVec3f dist;
    IntersectionData idata;
    
    
    u = ( ( ( point.x - line.getP0().x ) * ( line.getVec().x ) +
           ( ( point.y - line.getP0().y ) * ( line.getVec().y) ) +
           ( ( point.z - line.getP0().z ) * ( line.getVec().z) ) ) /
         ( line.getVec().lengthSquared()));
    
    if( u < 0.0f || u > 1.0f ){
        idata.isIntersection=false;
        return idata;
    }
    
    idata.isIntersection=true;
    idata.pos.x = line.getP0().x + u * ( line.getVec().x );
    idata.pos.y = line.getP0().y + u * ( line.getVec().y );
    idata.pos.z = line.getP0().z + u * ( line.getVec().z );
    idata.dir.set(idata.pos- point);
    
    return idata;
    
}





/************** Plane  ************/


IntersectionData ofxIntersection::PlanePlaneIntersection(IsPlane &plane1, IsPlane& plane2){
    IntersectionData idata;
    
    ofVec3f n1=plane1.getNormal();
    ofVec3f n2=plane2.getNormal();
    float d1=plane1.getDCoeff();
    float d2=plane2.getDCoeff();
    
    // Check if planes are parallel, if so return false:
    ofVec3f dir=plane1.getNormal().cross(plane2.getNormal());
    
    if(dir.length() < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    idata.isIntersection=true;
    // Direction of intersection is the cross product of the two normals:
    dir.normalize();
    
    // Thank you Toxi!
    float offDiagonal = n1.dot(n2);
    double det = 1.0 / (1 - offDiagonal * offDiagonal);
    double a = (d1 - d2 * offDiagonal) * det;
    double b = (d2 - d1 * offDiagonal) * det;
    ofVec3f anchor = n1.scale((float) a)+n2.scale((float) b);
    
    
    idata.pos=anchor;
    idata.dir=dir;
    return idata;
}





IntersectionData ofxIntersection::PlaneRectangleIntersection(IsPlane &plane, IsRectangle& rect){
    IntersectionData idata;
    
    ofVec3f n1=plane.getNormal();
    ofVec3f n2=rect.getNormal();
    float d1=plane.getDCoeff();
    float d2=rect.getDCoeff();
    
    // Check if planes are parallel, if so return false:
    ofVec3f dir=plane.getNormal().cross(rect.getNormal());
    
    if(dir.length() < EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    idata.isIntersection=true;
    // Direction of intersection is the cross product of the two normals:
    dir.normalize();
    
    // Thank you Toxi!
    float offDiagonal = n1.dot(n2);
    double det = 1.0 / (1 - offDiagonal * offDiagonal);
    double a = (d1 - d2 * offDiagonal) * det;
    double b = (d2 - d1 * offDiagonal) * det;
    ofVec3f anchor = n1.scale((float) a)+n2.scale((float) b);
    
    
    // TODO: find intersections wiht edges of Rectangle
    
    IsLine edges[4];
    
    for(int i=0;i<4;i++){
    
    //    IsLine[i].set(rect.getPos()-rect.width);
        
        
        
    }
    
    
    
    
    idata.pos=anchor;
    idata.dir=dir;
    
    
    
    
    
    return idata;
}



IntersectionData ofxIntersection::PlanePlanePlaneIntersection(IsPlane &plane1, IsPlane &plane2, IsPlane &plane3){

    
    IntersectionData idata;
    
    float d1=plane1.getDCoeff();
    float d2=plane2.getDCoeff();
    float d3=plane3.getDCoeff();
    
    ofVec3f n1=plane1.getNormal();
    ofVec3f n2=plane2.getNormal();
    ofVec3f n3=plane3.getNormal();
    
    ofVec3f cross1=n2.crossed(n3);
    ofVec3f cross2=n3.crossed(n1);
    ofVec3f cross3=n1.crossed(n2);
    
    float det=n1.dot(cross1);
    
    if(fabs(det)<EPS){
        idata.isIntersection=false;
        return idata;
    }
    
    

    idata.isIntersection=true;
    idata.pos=  (d1*cross1+d2*cross2+d3*cross3)/det;
    
    return idata;
    
}

IntersectionData ofxIntersection::PlaneTriangleIntersection(IsPlane& plane, IsTriangle& triangle){
    
    IntersectionData idata;
    ofVec3f tp0=triangle.getP0();
    ofVec3f tp1=triangle.getP1();
    ofVec3f tp2=triangle.getP2();
    
    float dist1=PointPlaneDistance(tp0, plane);
    float dist2=PointPlaneDistance(tp1, plane);
    float dist3=PointPlaneDistance(tp2, plane);
    
    int pos1=ofSign(dist1);
    int pos2=ofSign(dist2);
    int pos3=ofSign(dist3);
    
    if(pos1==pos2 && pos1==pos3){
        idata.isIntersection=false;
        return idata;
    };

    vector<ofPoint>ispoints;
    bool bintersects=false;
    ofVec3f ip;
    
    if(pos1!=pos2){
        ip=LinePlaneIntersectionFast(tp0, tp1, plane);
        if(!containsValue(&ispoints, ip)){
            ispoints.push_back(ip);
        };
    }
    if(pos2!=pos3){
        ip=LinePlaneIntersectionFast(tp1, tp2, plane);
        if(!containsValue(&ispoints, ip)){
            ispoints.push_back(ip);
        };
    }
    if(pos3!=pos1){
        ip=LinePlaneIntersectionFast(tp2, tp0, plane);
        if(!containsValue(&ispoints, ip)){
            ispoints.push_back(ip);
        };
    }
    
    idata.isIntersection=true;
    idata.pos.set(ispoints.at(0));
    
    if(ispoints.size()==2){
        idata.dir.set(ispoints.at(1));
        idata.dir-=idata.pos;
        idata.dist=idata.dir.length();
    }
    
    return idata;

}

ofVec3f ofxIntersection::LinePlaneIntersectionFast(ofPoint& p0, ofPoint& p1, IsPlane& plane){
    ofVec3f vec(p1-p0);
    float denom = plane.getNormal().dot(vec);
    float u= plane.getNormal().dot(plane.getP0()-p0)/denom;
    return p0+vec*u;
}



bool ofxIntersection::containsValue(vector<ofPoint> *points, ofPoint point){
    for(int i=0;i<points->size();i++){
        if((points->at(i)-point).length()<EPS ){
            return true;
        }
    }
    return false;
}
