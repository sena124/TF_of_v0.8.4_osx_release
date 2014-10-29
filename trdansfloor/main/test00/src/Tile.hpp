#pragma once

#include <vector>
#include "ofMain.h"
#include "Scene.hpp"
#include "osc.hpp"

class Tile {
public:
    static const float SIZE;
    static const float DEATH_DISTANCE ;
    static const float EXPLODE_RAD;
    static const float EXPLODE_SEC;
    ofVec2f pos;
    float explode_time;
    Tile();
    ~Tile();
    void update(vector<ofVec2f> persons);
    void draw();
    bool islive();
};

class TileScene :public Scene {
public:
    const int TILE_NUM = 6;
    vector<Tile*> tiles;
    vector<ofVec2f> persons;
    TileScene();
    ~TileScene();
    void update();
    void draw();
};