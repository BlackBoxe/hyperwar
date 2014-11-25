#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    int   appFPS;
    float sequenceFPS;
    bool  bFrameIndependent;
    vector <ofImage> images;

    vector <ofImage> backgroundImages;
    ofImage backgroundImage;

    vector <ofImage> decoupesImages;
    vector <ofVec3f> decoupesVec;
    int NB_DECOUPES;

    ofImage plan;
    // plein de plans 3D
    vector <ofVec3f> planVec;

    ofLight pointLight;
	ofLight spotLight;
	ofLight directionalLight;

	float radius;
	ofVec3f center;

    vector <int> calibX, calibY;
    int selected;
    
    int _mouseX, _mouseY;
    
    float vitX;
    float vitY;
    
    int backgroundWidth = 5000;
    int backgroundHeight = 3000;
    
    float virtualX, virtualY;
    
};
