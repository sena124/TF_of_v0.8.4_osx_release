#include "Test.hpp"

TestScene::TestScene(){
}
TestScene::~TestScene(){
}

void TestScene::update(){
    poss = osc::getpos(config::USE_DUMMY_DATA);
}

void TestScene::draw(){
    if(poss.size() == 0)
        return;
    for(auto it = poss.begin(); it != poss.end(); it++){
        ofCircle(*it, 0.02);
    }
}