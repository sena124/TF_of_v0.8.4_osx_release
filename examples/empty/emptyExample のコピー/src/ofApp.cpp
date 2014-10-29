#include "ofApp.h"
#include <vector>
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
	ofSetFrameRate(60);

}

//--------------------------------------------------------------
void ofApp::update(){

}


void ofApp::draw(){
    
    ofSetColor(255,0,0);
    
    for (int i =0 ; i<=10 ; i++) {
        for (int j =0 ; j<=100 ; j++) {
            ofRect(10*4*i+i, 10*4*j+j, 20, 20);
        }
    }
    
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