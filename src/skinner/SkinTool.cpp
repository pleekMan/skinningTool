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
        
        // (IF NO PIVOT WAS MOVED, REMAIN AT YOUR POSE POSITION)
        ofVec3f finalPos = *sPo->getPosePosition();
        
        // FOR ALL ATTACHED SkinPivots
        for (int j=0; j < sPo->getPivots().size(); j++) {
            
            SkinPivot* sPi = sPo->getPivots()[j];
            
            // CALCULATE SkinPivot OFFSET
            //ofVec3f boneMatrix = sPi->position - sPi->posePosition;
            
            /*
            ofMatrix4x4 boneMatrix; // (3d Bone Matrix: Transformation Matrix local to Pivot/Bone Space)
            ofMatrix4x4 rotation;
            ofMatrix4x4 translation;
            boneMatrix.makeTranslationMatrix(sPo->posePosition - sPi->posePosition);
            rotation.makeRotationMatrix(ofRadToDeg(sPi->rotation), ofVec3f(0,0,1));
            translation.makeTranslationMatrix(sPi->position - sPi->posePosition);
            */
            
            // BEGIN TRANSFORMATION SEQUENCE
            //ofVec3f transformedPoint = boneMatrix * ofVec3f(1);
            ofVec3f transformedPoint = sPo->posePosition - sPi->posePosition;
            //transformedPoint =  boneMatrix.getInverse() * transformedPoint; // translate P to origin
            //transformedPoint = rotation * transformedPoint; // rotate
            
            transformedPoint = transformedPoint.rotate(ofRadToDeg(sPi->rotation), ofVec3f(0,0,1)); // rotate
            transformedPoint = transformedPoint + (sPi->getTranslation()); // translate
            transformedPoint = transformedPoint + sPi->posePosition; // translate back to Pivot/Bone Space
            
            
            // Weighted INTERPOLATION => ADD TO FINAL POSITION -> DELTA TRANSFORM * WEIGHT
            finalPos += (transformedPoint - *sPo->getPosePosition())  * sPo->getWeights()[j];

            
        }
        
        
        // WEIGHTED INTERPOLATION
        /*
        ofVec3f finalPos = *sPo->getPosePosition();
        for (int i=0; i<transforms.size(); i++) {
        }
         */

        
        // Apply to SkinPoint
        sPo->setPosition(finalPos);
        
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

void SkinTool::drawTensorsForPoint(SkinPoint* point){
    

    ofSetColor(0, 127, 127);
    for (int i=0; i< point->getPivots().size(); i++) {
        SkinPivot* sPi = point->getPivots()[i];
        
        ofVec3f pointToPivot = sPi->posePosition - point->posePosition;
        pointToPivot *= point->getWeights()[i];
        
        ofDrawLine(point->posePosition, pointToPivot + point->posePosition);
        
    }
    
    
}

void SkinTool::drawHeatMapForPivot(SkinPivot* pivot){
    
    ofFill();
    
    int selectedPivotId = pivot->pivotId;
    
    for (int i=0; i < points.size(); i++) {
        SkinPoint* sPo = &points[i];
        
        for (int j=0; j < sPo->getPivots().size(); j++) {
            
            if(selectedPivotId == sPo->getPivots()[j]->pivotId){
                
                ofVec3f pos = *sPo->getPosition();
                ofSetColor(sPo->weights[j] * 255, 0, 0);
                
                ofDrawCircle(pos, 8);
                
                break;
            }
            
        }
        
    }
}

//-----

void SkinTool::createSkinPivot(ofVec3f node){
    
    SkinPivot newPivot = SkinPivot(node, pivotIdCounter);
    pivots.push_back(newPivot);
    
    pivotIdCounter++;
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

vector<SkinPoint>* SkinTool::getSkinPoints(){
    return &points;
}

//-----

vector<SkinPivot>* SkinTool::getSkinPivots(){
    return &pivots;
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

void SkinTool::bindByDistance(vector<SkinPoint>* inPoints, vector<SkinPivot>* inPivots, float distanceLimit){


    clearPointBindings();
    
    cout << " Pivot : Point : Weight" << endl;
    
    for(int i=0; i < points.size(); i++ ){
        SkinPoint* sPo = &(*inPoints)[i]; // GETTING A POINTER TO THE OBJECT INSIDE THE vector POINTER
        
        for(int j=0; j < pivots.size(); j++){
            SkinPivot* sPi = &(*inPivots)[j];
            
            float distance = sPi->posePosition.distance(sPo->posePosition);
            if(distance <= distanceLimit){
                float distanceNorm = ofMap(distance, 0, distanceLimit, 1, 0); // TO NORM
                bind(sPo, sPi, distanceNorm);
                cout << "-| " + ofToString(j) + " : " + ofToString(i) + " : " + ofToString(distanceNorm) << endl;
            }
        }
        
        sPo->normalizeWeights();
    }
    
    
}

//-----

void SkinTool::clearPointBindings(){
    // CLEARS ALL WEIGHTS AND ATTACHED PIVOTS FROM ALL POINTS
    // DOES NOT CLEAR points AND pivots ALREADY CREATED IN THE SKIN
    
    for (int i=0; i<points.size(); i++) {
        points[i].pivots.clear();
        points[i].weights.clear();
    }
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
