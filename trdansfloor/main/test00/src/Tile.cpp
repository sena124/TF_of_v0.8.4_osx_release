#include "Tile.hpp"

const float Tile::SIZE              = 0.15;
const float Tile::DEATH_DISTANCE    = 0.2;
const float Tile::EXPLODE_RAD       = 0.5;
const float Tile::EXPLODE_SEC       = 0.8;

Tile::Tile(){
    explode_time = MAXFLOAT;
    pos.x = ofRandom(config::ASPECT_RATIO);
    pos.y = ofRandom(1.);
}

Tile::~Tile(){
}

void Tile::update(vector<ofVec2f> persons){
    for(auto it = persons.begin(); it != persons.end(); it++){
        if(it->distance(pos) < DEATH_DISTANCE)
            explode_time = ofGetElapsedTimef();
    }
}

void Tile::draw(){
    if( explode_time == MAXFLOAT){
        ofPushStyle();
        ofSetColor(ofColor::white);
        ofRect(pos - (SIZE / 2), SIZE, SIZE);
        ofSetColor(ofColor::red);
        ofCircle(pos,0.05);
        ofPopStyle();
    } else {
        ofPushStyle();
        ofSetColor(ofColor::red);
        ofRect(pos - (SIZE / 2), SIZE, SIZE);
        ofSetColor(ofColor::white);
        ofCircle(pos,0.05);
        ofPopStyle();
    }
}

bool Tile::islive(){
    return ofGetElapsedTimef() - explode_time < EXPLODE_SEC;
}

TileScene::TileScene(){
}
TileScene::~TileScene(){
}

void TileScene::update(){
    for(int i = 0; i < TILE_NUM - tiles.size(); i++ )
        tiles.push_back(new Tile());

    for(auto it = tiles.begin(); it != tiles.end();){
        if(!(*it)->islive()) {
            delete  *it;
            it = tiles.erase(it);
        }else {
            ++it;
        }
    }
    
    persons = osc::getpos(false);
    for (auto it = tiles.begin(); it != tiles.end(); it++) {
        (*it)->update(persons);
    }
}

void TileScene::draw(){
    for (auto it = tiles.begin(); it != tiles.end(); it++) {
        (*it)->draw();
    }
    
    if(persons.size() == 0)
        return;
    for(auto it = persons.begin(); it != persons.end(); it++){
        ofCircle(*it, 0.05);
    }
}

