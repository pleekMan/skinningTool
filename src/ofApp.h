#pragma once

#include "ofMain.h"
#include "SkinTool.h"

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
    
    int selectedPivot;
    
    /*
    ofVec3f vertex1;
    ofVec3f vertex2;
    ofVec3f vertex3;
		
    ofVec3f pivot1;
    ofVec3f pivot2;
    */
    
private:
    void buildSnake();
    
};
