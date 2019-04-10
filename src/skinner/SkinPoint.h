//
//  SkinPoint.hpp
//  skinningTool
//
//  Created by PleekMan on 14/2/2019.
//
//

#pragma once

//#ifndef SkinPoint_h
//#define SkinPoint_h

#include <stdio.h>
#include "ofMain.h"
#include "SkinPivot.h"

//#endif /* SkinPoint_h */

class SkinPoint {
    
public:
    SkinPoint(ofVec3f vertex);
    
    void init();
    void update();
    void render();
    void setPosePosition(ofVec3f pos);
    void setPosition(ofVec3f newPos);
    void attachToPivot(SkinPivot *pivot, float weight);
    
    ofVec3f* getPosition();
    ofVec3f* getPosePosition();

    vector<SkinPivot*> getPivots();
    vector<float> getWeights();

    
    vector<SkinPivot *> pivots;
    vector<float> weights;
    
    void normalizeWeights();
    
    ofVec3f posePosition; // INITIAL POSITION OF BOTH VERTEX AND SKINPOINT
    ofVec3f transformedposition; // WILL TRANSFORM THIS VERTEX
      
    
    
private:
    int isAlreadyAttachedTo(SkinPivot* pivot);
    void addPivot(SkinPivot* pivot, float weight);
    void updatePivot(int pivotId, float weight);

    
};
