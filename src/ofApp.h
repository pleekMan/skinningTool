#pragma once

#include "ofMain.h"
#include "SkinTool.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    SkinTool skin;
    
    int selectedPivot = 0;
    int selectedPoint = 0;
    
    bool showPivotHeatMap = false;
    bool drawDebug = false;
    bool dragPivots = false;
    //bool setWeightsMode = false;
    
    // GUI -----
    ofxPanel gui;
    ofxFloatSlider distanceForAutoBindSlider;
    ofxToggle setWeightsToggle;

    
    
private:
    void buildSnake();
    void animateSnake();
    
    void buildTheBall();
    void animateTheBall();
    
    void buildGrid();

    
};
