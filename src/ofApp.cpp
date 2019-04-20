#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetCircleResolution(50);
    
    // GUI
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
    //skin.createPoint(vertex0);
    //skin.createPoint(vertex1);
    //skin.createPoint(vertex2);

    
    // SETUP SkinPivots
    //skin.createPivot(pivot0, 0);
    //skin.createPivot(pivot1, 1);
    
    
    // ATTACHING Points AND Pivots
    //SkinPoint* sPo0 = skin.getPoint(0);
    //SkinPoint* sPo1 = skin.getPoint(1);
    //SkinPoint* sPo2 = skin.getPoint(2);
    
    //SkinPivot* sPi0 = skin.getPivot(0);
    //SkinPivot* sPi1 = skin.getPivot(1);
    
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
    buildTheBall();
    //buildGrid();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    
    //SkinPivot* pivot1 = skin.getPivot(selectedPivot % skin.getPivots()->size());
    //pivot1->setTransformedPosition(ofVec3f(pivot1->position.x, ofGetMouseY()));
    //pivot1->setRotation(ofMap(ofGetMouseX(), 0, ofGetWindowWidth(), 0, HALF_PI));
    //pivot1->setRotation(HALF_PI);

    //cout << ofToString(pivot1->rotation) << endl;
    
    // PIVOT DRAGGING
    if (dragPivots) {
        skin.getSelectedPivot()->setTransformedPosition(ofVec3f(ofGetMouseX(), ofGetMouseY()));
    }
    
    // PER-VERTEX WEIGHT CALIBRATION
    //if (setWeightsToggle) {
        //skin.calibratePerVertex();
    //}
    
    
    
    // SKIN CALCULATIONS
    skin.update();

    
    //---- ANIMATIONS
    
    animateTheBall();
    //animateSnake();
    
    
    //-----
    
    if (drawDebug) {
        skin.drawPoints();
        skin.drawPivots();
        skin.drawPose();

        
        skin.drawTensorsForPoint(skin.getSelectedPoint());
        
        if(showPivotHeatMap){
            skin.drawHeatMapForPivot(skin.getSelectedPivot());
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
            skin.createPoint(ofVec3f(x,y,0));
        }
    }
    
    // PIVOTS
    for (int y=0; y<ofGetWindowHeight(); y+= 100) {
        for (int x=0; x<ofGetWindowWidth(); x+= 100) {
            skin.createPivot(ofVec3f(x,y));
        }
    }
    
    skin.bindByDistance(skin.getPoints(), skin.getPivots(), 200);
    
    
}

void ofApp::buildSnake(){
    
    float separation = 50;
    ofVec3f startPos = ofVec3f(100,400);
    
    // SkinPoints
    for (int i =0; i<15; i++) {
        ofVec3f topV = startPos + ofVec3f(separation * i, 0);
        ofVec3f bottomV = startPos + ofVec3f(separation * i, separation);
        
        skin.createPoint(topV);
        skin.createPoint(bottomV);
    }
    
    //SkinPivots
    ofVec3f pivotStartPos = ofVec3f(125,425);
    for (int i =0; i<7; i++) {
        ofVec3f pivot = pivotStartPos + ofVec3f(separation * i * 2, 0);
        
        skin.createPivot(pivot);
    }
    
    skin.setSelectedPivot(0);
    skin.setSelectedPoint(0);

    skin.bindByDistance(skin.getPoints(), skin.getPivots(), 200);
    
    
}

void ofApp::animateSnake(){
    
    
    for (int i=0; i < skin.getPivots()->size(); i++) {
        float noiseValue = ofNoise(skin.getPivot(i)->posePosition + ofVec3f(ofGetFrameNum() * 0.01,0,0));
        //noiseValue *= 0.2;
        
        skin.getPivot(i)->setRotation(ofMap(noiseValue, 0, 1, -HALF_PI, HALF_PI));
    }
    
    // DRAW FILLED POLY
    ofFill();
    ofSetColor(120,150,255);
    
    //ofBeginShape();
    for (int i=0; i < 14 * 2; i+=2) {
        ofBeginShape();
        ofVertex(*skin.getPoint(i)->getPosition());
        ofVertex(*skin.getPoint(i+1)->getPosition());
        ofVertex(*skin.getPoint(i+3)->getPosition());
        ofVertex(*skin.getPoint(i+2)->getPosition());
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
        skin.createPoint(verts[i]);
    }
    
    skin.createPivot(ofVec3f(400, 400));
    skin.createPivot(ofVec3f(600, 400));
    skin.createPivot(ofVec3f(400, 600));
    skin.createPivot(ofVec3f(600, 600));
    
    skin.bindByDistance(skin.getPoints(), skin.getPivots(), 300);
    
}

void ofApp::animateTheBall(){
    
    ofFill();
    ofSetColor(120,255,150,127);
    
    
    ofBeginShape();
    for (int i=0; i< skin.getPointCount(); i++) {
        ofVertex(*skin.getPoint(i)->getPosition());
    }
    ofEndShape();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
    }
    if (key == '2') {
    }
    
    if (key == '3') {
        //skin.bindByDistance(skin.getPoints(), skin.getPivots(), 500 * (ofGetMouseY() / (float)ofGetWindowHeight() ));
        skin.bindByDistance(skin.getPoints(), skin.getPivots(), distanceForAutoBindSlider);

    }
    
    // SELECT POINTS
    if (key == 'q' || key == 'Q') {
        skin.setSelectedPoint(skin.getSelectedPointId() - 1);
    }
    if (key == 'w' || key == 'W') {
        skin.setSelectedPoint(skin.getSelectedPointId() + 1);
    }
    
    // CYCLE PIVOTS
    if (key == 'a' || key == 'A') {
        skin.setSelectedPivot(skin.getSelectedPivotId() - 1);
    }
    if (key == 's' || key == 'S') {
        skin.setSelectedPivot(skin.getSelectedPivotId() + 1);
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
    
    if (key == 'i' || key == 'I') {
        skin.printPointData(skin.getSelectedPointId());
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
        skin.pullTensor(skin.getSelectedPoint(), skin.getSelectedPivot());
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    skin.selectWithPointer(x, y);
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
