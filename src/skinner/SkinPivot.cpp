//
//  SkinPivot.cpp
//  skinningTool
//
//  Created by PleekMan on 15/2/2019.
//
//

#include "SkinPivot.h"

SkinPivot::SkinPivot(ofVec3f pos){
    setPosePosition(pos);

}


//-------

void SkinPivot::setPosePosition(ofVec3f pos){
    posePosition = pos;
}

//----------

void SkinPivot::setTransformedPosition(ofVec3f pos){
    position = pos;
}
