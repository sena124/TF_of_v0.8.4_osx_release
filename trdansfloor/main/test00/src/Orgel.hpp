#pragma once
#include <vector>
#include "ofMain.h"
#include "Scene.hpp"
#include "osc.hpp"

class OrgelScene: public Scene{
public:
    OrgelScene();
    ~OrgelScene();
    void update();
    void draw();
    vector<ofVec2f> poss;
    vector <float> line;
    ofSoundPlayer sonar;
    ofSoundStream s_sonar;
    const int t_posx1 = 300;
};
