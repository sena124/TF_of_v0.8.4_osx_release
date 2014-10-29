#pragma once

#include "ofMain.h"
#include "config.hpp"

#include "osc.hpp"

#include "Scene.hpp"
#include "Test.hpp"
#include "Bibibi.hpp"
#include "Moire.hpp"
#include "Orgel.hpp"
#include "Scratch.hpp"
#include "Tile.hpp"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
//OSC//////////
#include "ofxOsc.h"
#define HOST "169.254.40.194"
#define PORT 8000
//OSC//////////
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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    Scene *scene;
    
    //Kinect//////////
    
    void drawPointCloud();
    void exit();
    
    ofxKinect kinect;
    
#ifdef USE_TWO_KINECTS
    ofxKinect kinect2;
#endif
    
    ofxCvColorImage colorImg;
    
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
    ofxCvContourFinder contourFinder;
    
    bool bThreshWithOpenCV;
    bool bDrawPointCloud;
    
    int nearThreshold;
    int farThreshold;
    
    int angle;
    
    // used for viewing the point cloud
    ofEasyCam easyCam;
    
    vector<ofPoint> vecPossFromKinect;
    vector<float> vecTmpPointX;
    vector<float> vecTmpPointY;
    ofPoint possFromKinect;
    float tmpPointX;
    float tmpPointY;
    
    //Kinect//////////
    
    
    //OSC//////////
    ofxOscSender sender;
    //OSC//////////
    
    
    
};
