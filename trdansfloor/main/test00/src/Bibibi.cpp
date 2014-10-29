#include "Bibibi.hpp"

BibibiScene::BibibiScene(){
//    ofEnableSmoothing();
    ofNoFill();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(64);
//    sound_01.loadSound("./")
}
BibibiScene::~BibibiScene(){
    
}
void BibibiScene::update(){
    position = osc::getpos(true);
    
}

void BibibiScene::draw(){
    if(position.size() == 0)
        return;
    for(auto i = position.begin(); i != position.end(); i++){
        ofCircle(*i, 0.005);//just for point.
        overlap = 0;
        for (auto j = position.begin(); j != position.end(); j++) {
            if (i < j) {
                disX = j->x - i->x;
                disY = j->y - i->y;
                distance = sqrt(disX * disX + disY * disY);
                noiseRatio = 1 / distance;
                eachDisX = disX / noiseNum;
                eachDisY = disY / noiseNum;
                clrMain = 255 * ofRandom(0.3, 1.0);
                if (distance < distanceMin) {
                    ofSetColor(clrSub, clrSub, clrMain, circleAlpha);
                }
                if (distance < distanceMode2) {
                    ofSetColor(clrSub, clrMain, clrSub, circleAlpha);
                }
                if (distance < distanceMode3) {
                    ofSetColor(clrMain, clrMain, clrSub, circleAlpha);
                }
                if (distance < distanceMode4) {
                    ofSetColor(clrMain, clrSub, clrSub, circleAlpha);
                }
                if (distance < distanceMin) {
                    if (overlap == 0) {
                        ofCircle(*i, ofRandom(0.003 * noiseRatio, 0.02 * noiseRatio * 0.7));
                        ofCircle(*j, ofRandom(0.003 * noiseRatio, 0.02 * noiseRatio * 0.7));
                        overlap++;
                    }
                    for (int k = 0; k < noiseNum; k++) {
                        ranX[k] = ofRandom(-0.01 * noiseRatio, 0.01 * noiseRatio);
                        ranY[k] = ofRandom(-0.01 * noiseRatio, 0.01 * noiseRatio);
                    }
                    for (int k = 0; k < noiseNum; k++) {
                        ofSetLineWidth(noiseRatio);
                        if (k != 0 && k != noiseNum - 1) {
                            ofLine(i->x + k * eachDisX + ranX[k],
                                   i->y + k * eachDisY + ranY[k],
                                   i->x + (k + 1) * eachDisX + ranX[k + 1],
                                   i->y + (k + 1) * eachDisY + ranY[k + 1]);
                        }
                        else if (k == 0) {
                            ofLine(i->x,
                                   i->y,
                                   i->x + (k + 1) * eachDisX + ranX[k + 1],
                                   i->y + (k + 1) * eachDisY + ranY[k + 1]);
                        }
                        else {
                            ofLine(i->x + k * eachDisX + ranX[k],
                                   i->y + k * eachDisY + ranY[k],
                                   i->x + (k + 1) * eachDisX,
                                   i->y + (k + 1) * eachDisY);
                        }
                    }
                }
            }
        }
    }
    ofSetColor(255);
}