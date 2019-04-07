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
        
        ofVec3f transformSum = ofVec3f();
        
        SkinPoint* sPo = &points[i];
        
        // FOR ALL ATTACHED SkinPivots
        for (int j=0; j < sPo->getPivots().size(); j++) {
            
            SkinPivot* sPi = sPo->getPivots()[j];
            
            // CALCULATE SkinPivot OFFSET
            ofVec3f pivotDelta = sPi->position - sPi->posePosition;
            
            // Multiply by weight
            pivotDelta *= sPo->getWeights()[j];
            
            // ADD TO transformSum
            transformSum += pivotDelta;

            
        }
        
        // Apply to SkinPoint
        sPo->transform(transformSum);
        
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

void SkinTool::createSkinPivot(ofVec3f vert, int _id){
    SkinPivot newPivot = SkinPivot(vert, _id);
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
void SkinTool::skin(SkinPoint* point, SkinPivot* pivot, float weight){
    
    // CHECK IF THE POINT ALREADY IS ATTACHED TO THE PIVOT, TO NOT ADD THE SAME PIVOT TO THE SkinPoint's pivotlist
    /*
    bool alreadyAttached = isAlreadyAttached(point, pivot);
    
    if (alreadyAttached) {
        int pivotId = pivot->pivotId;
    } else{
        point->attachToPivot(pivot, weight);
    }
     */
     point->attachToPivot(pivot, weight);
}

//-----

bool SkinTool::isAlreadyAttached(SkinPoint *point, SkinPivot *pivot){
    
    for (int i=0; i<point->getPivots().size(); i++) {
        int inputPivotId = pivot->pivotId;
        int currentPivotId = point->getPivots()[i]->pivotId;
        
        if(inputPivotId == currentPivotId)return true;
    }
    
    return false;
    
}
