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
    
    void drawPose();
    void drawPivots();
    void drawPoints();
    
    void createSkinPoint(ofVec3f vertex);
    void createSkinPivot(ofVec3f vert, int _id);

    
    SkinPoint* getSkinPoint(int i);
    SkinPivot* getSkinPivot(int i);
    int getPointCount();
    vector<SkinPoint>* getSkinPoints();
    vector<SkinPivot>* getSkinPivots();



    
    void bind(SkinPoint *point, SkinPivot *pivot, float weight);
    void bindByDistance(vector<SkinPoint>* inPoints, vector<SkinPivot>* inPivots, float distanceLimit);
    
    vector<SkinPivot> pivots;
    vector<SkinPoint> points;
    
private:
    bool isAlreadyAttached(SkinPoint* point, SkinPivot* pivot);

    
    
};
