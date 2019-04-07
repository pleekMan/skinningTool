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
    SkinPivot(ofVec3f &pos);
    void setPosition(ofVec3f &pos);
    void setPosition(float x, float y);
    
    ofVec3f position;
};

