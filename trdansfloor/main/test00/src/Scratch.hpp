#pragma once
#include <vector>
#include "ofMain.h"
#include "Scene.hpp"
#include "osc.hpp"

class ScratchScene :public Scene{
public:
    ScratchScene();
    ~ScratchScene();
    void update();
    void draw();
    void setup();
    
    vector<ofVec2f> poss;
    ofImage myImage;
    ofVec2f part[200][200];
};