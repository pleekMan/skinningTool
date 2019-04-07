//
//  SkinTool.cpp
//  skinningTool
//
//  Created by PleekMan on 5/4/2019.
//
//

#include "SkinTool.h"
//#include "SkinPivot.h"


//-----

void SkinTool::update(){
    
    // FOR ALL SkinPoints
    for (int i=0; i<points.size(); i++) {
        
        SkinPoint* sPo = &points[i];
        
        // FOR ALL ATTACHED SkinPivots
        for (int j=0; j < sPo->getPivots().size(); j++) {
            
            SkinPivot* sPi = sPo->getPivots()[j];
            
            // CALCULATE SkinPivot OFFSET
            ofVec3f pivotDelta = sPi->position - sPi->posePosition;
            
            // Multiply by weight
            pivotDelta *= sPo->getWeights()[j];
            
            // Apply to SkinPoint
            sPo->transform(pivotDelta);
            
        }
        
    }
}
//-----

void SkinTool::drawPivots(){
    ofSetColor(255,0,0);
    //ofNoFill();
    for (int i=0; i<pivots.size(); i++) {
        ofDrawLine(pivots[i].position.x, pivots[i].position.y - 12, pivots[i].position.x, pivots[i].position.y + 4);
        ofDrawLine(pivots[i].position.x - 5, pivots[i].position.y, pivots[i].position.x + 5, pivots[i].position.y);
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
