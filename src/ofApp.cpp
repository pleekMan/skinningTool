#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    rotation = 10;
    
    ofVec3f bonesPivot = ofVec3f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.25,0);
    
    for (int i=0; i<4; i++) {
        bonesLength.push_back(ofVec3f(0, 100,0)); // LENGTH ON Y-AXIS
        bonesPos.push_back(bonesPivot + (bonesLength[i] * i));
    }

    
    skinPoint.init();
    skinPoint.setBoneSystem(&bonesPos);
    skinPoint.setBone(bonesPos.size() - 1);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // SWINGING THE BONES (FORWARD KINEMATICS) -----------
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
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        skinPoint.setBone(1);
    }
    
    if (key == '2') {
        skinPoint.setBone(2);
    }
    
    if (key == '3') {
        skinPoint.setBone(3);
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
