//
//  SkinPivot.cpp
//  skinningTool
//
//  Created by PleekMan on 15/2/2019.
//
//

#include "SkinPivot.h"

SkinPivot::SkinPivot(ofVec3f & pos){
    setPosition(pos.x, pos.y);

}


//-------

void SkinPivot::setPosition(ofVec3f & pos){
    setPosition(pos.x, pos.y);
}

//----------

void SkinPivot::setPosition(float x, float y){
    position = ofVec3f(x, y, 0);
}
