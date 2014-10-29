#include "Scratch.hpp"

ScratchScene::ScratchScene(){
    myImage.loadImage("./Scratch/sky.jpg");
    myImage.draw(0,0);
    setup();
}
ScratchScene::~ScratchScene(){
}

void ScratchScene::setup(){
    for (int i =0; i<200; i++){
        for (int j =0; j<200; j++){
            part[i][j].x = (float)0.03*i;
            part[i][j].y = (float)0.03*j;
        }
    }
}

void ScratchScene::update(){
    poss = osc::getpos(true);
}

void ScratchScene::draw(){
    ofPushStyle();
        myImage.draw(0, 0, 3, 0.5*1440/640 );
    
    ofSetColor(255,0,0);
    for (int i =0; i<200; i++){
        for (int j =0; j<200; j++){
            ofCircle(part[i][j].x,part[i][j].y,0.02);
        }
    }
    ofSetColor(255,255,255);
    for(auto it = poss.begin(); it != poss.end(); it++){
        ofCircle(*it, 0.02);
        for (int i =0; i<200; i++){
            for (int j =0; j<200; j++){
                if(part[i][j].x-0.03 < it->x && it->x < part[i][j].x+0.03){
                    if(part[i][j].y-0.03 < it->y && it->y < part[i][j].y+0.03){
                        part[i][j].x = 0;
                        part[i][j].y = 0;
                    }
                }
            }
        }
    }
    ofPopStyle();
}