//
//  SkinPoint.cpp
//  skinningTool
//
//  Created by PleekMan on 14/2/2019.
//
//

#include "SkinPoint.h"

void SkinPoint::init(){
    
    //pivotPoint = ofVec3f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5, 0.0);
    vertexPos = ofVec3f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.75, 0.0);
    
    //vertexTransform = ofMatrix4x4();
    //vertexTransform.makeTranslationMatrix(vertexPoint - pivotPoint);
    
    
    
}

//------

void SkinPoint::update(){
    
    //ofMatrix4x4 rotMatrix;
    
    //vertexPoint = pivotPoint * vertexPoint;
}

//-------

void SkinPoint::render(){
    
    ofSetColor(255, 0, 0);
    ofDrawCircle(vertexPos, 10.0);
    
    ofSetColor(0, 255, 0);
    ofDrawCircle(vertexOffset, 10.0);
    
}

void SkinPoint::rotate(ofMatrix4x4 *rotMatrix){
    ofVec3f rotatedVertex = vertexOffset * *rotMatrix;
    vertexPos = (*bones)[boneAttach] + rotatedVertex;
}

void SkinPoint::setBone(int boneId){
    boneAttach = boneId;
    vertexOffset = vertexPos - (*bones)[boneAttach];
}

void SkinPoint::setBoneSystem(vector<ofVec3f> *system){
    bones = system;
}
