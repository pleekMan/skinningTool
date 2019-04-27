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

class Skin2D {
    
    
public:
    
    Skin2D();
    void update();
    
    void drawPose();
    void drawPivots();
    void drawPoints();
    void drawTensorsForPoint(SkinPoint* point);
    void drawHeatMapForPivot(SkinPivot* pivot);
    
    void createPoint(ofVec3f linkedVertex);
    void createPivot(ofVec3f node);
    
    
    SkinPoint* getPoint(int i);
    SkinPivot* getPivot(int i);
    int getPointCount();
    int getPivotCount();
    vector<SkinPoint>* getPoints();
    vector<SkinPivot>* getPivots();
    
    void skin(ofPolyline* shape); // STARTS IT UP: CREATE 1 PIVOT AND CALLS bind ON EACH VERTEX
    void bind(SkinPoint *point, SkinPivot *pivot, float weight);
    void bindByDistance(vector<SkinPoint>* inPoints, vector<SkinPivot>* inPivots, float distanceLimit);
    void pullTensor(SkinPoint *point, SkinPivot *pivot);
    void clearPointBindings();

    
    void printPointData(int selectedPoint);
    
    // SELECTED PIVOT
    int selectedPivot = 0;
    void setSelectedPivot(int index);
    SkinPivot* getSelectedPivot();
    int getSelectedPivotId();
    
    // SELECTED POINT
    int selectedPoint = 0;
    void setSelectedPoint(int index);
    SkinPoint* getSelectedPoint();
    int getSelectedPointId();
    
    vector<SkinPivot> pivots;
    vector<SkinPoint> points;
    int pivotIdCounter = 0;
    int pointIdCounter = 0;
    
    
    void onMousePressed(int x, int y, int button);
    
    void selectWithPointer(int x, int y);
    
    enum EditMode {ADD_PIVOT, EDIT};
    EditMode inMode;
    void setMode(EditMode mode);

    
private:
    bool isAlreadyAttached(SkinPoint* point, SkinPivot* pivot);

    
    
};
