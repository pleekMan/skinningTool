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
            //ofVec3f boneMatrix = sPi->position - sPi->posePosition;
            
            ofMatrix4x4 boneMatrix; // (3d Bone Matrix: Transformation Matrix local to Pivot/Bone Space)
            ofMatrix4x4 rotation;
            ofMatrix4x4 translation;
            boneMatrix.makeTranslationMatrix(sPo->posePosition - sPi->posePosition);
            rotation.makeRotationMatrix(ofRadToDeg(sPi->rotation), ofVec3f(0,0,1));
            translation.makeTranslationMatrix(sPi->position - sPi->posePosition);
            
            // BEGIN TRANSFORMATION SEQUENCE
            //ofVec3f transformedPoint = boneMatrix * ofVec3f(1);
            ofVec3f transformedPoint = sPo->posePosition - sPi->posePosition;
            //transformedPoint =  boneMatrix.getInverse() * transformedPoint; // translate P to origin
            //transformedPoint = rotation * transformedPoint; // rotate
            transformedPoint = transformedPoint.rotate(ofRadToDeg(sPi->rotation * sPo->getWeights()[j]), ofVec3f(0,0,1)); // rotate
            transformedPoint = transformedPoint + (sPi->getTranslation() * sPo->getWeights()[j]); // translate
            transformedPoint = transformedPoint + sPi->posePosition; // translate back to Pivot/Bone Space
            
            
            // Multiply by weight
            //transformedPoint *= sPo->getWeights()[j];
            
            // ADD TO transformSum
            transformSum += transformedPoint; // SHOULD NOT BE SUMMED

            
        }
        
        // Apply to SkinPoint
        sPo->setPosition(transformSum);
        
    }
}
//-----

void SkinTool::drawPivots(){
    ofSetColor(255,0,0);
    //ofNoFill();
    
    for (int i=0; i<pivots.size(); i++) {
        
        ofPushMatrix();
        
        ofTranslate(pivots[i].position);
        ofRotateZ(ofRadToDeg(pivots[i].rotation));
        
        ofDrawLine(0, 0 - 20, 0, 0 + 8);
        ofDrawLine(0 - 10, 0, 0 + 10, 0);
        
        ofPopMatrix();
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

void SkinTool::drawPose(){
    
    // PIVOTS
    
    ofSetColor(200);
    //ofNoFill();
    
    for (int i=0; i<pivots.size(); i++) {
        
        ofPushMatrix();
        
        ofTranslate(pivots[i].posePosition);
        //ofRotateZ(ofRadToDeg(pivots[i].rotation));
        
        ofDrawLine(0, 0 - 20, 0, 0 + 8);
        ofDrawLine(0 - 10, 0, 0 + 10, 0);
        
        ofPopMatrix();
    }
    
    // POINTS
    ofSetColor(127);
    ofNoFill();
    for (int i=0; i<points.size(); i++) {
        ofDrawCircle(*points[i].getPosePosition(),5);
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
void SkinTool::bind(SkinPoint* point, SkinPivot* pivot, float weight){
    
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
