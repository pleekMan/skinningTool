//
//  SkinTool.hpp
//  skinningTool
//
//  Created by PleekMan on 5/4/2019.
//
//

#pragma once

//#ifndef SkinTool_h
//#define SkinTool_h

#include <stdio.h>
#include "SkinPivot.h"
#include "SkinPoint.h"
#include "ofMain.h"

//#endif /* SkinTool_h */

class SkinTool {
    
    
public:
    
    void update();
    
    void drawPivots();
    void drawPoints();
    
    void createSkinPoint(ofVec3f vertex);
    void createSkinPivot(ofVec3f vert, int _id);
    bool isAlreadyAttached(SkinPoint* point, SkinPivot* pivot);

    
    SkinPoint* getSkinPoint(int i);
    SkinPivot* getSkinPivot(int i);
    int getPointCount();

    
    void skin(SkinPoint *point, SkinPivot *pivot, float weight);
    
    vector<SkinPivot> pivots;
    vector<SkinPoint> points;
    
    
};
