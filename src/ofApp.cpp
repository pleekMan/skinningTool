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
    //skin.createSkinPoint(vertex0);
    //skin.createSkinPoint(vertex1);
    //skin.createSkinPoint(vertex2);

    
    // SETUP SkinPivots
    //skin.createSkinPivot(pivot0, 0);
    //skin.createSkinPivot(pivot1, 1);
    
    
    // ATTACHING Points AND Pivots
    //SkinPoint* sPo0 = skin.getSkinPoint(0);
    //SkinPoint* sPo1 = skin.getSkinPoint(1);
    //SkinPoint* sPo2 = skin.getSkinPoint(2);
    
    //SkinPivot* sPi0 = skin.getSkinPivot(0);
    //SkinPivot* sPi1 = skin.getSkinPivot(1);
    
    // assign weights
    //skin.bind(sPo0, sPi0, 1.0);
    //skin.bind(sPo0, sPi1, 0.5);
    
    //skin.bind(sPo1, sPi0, 0.5);
    //skin.bind(sPo1, sPi1, 0.5);
    
    //skin.bind(sPo2, sPi1, 1.0);
    
    /*
    ofVec3f* pivot3 = &pivot0;
    cout << &pivot0 << " | " << *pivot3 << endl;
    cout << ofToString(pivot3 == &pivot0) << endl;
    //pivot3 == &pivot0;
    */
    //------
    
    
    //buildSnake();
    skinTheBall();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    
    SkinPivot* pivot1 = skin.getSkinPivot(selectedPivot);
    //pivot1->setTransformedPosition(ofVec3f(pivot1->position.x, ofGetMouseY()));
    pivot1->setRotation(ofMap(ofGetMouseX(), 0, ofGetWindowWidth(), 0, HALF_PI));
    //pivot1->setRotation(HALF_PI);

    //cout << ofToString(pivot1->rotation) << endl;
    
    skin.update();
    
    skin.drawPose();
    skin.drawPoints();
    skin.drawPivots();
    
    skin.drawTensorsForPoint(skin.getSkinPoint( selectedPoint % skin.getSkinPoints()->size() ));
    
    if(showPivotHeatMap){
        skin.drawHeatMapForPivot(skin.getSkinPivot(selectedPivot));
    }
    
    ofSetColor(0,255,255);
    ofDrawBitmapString(ofToString(ofVec2f(ofGetMouseX(),ofGetMouseY())), ofGetMouseX(), ofGetMouseY());
    

}

void ofApp::buildSnake(){
    
    float separation = 50;
    ofVec3f startPos = ofVec3f(100,100);
    
    // SkinPoints
    for (int i =0; i<12; i++) {
        ofVec3f topV = startPos + ofVec3f(separation * i, startPos.y);
        ofVec3f bottomV = startPos + ofVec3f(separation * i, startPos.y + separation);
        
        skin.createSkinPoint(topV);
        skin.createSkinPoint(bottomV);
    }
    
    //SkinPivots
    ofVec3f pivotStartPos = ofVec3f(150,125);
    for (int i =0; i<5; i++) {
        ofVec3f pivot = pivotStartPos + ofVec3f(separation * i, startPos.y);
        
        skin.createSkinPivot(pivot);
    }

    skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), 200);
    
    
}
//--------------------------------------------------------------

void ofApp::skinTheBall(){
    
    ofPath circle;
    circle.circle(500, 500, 300);
    
    vector<ofVec3f> verts = circle.getOutline()[0].getVertices(); // GET THE VERTICES OF THE FIRST PATH INSIDE THE ofPath
    
    // SKIN POINTS
    for (int i=0; i<verts.size(); i++) {
        skin.createSkinPoint(verts[i]);
    }
    
    skin.createSkinPivot(ofVec3f(400, 400));
    skin.createSkinPivot(ofVec3f(600, 400));
    skin.createSkinPivot(ofVec3f(400, 600));
    skin.createSkinPivot(ofVec3f(600, 600));
    
    skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), 500);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        selectedPivot = 0;
    }
    if (key == '2') {
        selectedPivot = 1;
    }
    
    if (key == '3') {
        skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), 500 * (ofGetMouseY() / (float)ofGetWindowHeight() ));
    }
    
    if (key == 'q' || key == 'Q') {
        selectedPoint--;
    }
    if (key == 'w' || key == 'W') {
        selectedPoint++;
    }
    
    if (key == 'c' || key == 'C') {
        skin.clearPointBindings();
    }
    
    if (key == 'h' || key == 'H') {
        showPivotHeatMap = !showPivotHeatMap;
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
