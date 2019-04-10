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
    void drawTensorsForPoint(SkinPoint* point);
    void drawHeatMapForPivot(SkinPivot* pivot);
    
    void createSkinPoint(ofVec3f node);
    void createSkinPivot(ofVec3f vertex);
    
    
    SkinPoint* getSkinPoint(int i);
    SkinPivot* getSkinPivot(int i);
    int getPointCount();
    vector<SkinPoint>* getSkinPoints();
    vector<SkinPivot>* getSkinPivots();

    void clearPointBindings();
    void bind(SkinPoint *point, SkinPivot *pivot, float weight);
    void bindByDistance(vector<SkinPoint>* inPoints, vector<SkinPivot>* inPivots, float distanceLimit);
    void pullTensor(SkinPoint *point, SkinPivot *pivot);

    
    vector<SkinPivot> pivots;
    vector<SkinPoint> points;
    int pivotIdCounter = 0;
    
private:
    bool isAlreadyAttached(SkinPoint* point, SkinPivot* pivot);

    
    
};
