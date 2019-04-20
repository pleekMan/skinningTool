//
//  Skin2D.cpp
//  skinningTool
//
//  Created by PleekMan on 5/4/2019.
//
//

#include "Skin2D.h"
//#include "SkinPivot.h"


//-----

void Skin2D::update(){
    
    
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

void Skin2D::drawPivots(){
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
void Skin2D::drawPoints(){
    ofSetColor(0, 127, 255);
    ofFill();
    for (int i=0; i<points.size(); i++) {
        ofDrawCircle(*points[i].getPosition(),3);
    }
    
}

//-----

void Skin2D::drawPose(){
    
    // PIVOTS
    
    ofSetColor(255,255,0);
    ofNoFill();
    
    for (int i=0; i<pivots.size(); i++) {
        
        ofPushMatrix();
        
        ofTranslate(pivots[i].posePosition);
        //ofRotateZ(ofRadToDeg(pivots[i].rotation));
        
        ofDrawLine(0, 0 - 20, 0, 0 + 8);
        ofDrawLine(0 - 10, 0, 0 + 10, 0);
        
        ofPopMatrix();
    }
    
    // SELECTED IN POSE/TRANSFORMED
    ofSetColor(255,0,0);
    ofDrawCircle(*pivots[selectedPivot].getPosePosition(),10);
    ofDrawCircle(*pivots[selectedPivot].getPosition(),10);
    
    //----
    
    // POINTS
    ofSetColor(255);
    ofNoFill();
    for (int i=0; i<points.size(); i++) {
        ofDrawCircle(*points[i].getPosePosition(),5);
    }
    
    // SELECTED IN POSE/TRANSFORMED
    ofSetColor(0,255,0);
    ofDrawCircle(*points[selectedPoint].getPosePosition(),10);
    ofDrawCircle(*points[selectedPoint].getPosition(),10);
    
}

//-----

void Skin2D::drawTensorsForPoint(SkinPoint* point){
    

    ofSetColor(255);
    for (int i=0; i< point->getPivots().size(); i++) {
        SkinPivot* sPi = point->getPivots()[i];
        
        ofVec3f pointToPivot = sPi->posePosition - point->posePosition;
        pointToPivot *= point->getWeights()[i];
        
        ofDrawLine(point->posePosition, pointToPivot + point->posePosition);
        
    }
    
    
}

void Skin2D::drawHeatMapForPivot(SkinPivot* pivot){
    
    ofFill();
    
    int selectedPivotId = pivot->pivotId;
    
    for (int i=0; i < points.size(); i++) {
        SkinPoint* sPo = &points[i];
        
        for (int j=0; j < sPo->getPivots().size(); j++) {
            
            if(selectedPivotId == sPo->getPivots()[j]->pivotId){
                
                ofVec3f pos = *sPo->getPosePosition();
                ofSetColor(sPo->weights[j] * 255, 0, 0);
                
                ofDrawCircle(pos, 8);
                
                break;
            }
            
        }
        
    }
    
    // HIGHLIGHT PIVOT
    
    ofSetColor(0, 255, 255);
    ofPushMatrix();
    
    ofTranslate(pivot->posePosition);
    ofRotateZ(ofRadToDeg(pivot->rotation));
    
    ofDrawLine(0, 0 - 20, 0, 0 + 8);
    ofDrawLine(0 - 10, 0, 0 + 10, 0);
    
    ofPopMatrix();
}

//-----

void Skin2D::createPivot(ofVec3f node){
    
    SkinPivot newPivot = SkinPivot(node, pivotIdCounter);
    pivots.push_back(newPivot);
    
    pivotIdCounter++;

}

//-----

void Skin2D::createPoint(ofVec3f vertex){
    SkinPoint newPoint = SkinPoint(vertex, pointIdCounter);
    points.push_back(newPoint);
    
    pointIdCounter++;

}

//-----

SkinPoint* Skin2D::getPoint(int i){
    return &points[i];
}

//-----

SkinPivot* Skin2D::getPivot(int i){
    return &pivots[i];
}

//-----

vector<SkinPoint>* Skin2D::getPoints(){
    return &points;
}

//-----

vector<SkinPivot>* Skin2D::getPivots(){
    return &pivots;
}

//-----

int Skin2D::getPointCount(){
    return points.size();
}

//-----

int Skin2D::getPivotCount(){
    return pivots.size();
}

//-----
void Skin2D::bind(SkinPoint* point, SkinPivot* pivot, float weight){
    
     point->attachToPivot(pivot, weight);
}

//-----

void Skin2D::bindByDistance(vector<SkinPoint>* inPoints, vector<SkinPivot>* inPivots, float distanceLimit){


    clearPointBindings();
    
    //cout << " Pivot : Point : Weight" << endl;
    
    for(int i=0; i < points.size(); i++ ){
        SkinPoint* sPo = &(*inPoints)[i]; // GETTING A POINTER TO THE OBJECT INSIDE THE vector POINTER
        
        for(int j=0; j < pivots.size(); j++){
            SkinPivot* sPi = &(*inPivots)[j];
            
            float distance = sPi->posePosition.distance(sPo->posePosition);
            if(distance <= distanceLimit){
                float distanceNorm = ofMap(distance, 0, distanceLimit, 1, 0); // TO NORM
                bind(sPo, sPi, distanceNorm);
                //cout << "-| " + ofToString(j) + " : " + ofToString(i) + " : " + ofToString(distanceNorm) << endl;
            }
        }
        
        sPo->normalizeWeights();
    }
    
    
}

//-----

void Skin2D::pullTensor(SkinPoint *point, SkinPivot *pivot){
    
    float pullDistance = ofDist(point->getPosePosition()->x, point->getPosePosition()->y, ofGetMouseX(), ofGetMouseY());
    ofVec3f pointPos = *point->getPosePosition();
    ofVec3f pivotPos = *pivot->getPosePosition();
    
    ofVec3f pointToPivot = pointPos - pivotPos;
    
    pullDistance = ofClamp(pullDistance, 0, pointToPivot.length());
    
    bind(point, pivot, pullDistance / pointToPivot.length());
    
    //cout << ofToString(pullDistance) << endl;
    //ofDrawBitmapString(ofToString(pullDistance), 200, 20);
}

//-----

void Skin2D::setSelectedPivot(int index){
    
    if(getPivotCount() > 0){
        selectedPivot = index % pivots.size();
    } else {
        cout << "-|| Skin2D : THE SPECIFIED PIVOT IS OUT OF RANGE" << endl;
    }
}

SkinPivot* Skin2D::getSelectedPivot(){
    return &pivots[selectedPivot];
}

int Skin2D::getSelectedPivotId(){
    return pivots[selectedPivot].pivotId;
}

//-----

void Skin2D::setSelectedPoint(int index){
    
    if(getPointCount() > 0){
        //selectedPoint = selectedPoint % getPoints()->size();
        selectedPoint = index % points.size();
    } else {
        cout << "-|| Skin2D : THE SPECIFIED POINT IS OUT OF RANGE" << endl;
    }
}

SkinPoint* Skin2D::getSelectedPoint(){
    return &points[selectedPoint];
}


int Skin2D::getSelectedPointId(){
    return points[selectedPoint].pointId;
}


//-----

void Skin2D::selectWithPointer(int x, int y){
    
    // FIRST CHECK pivots
    for (int i=0; i < pivots.size(); i++) {
        SkinPivot* spi = getPivot(i);
        
        float dist = ofDist(spi->getPosePosition()->x, spi->getPosePosition()->y, x, y);
        
        if (dist < 8) {
            setSelectedPivot(spi->pivotId);
            return;
        }
    }
    
    // SECOND CHECK POINTS
    for (int i=0; i < points.size(); i++) {
        SkinPoint* spo = getPoint(i);
        
        float dist = ofDist(spo->getPosePosition()->x, spo->getPosePosition()->y, x, y);
        
        if (dist < 8) {
            setSelectedPoint(spo->pointId);
            return;
        }
    }
}

//-----


void Skin2D::clearPointBindings(){
    // CLEARS ALL WEIGHTS AND ATTACHED PIVOTS FROM ALL POINTS
    // DOES NOT CLEAR points AND pivots ALREADY CREATED IN THE SKIN
    
    for (int i=0; i<points.size(); i++) {
        points[i].pivots.clear();
        points[i].weights.clear();
    }
}
//-----


bool Skin2D::isAlreadyAttached(SkinPoint *point, SkinPivot *pivot){
    
    for (int i=0; i<point->getPivots().size(); i++) {
        int inputPivotId = pivot->pivotId;
        int currentPivotId = point->getPivots()[i]->pivotId;
        
        if(inputPivotId == currentPivotId)return true;
    }
    
    return false;
    
}

void Skin2D::printPointData(int selectedPoint){
    
    SkinPoint* point = getPoint(selectedPoint);
    
    //string pointData = "Point => " + ofToString(selectedPoint);
    cout << "-| Point: " + ofToString(selectedPoint) << endl;
    cout << "--| Pivots | Weights " << endl;

    
    for (int i=0; i < point->getPivots().size(); i++) {
        cout << "--| " + ofToString(point->getPivots()[i]->pivotId) + " => \t\t" + ofToString(point->getWeights()[i]) << endl;
    }
    cout << "-----------" << endl;

    
}
