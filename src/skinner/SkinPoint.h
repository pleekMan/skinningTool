//
//  SkinPoint.hpp
//  skinningTool
//
//  Created by PleekMan on 14/2/2019.
//
//

#ifndef SkinPoint_h
#define SkinPoint_h

#include <stdio.h>
#include "ofMain.h"

#endif /* SkinPoint_h */

class SkinPoint {
    
public:
    void init();
    void update();
    void render();
    void setBone(int boneId);
    void setBoneSystem(vector<ofVec3f> *system);
    void rotate(ofMatrix4x4 *rotMatrix);
    
    ofMatrix4x4 vertexTransform;
    ofVec3f vertexOffset;
    ofVec3f vertexPos;
    
    vector<ofVec3f> *bones;
    int boneAttach;
    float weight;
    
    
    
private:
    
    
};
