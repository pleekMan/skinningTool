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
    SkinPoint(ofVec3f linkedVert, int _id);
    
    void init();
    void update();
    void render();
    
    void setPosePosition(ofVec3f pos);
    void setPosition(ofVec3f newPos);
    void attachToPivot(SkinPivot *pivot, float weight);
    
    ofVec3f* getPosition();
    ofVec3f* getPosePosition();

    void setId(int _id);
    
    vector<SkinPivot*> getPivots();
    vector<float> getWeights();

    bool hasPivotsAttached();
    
    void normalizeWeights();
    
    ofVec3f posePosition; // INITIAL POSITION OF BOTH VERTEX AND SKINPOINT
    ofVec3f* linkedVertex; // WILL TRANSFORM THIS VERTEX
    int pointId;
      
    
    
private:
    
    
    vector<SkinPivot *> pivots;
    vector<float> weights;
    
    int isAlreadyAttachedTo(SkinPivot* pivot);
    void addPivot(SkinPivot* pivot, float weight);
    void updatePivot(int pivotId, float weight);

    
};
