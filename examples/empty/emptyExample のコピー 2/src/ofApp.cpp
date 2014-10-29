#include "ofApp.h"
#include <vector>
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
	ofSetFrameRate(60);
    
    x =0.;
    y =200.;

}

//--------------------------------------------------------------
void ofApp::update(){
        x = x + 0.033f;
}

//--------------------------------------------------------------

void ofApp::draw(){
    ofSetColor(255, 0, 0, 100);
    ofCircle(300+sin(x)*100, y, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
		scale = scale+1;
	}
    


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}