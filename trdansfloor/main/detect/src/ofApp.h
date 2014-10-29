#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{
    
public:
    const string TARGET_IP = "127.0.0.1";
    const int MACHINE_ID = 0;
    const int OSC_SEND_PORT_OFFSET = 60020;
    
    ofxKinect k;
    
    ofImage kimage; // color image
    ofImage dimage; // depth image
    ofImage fimage; // threshed image

    ofxPanel gui;
    ofxToggle cam_id;       // 0 or 1
    ofxIntSlider window_id; // [ 0 - 3 ]
    ofxIntSlider near;
    ofxIntSlider far;
    ofxIntSlider min_radius;
    ofxIntSlider max_radius;
    ofxIntSlider thresh;
    ofxIntSlider angle;
    ofxIntSlider split;

    ofxCvContourFinder cntr;
    
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
    
private:
    
};
