#include "Moire.hpp"


MoireScene::MoireScene(){
    
}
MoireScene::~MoireScene(){
    
}

void MoireScene::set_xy(){
    for (int i =0; i<360;i++ ){
        x[i] = sin(i);
        y[i] = cos(i);
    }
}
void MoireScene::update(){
    poss = osc::getpos(true);
    
    set_xy();
    r =r+0.01;
    
}

void MoireScene::draw(){
    ofPushStyle();
    if(poss.size() == 0)
        return;
    for(auto it = poss.begin(); it != poss.end(); it++){
        
        
        a = it->x;
        b = it->y;
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(255, 255 , 255, 100-r*100);
        for (int i =0; i<359;i++ ){
            ofLine(a+x[i]*r, b+y[i]*r, a+x[i+1]*r, b+y[i+1]*r);
        }
        
        
        ofCircle(*it, 0.02);
    }
    ofPopStyle();
}
