//
//  SkinPivot.hpp
//  skinningTool
//
//  Created by PleekMan on 15/2/2019.
//
//

#pragma once
//#ifndef SkinPivot_h
//#define SkinPivot_h

#include <stdio.h>
#include "ofMain.h"

//#endif

class SkinPivot {

    
public:
    SkinPivot();
    SkinPivot(ofVec3f pos, int _id);
    
    void setId(int _id);
    void setPosePosition(ofVec3f pos);
    void setTransformedPosition(ofVec3f pos);
    void setRotation(float angle);
    
    ofVec3f* getPosePosition();
    ofVec3f* getPosition();
    ofVec3f getTranslation();
    
    int pivotId;
    ofVec3f posePosition;
    ofVec3f position;
    float rotation;
};

