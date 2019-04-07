#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /*
    rotation = 10;
    
    
    for (int i=0; i<3; i++) {
        bonesPos.push_back(ofVec3f(ofGetWindowWidth() * 0.5, (ofGetWindowHeight() *0.5f) + (100 * i),0));
    }
    
    skinner.setPivots(&bonesPos);
    */
    /* THIS WORKED
    skinPoint.init();
    skinPoint.setBoneSystem(&bonesPos);
    skinPoint.setBone(bonesPos.size() - 1);
     */
    
    //skin.init();
    
    // RAW VECTORS FOR POINTS
    ofVec3f vertex0 = ofVec3f(100,100);
    ofVec3f vertex1 = ofVec3f(200,100);
    ofVec3f vertex2 = ofVec3f(300,100);
    
    // RAW VECTORS FOR PIVOTS
    ofVec3f pivot0 = ofVec3f(150,200);
    ofVec3f pivot1 = ofVec3f(250,200);
    
    // SETUP SkinPoints
    skin.createSkinPoint(vertex0);
    skin.createSkinPoint(vertex1);
    skin.createSkinPoint(vertex2);

    
    // SETUP SkinPivots
    skin.createSkinPivot(pivot0);
    skin.createSkinPivot(pivot1);
    
    
    // ATTACHING Points AND Pivots
    SkinPoint* sPo0 = skin.getSkinPoint(0);
    SkinPoint* sPo1 = skin.getSkinPoint(1);
    SkinPoint* sPo2 = skin.getSkinPoint(2);
    
    SkinPivot* sPi0 = skin.getSkinPivot(0);
    SkinPivot* sPi1 = skin.getSkinPivot(1);
    
    skin.link(sPo0, sPi0, 1.0);
    skin.link(sPo2, sPi1, 1.0);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    /*
    for (int i=0; i<3; i++) {
        //bonesPos[i].x = ofGetWindowWidth() * 0.5 + (sin(ofGetFrameNum() * 0.1) * (10 * (i+1)));
        bonesPos[i].x += 1;
    }
     */
    
    
    
    
    
    // SWINGING THE BONES (FORWARD KINEMATICS) -----------
    /*
    float angleIncrement = rotation;
    
    for (int i=1; i<bonesPos.size(); i++) {
        ofVec3f parentBone = bonesPos[i-1];
        
        ofMatrix4x4 rot;
        rot.makeRotationMatrix(angleIncrement, ofVec3f(0,0,1));
        
        ofVec3f rotatedBone = bonesLength[i] * rot;
        bonesPos[i] = bonesPos[i-1] + rotatedBone;
        
        if (skinPoint.boneAttach == i) {
            skinPoint.rotate(&rot);
        }
        
        angleIncrement += rotation;
        
    }

    rotation = 50 * sin(ofGetFrameNum() * 0.01);
    
    //-----------
    
    
    skinPoint.update();
     */
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    
    SkinPivot* pivot1 = skin.getSkinPivot(0);
    pivot1->setPosition(ofGetMouseX(), ofGetMouseY());
    
    skin.drawPoints();
    skin.drawPivots();
    
    /*
    for (int i=0; i<skin.getPointCount(); i++) {
        ofVec3f* pos = skin.getSkinPoint(i)->getPosition();
        ofDrawCircle(pos->x, pos->y, 5);
        
    }
     */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // THIS WORKED
    /*
    ofSetColor(0, 255, 255);
    
    for (int i=1; i<bonesPos.size(); i++) {
        ofDrawLine(bonesPos[i], bonesPos[i-1]);
        ofDrawBitmapString(ofToString(i), bonesPos[i]);
    }
    
    //-------
    // TEST TO SEE IF THE ROTATE WITH MATRIX PROCESS IS WORKING. It is.
    
    ofVec3f root = ofVec3f(ofGetMouseX(),ofGetMouseY(),0);
    ofVec3f bone1Length = ofVec3f(0,50,0);
    
    ofMatrix4x4 rot;
    rot.makeRotationMatrix(ofGetFrameNum() % 360, ofVec3f(0,0,1));
    
    
    ofVec3f rotatedBone = rot * bone1Length;
    ofVec3f bonePos = root + rotatedBone;
    
    ofSetColor(0, 127, 255);
    ofDrawLine(root, bonePos);
    
    //------------
    
    skinPoint.render();
     */
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        //skinPoint.setBone(1);
    }
    
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
