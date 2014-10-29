#include "Orgel.hpp"

OrgelScene::OrgelScene(){
    int bufferSize = 256;
    line.assign(bufferSize, 0.0);
    sonar.loadSound("./Orgel/sonar.mp3");
}
OrgelScene::~OrgelScene(){
    
}
void OrgelScene::update(){
    poss = osc::getpos(true);
}
void OrgelScene::draw(){
    ofPushStyle();
    if(poss.size() == 0)
        return;
    for(auto it = poss.begin(); it != poss.end(); it++){
        ofCircle(*it, 0.02);
        ofPushMatrix();
        ofScale(1./config::HEIGHT, 1./config::HEIGHT);
        
        for (int i = 0; i < line.size(); i++){
            ofVertex(t_posx1-line[i]*180.0f,i*2);
        }
        if (t_posx1-5 <= it->x*config::HEIGHT && it->x*config::HEIGHT <= t_posx1) {
            ofSetColor(245, 58, 135);
            ofSetLineWidth(3);
            ofBeginShape();
            for (unsigned int i = 0; i < line.size(); i++){
                ofVertex(t_posx1-line[i]*180.0f,i*line.size()/1);
            }
            ofEndShape(false);
            for (int i = 1; i<10; i++) {
                ofCircle(config::HEIGHT * it->x,config::HEIGHT * it->y, 5*i);
            }
            sonar.play();
            cout <<config::HEIGHT * it->x;
            cout <<",";
            cout <<config::HEIGHT * it->y;
            cout << "\n";
        } else {
            ofSetColor(255, 255, 255);
            ofSetLineWidth(3);
            ofBeginShape();
            for (unsigned int i = 0; i < line.size(); i++){
                ofVertex(t_posx1-line[i]*180.0f,i*line.size()/1);
            }
            ofEndShape(false);
            cout <<config::HEIGHT * it->x;
            cout <<",";
            cout <<config::HEIGHT * it->y;
            cout << "\n";
        }
        ofPopMatrix();
    }
    ofPopStyle();
    
}