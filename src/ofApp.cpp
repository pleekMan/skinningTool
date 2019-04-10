#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetCircleResolution(50);
    
    gui.setup();
    gui.add(distanceForAutoBindSlider.setup("AutoBind Distance", 100, 1, 500));
    gui.add(setWeightsToggle.setup("Set Weights Mode", false));
    
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
    
    
    buildSnake();
    //buildTheBall();
    //buildGrid();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    
    //SkinPivot* pivot1 = skin.getSkinPivot(selectedPivot % skin.getSkinPivots()->size());
    //pivot1->setTransformedPosition(ofVec3f(pivot1->position.x, ofGetMouseY()));
    //pivot1->setRotation(ofMap(ofGetMouseX(), 0, ofGetWindowWidth(), 0, HALF_PI));
    //pivot1->setRotation(HALF_PI);

    //cout << ofToString(pivot1->rotation) << endl;
    
    // PIVOT DRAGGING
    if (dragPivots) {
        skin.getSkinPivot(selectedPivot)->setTransformedPosition(ofVec3f(ofGetMouseX(), ofGetMouseY()));
    }
    
    // PER-VERTEX WEIGHT CALIBRATION
    if (setWeightsToggle) {
        //skin.calibratePerVertex();
    }
    
    
    
    // SKIN CALCULATIONS
    skin.update();

    
    //---- ANIMATIONS
    
    //animateTheBall();
    animateSnake();
    
    
    //-----
    
    if (drawDebug) {
        skin.drawPose();
        skin.drawPoints();
        skin.drawPivots();
        
        skin.drawTensorsForPoint(skin.getSkinPoint(selectedPoint));
        
        if(showPivotHeatMap){
            skin.drawHeatMapForPivot(skin.getSkinPivot(selectedPivot));
        }
        
        
        // BIND-BY-DISTANCE HELPER
        ofNoFill();
        ofSetColor(0, 127, 127);
        ofDrawCircle(ofGetMouseX(), ofGetMouseY(), distanceForAutoBindSlider);
    }
    
    
    ofSetColor(0,255,255);
    ofDrawBitmapString(ofToString(ofVec2f(ofGetMouseX(),ofGetMouseY())), ofGetMouseX(), ofGetMouseY());
    
    gui.draw();
    

}

void ofApp::buildGrid(){
    
    // POINTS
    for (int y=0; y<ofGetWindowHeight(); y+= 50) {
        for (int x=0; x<ofGetWindowWidth(); x+= 50) {
            skin.createSkinPoint(ofVec3f(x,y,0));
        }
    }
    
    // PIVOTS
    for (int y=0; y<ofGetWindowHeight(); y+= 100) {
        for (int x=0; x<ofGetWindowWidth(); x+= 100) {
            skin.createSkinPivot(ofVec3f(x,y));
        }
    }
    
    skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), 200);
    
    
}

void ofApp::buildSnake(){
    
    float separation = 50;
    ofVec3f startPos = ofVec3f(100,400);
    
    // SkinPoints
    for (int i =0; i<15; i++) {
        ofVec3f topV = startPos + ofVec3f(separation * i, 0);
        ofVec3f bottomV = startPos + ofVec3f(separation * i, separation);
        
        skin.createSkinPoint(topV);
        skin.createSkinPoint(bottomV);
    }
    
    //SkinPivots
    ofVec3f pivotStartPos = ofVec3f(125,425);
    for (int i =0; i<7; i++) {
        ofVec3f pivot = pivotStartPos + ofVec3f(separation * i * 2, 0);
        
        skin.createSkinPivot(pivot);
    }

    skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), 200);
    
    
}

void ofApp::animateSnake(){
    
    
    for (int i=0; i < skin.getSkinPivots()->size(); i++) {
        float noiseValue = ofNoise(skin.getSkinPivot(i)->posePosition + ofVec3f(ofGetFrameNum() * 0.01,0,0));
        //noiseValue *= 0.2;
        
        skin.getSkinPivot(i)->setRotation(ofMap(noiseValue, 0, 1, -HALF_PI, HALF_PI));
    }
    
    // DRAW FILLED POLY
    ofFill();
    ofSetColor(120,150,255);
    
    //ofBeginShape();
    for (int i=0; i < 14 * 2; i+=2) {
        ofBeginShape();
        ofVertex(*skin.getSkinPoint(i)->getPosition());
        ofVertex(*skin.getSkinPoint(i+1)->getPosition());
        ofVertex(*skin.getSkinPoint(i+3)->getPosition());
        ofVertex(*skin.getSkinPoint(i+2)->getPosition());
        ofEndShape();
    }
    //ofEndShape();
    
}
//--------------------------------------------------------------

void ofApp::buildTheBall(){
    
    ofPath circle;
    circle.circle(500, 500, 300);
    
    vector<ofVec3f> verts = circle.getOutline()[0].getVertices(); // GET THE VERTICES OF THE FIRST PATH INSIDE THE ofPath
    cout << "-| Verts in circle: " << verts.size() << endl;
    
    // SKIN POINTS
    for (int i=0; i<verts.size(); i++) {
        skin.createSkinPoint(verts[i]);
    }
    
    skin.createSkinPivot(ofVec3f(400, 400));
    skin.createSkinPivot(ofVec3f(600, 400));
    skin.createSkinPivot(ofVec3f(400, 600));
    skin.createSkinPivot(ofVec3f(600, 600));
    
    skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), 300);
    
}

void ofApp::animateTheBall(){
    
    ofFill();
    ofSetColor(120,255,150,127);
    
    
    ofBeginShape();
    for (int i=0; i< skin.getPointCount(); i++) {
        ofVertex(*skin.getSkinPoint(i)->getPosition());
    }
    ofEndShape();
    
    
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
        //skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), 500 * (ofGetMouseY() / (float)ofGetWindowHeight() ));
        skin.bindByDistance(skin.getSkinPoints(), skin.getSkinPivots(), distanceForAutoBindSlider);

    }
    
    // SELECT POINTS
    if (key == 'q' || key == 'Q') {
        selectedPoint--;
        selectedPoint = selectedPoint % skin.getSkinPoints()->size();

    }
    if (key == 'w' || key == 'W') {
        selectedPoint++;
        selectedPoint = selectedPoint % skin.getSkinPoints()->size();

    }
    
    // CYCLE PIVOTS
    if (key == 'a' || key == 'A') {
        selectedPivot--;
        selectedPivot = selectedPivot % skin.getSkinPivots()->size();
    }
    if (key == 's' || key == 'S') {
        selectedPivot++;
        selectedPivot = selectedPivot % skin.getSkinPivots()->size();

    }
    
    
    if (key == 'c' || key == 'C') {
        skin.clearPointBindings();
    }
    
    if (key == 'h' || key == 'H') {
        showPivotHeatMap = !showPivotHeatMap;
    }
    
    if (key == 'd' || key == 'D') {
        drawDebug = !drawDebug;
    }
    
    if (key == 'p' || key == 'P') {
        dragPivots = !dragPivots;
    }
    
    
    if (key == 'm' || key == 'M') {
        setWeightsToggle = !setWeightsToggle;
    }
    
    
    //pointWeightSlider.setFillColor(ofColor(255,0,0));
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
    if (setWeightsToggle) {
        skin.pullTensor(skin.getSkinPoint(selectedPoint), skin.getSkinPivot(selectedPivot));
    }

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
