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
    ofVec3f pivot0 = ofVec3f(100,200);
    ofVec3f pivot1 = ofVec3f(200,200);
    
    // SETUP SkinPoints
    skin.createSkinPoint(vertex0);
    skin.createSkinPoint(vertex1);
    skin.createSkinPoint(vertex2);

    
    // SETUP SkinPivots
    skin.createSkinPivot(pivot0, 0);
    skin.createSkinPivot(pivot1, 1);
    
    
    // ATTACHING Points AND Pivots
    SkinPoint* sPo0 = skin.getSkinPoint(0);
    SkinPoint* sPo1 = skin.getSkinPoint(1);
    SkinPoint* sPo2 = skin.getSkinPoint(2);
    
    SkinPivot* sPi0 = skin.getSkinPivot(0);
    SkinPivot* sPi1 = skin.getSkinPivot(1);
    
    // assign weights
    skin.bind(sPo0, sPi0, 0.5);
    skin.bind(sPo0, sPi1, 0.5);
    
    //skin.bind(sPo1, sPi0, 0.5);
    //skin.bind(sPo1, sPi1, 0.5);
    
    //skin.bind(sPo2, sPi1, 1.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    
    SkinPivot* pivot1 = skin.getSkinPivot(selectedPivot);
    //pivot1->setTransformedPosition(ofVec3f(pivot1->position.x, ofGetMouseY()));
    //pivot1->setRotation(ofMap(ofGetMouseX(), 0, ofGetWindowWidth(), 0, HALF_PI));
    
    pivot1->setRotation(HALF_PI);

    //cout << ofToString(pivot1->rotation) << endl;
    
    skin.update();
    
    skin.drawPose();
    skin.drawPoints();
    skin.drawPivots();
    
    
    //string p1t = ofToString(skin.getSkinPoint(0)->getPosition());
    
    
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
        selectedPivot = 0;
    }
    if (key == '2') {
        selectedPivot = 1;
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
