//
//  SkinTool.cpp
//  skinningTool
//
//  Created by PleekMan on 5/4/2019.
//
//

#include "SkinTool.h"
//#include "SkinPivot.h"


void SkinTool::init(){
    
}

//-----

void SkinTool::drawPivots(){
    ofSetColor(255,0,0);
    ofFill();
    for (int i=0; i<pivots.size(); i++) {
        ofDrawCircle(pivots[i].position,5);
    }
}

//-----
void SkinTool::drawPoints(){
    ofSetColor(0, 127, 255);
    ofNoFill();
    for (int i=0; i<points.size(); i++) {
        ofDrawCircle(*points[i].getPosition(),5);
    }
}

//-----

void SkinTool::createSkinPivot(ofVec3f vert){
    SkinPivot newPivot = SkinPivot(vert);
    pivots.push_back(newPivot);
}

//-----

void SkinTool::createSkinPoint(ofVec3f vertex){
    SkinPoint newPoint = SkinPoint(vertex);
    points.push_back(newPoint);
}

//-----

SkinPoint* SkinTool::getSkinPoint(int i){
    return &points[i];
}

//-----

SkinPivot* SkinTool::getSkinPivot(int i){
    return &pivots[i];
}

//-----

int SkinTool::getPointCount(){
    return points.size();
}

//-----
void SkinTool::link(SkinPoint* point, SkinPivot* pivot, float weight){
    point->attachToPivot(pivot, weight);
}

//-----

/*
void SkinTool::setPivots(vector<ofVec3f> *pointsForPivots){
    
    for (int i=0; i < pointsForPivots->size(); i++) {
        SkinPivot newPivot = SkinPivot((*pointsForPivots)[i]);
        pivots.push_back(newPivot);
    }
    
}
 */

//--------




//---------

void SkinTool::render(){
    ofSetColor(255, 0, 0);
    ofNoFill();
    int hSize = 10;
    for (int i=0; i<pivots.size(); i++) {
        // ASTERISK
        ofDrawLine(pivots[i].position.x - hSize, pivots[i].position.y, pivots[i].position.x + hSize, pivots[i].position.y);
        ofDrawLine(pivots[i].position.x, pivots[i].position.y - hSize, pivots[i].position.x, pivots[i].position.y + hSize);
        ofDrawLine(pivots[i].position.x - hSize, pivots[i].position.y - hSize, pivots[i].position.x + hSize, pivots[i].position.y + hSize);
        ofDrawLine(pivots[i].position.x - hSize, pivots[i].position.y + hSize, pivots[i].position.x + hSize, pivots[i].position.y - hSize);
    }
}
