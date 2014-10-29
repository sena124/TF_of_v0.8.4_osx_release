#pragma once

#include "ofMain.h"
#include "Scene.hpp"

#include "osc.hpp"


class MoireScene :public Scene {
public:
    MoireScene();
    ~MoireScene();
    void set_xy();
    void update();
    void draw();
    
    vector<ofVec2f> poss;
    
    float x[360];
    float y[360];
    float r;
    float a;
    float b;
    };
