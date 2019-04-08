//
//  SkinPoint.cpp
//  skinningTool
//
//  Created by PleekMan on 14/2/2019.
//
//

#include "SkinPoint.h"


SkinPoint::SkinPoint(ofVec3f pos){
    setPosePosition(pos);
    
}

//------

void SkinPoint::setPosePosition(ofVec3f pos){
    posePosition = pos;
}

void SkinPoint::setPosition(ofVec3f newPos){
    transformedposition = newPos;
}

ofVec3f* SkinPoint::getPosePosition(){
    return &posePosition; // CHANGE TO TRANSFORMED POSITION
}

ofVec3f* SkinPoint::getPosition(){
    return &transformedposition; // CHANGE TO TRANSFORMED POSITION
}

void SkinPoint::attachToPivot(SkinPivot *pivot, float weight){
    pivots.push_back(pivot);
    weights.push_back(weight);
}

vector <SkinPivot*> SkinPoint::getPivots(){
    return pivots;
}

vector<float> SkinPoint::getWeights(){
    return weights;
}

void SkinPoint::normalizeWeights(){
    // NORMALIZE value/count
    
    // SUM ALL UN-NORMALIZED VALUES
    float unNormalizedSum = 0;
    for (float weight : weights) {
        unNormalizedSum += weight;
    }
    
    // REMAP TO 0 -> 1
    for (int i=0; i<weights.size(); i++) {
        weights[i] = ofMap(weights[i], 0, unNormalizedSum, 0, 1);
    }
    
    
}

void SkinPoint::init(){
    
    
}

//------

void SkinPoint::update(){
    
    //ofMatrix4x4 rotMatrix;
    
    //vertexPoint = pivotPoint * vertexPoint;
}

//-------

void SkinPoint::render(){
    
    // DRAW SkinPoint GIZMO
    // STATIC => SKIN POSE
    ofSetColor(255, 125, 0);
    ofDrawCircle(posePosition, 5);
    
    // VERTEX FOLLOW
    //ofSetColor(255, 255, 0);
    //ofDrawCircle(*wrappedVertex, 5);
    
    
    
}

/*
void SkinPoint::rotate(ofMatrix4x4 *rotMatrix){
    
    // WEIGHT: "scaling" the rotation
    ofMatrix4x4 scaling = ofMatrix4x4(weight, weight, 0,0, weight, weight, 0,0,0,0,0,0,0,0,0,0);
    ofMatrix4x4 weightedRotation = *rotMatrix * 1.0f;
    
    
    ofVec3f rotatedVertex = vertexOffset * weightedRotation;
    vertexPos = (*bones)[boneAttach] + rotatedVertex;
    
    cout << ofToString(vertexPos.x) + " | " + ofToString(vertexPos.y) +  " | " + ofToString(vertexPos.z) << endl;
}
*/

/*
void SkinPoint::setBone(int boneId){
    boneAttach = boneId;
    vertexOffset = vertexPos - (*bones)[boneAttach];
}

void SkinPoint::setBoneSystem(vector<ofVec3f> *system){
    bones = system;
}
*/
