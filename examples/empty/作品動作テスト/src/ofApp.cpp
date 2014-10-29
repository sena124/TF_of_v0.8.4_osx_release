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
    counter++;
    num_c = counter%200;
    if (num_c == 0) {
        scale = 0;
        num_bra = 16;
        add_ang = 10;
        slope = 0;
    }

}

//--------------------------------------------------------------
class branch_class{
    public:
    float x1,x2,y1,y2;
    int generation;
    
    branch_class(float x_1,float y_1,float x_2, float y_2){
        x1 = x_1;
        y1 = y_1;
        x2 = x_2;
        y2 = y_2;
    }
    
    branch_class(float x_1,float y_1,float x_2, float y_2, int g){
        x1 = x_1;
        y1 = y_1;
        x2 = x_2;
        y2 = y_2;
        generation = g;
    }
    
    void set_all(float x_1,float y_1,float x_2, float y_2){
        x1 = x_1;
        y1 = y_1;
        x2 = x_2;
        y2 = y_2;
    }
    
    void set_all(float x_1,float y_1,float x_2, float y_2, int g){
        x1 = x_1;
        y1 = y_1;
        x2 = x_2;
        y2 = y_2;
        generation = g;
    }
    
    float length(){
        return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
    }

};

int generation_counter(int i){
    if (i == 1){
        return 1;
    } else if (2<=i && i<=3 ){
        return 2;
    } else if (4<=i && i<=7 ){
        return 3;
    } else if (8<=i && i<=15 ){
        return 4;
    } else if (16<=i && i<=31 ){
        return 5;
    } else if (32<=i && i<=63 ){
        return 6;
    }
    
}

int branch_counter(int i){
    if (i == 1){
        return 1;
    } else if (2<=i && i<=3 ){
        return i-1;
    } else if (4<=i && i<=7 ){
        return i-3;
    } else if (8<=i && i<=15 ){
        return i-7;
    } else if (16<=i && i<=31 ){
        return i-15;
    } else if (32<=i && i<=63 ){
        return i-31;
    }
}

int max_branch(int i){
    if (i == 1){
        return 1;
    } else if (2<=i && i<=3 ){
        return 2;
    } else if (4<=i && i<=7 ){
        return 4;
    } else if (8<=i && i<=15 ){
        return 8;
    } else if (16<=i && i<=31 ){
        return 16;
    } else if (32<=i && i<=63 ){
        return 32;
    }
}

float branch_length(float x1, float y1, float x2, float y2){
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}


void ofApp::draw(){
    
    struct branch_str{
        float x1,y1,x2,y2;
        float pl1x,pl1y,pl2x,pl2y,pl3x,pl3y,pr1x,pr1y,pr2x,pr2y,pr3x,pr3y;
        int gen;
        int max_branch;
        int p_branch;
        float angle;
    };
    
    struct branch_str arr_branch_str[2000];
    
    float x_root = 500;
    float y_root = 700;
    ofFill();
    ofSetHexColor(0x0cb0b6);
    
    arr_branch_str[1].p_branch = 0;
    arr_branch_str[1].angle = slope;
    arr_branch_str[1].x1 = x_root;
    arr_branch_str[1].y1 = y_root;
    arr_branch_str[1].x2 = x_root-200*sin(slope);
    arr_branch_str[1].y2 = y_root-(100-scale)*cos(slope);
    
    for (int ii =1; ii<=num_bra; ii++){
        arr_branch_str[ii+1].p_branch = (int)(ii+1)/2;
    }
    
    for (int ii =1; ii<=num_bra; ii++){
        if (branch_counter(ii+1)%2==1){
            arr_branch_str[ii+1].angle = arr_branch_str[arr_branch_str[ii+1].p_branch].angle+pi/(4-add_ang);
        } else if (branch_counter(ii+1)%2==0){
            arr_branch_str[ii+1].angle = arr_branch_str[arr_branch_str[ii+1].p_branch].angle-pi/(4-add_ang);
        }
    }

    for (int ii =1; ii<=num_bra; ii++){
        arr_branch_str[ii+1].x1 = arr_branch_str[arr_branch_str[ii+1].p_branch].x2;
        arr_branch_str[ii+1].y1 = arr_branch_str[arr_branch_str[ii+1].p_branch].y2;
        arr_branch_str[ii+1].x2 = arr_branch_str[arr_branch_str[ii+1].p_branch].x2 - branch_length(arr_branch_str[arr_branch_str[ii+1].p_branch].x1,arr_branch_str[arr_branch_str[ii+1].p_branch].y1,arr_branch_str[arr_branch_str[ii+1].p_branch].x2,arr_branch_str[arr_branch_str[ii+1].p_branch].y2)*sin(arr_branch_str[ii+1].angle)*2/3;
        arr_branch_str[ii+1].y2 = arr_branch_str[arr_branch_str[ii+1].p_branch].y2 - branch_length(arr_branch_str[arr_branch_str[ii+1].p_branch].x1,arr_branch_str[arr_branch_str[ii+1].p_branch].y1,arr_branch_str[arr_branch_str[ii+1].p_branch].x2,arr_branch_str[arr_branch_str[ii+1].p_branch].y2)*cos(arr_branch_str[ii+1].angle)*2/3;
    }
    
    //葉の作成
    for (int ii =1; ii<=num_bra; ii++){
        arr_branch_str[ii+1].pl1x = (arr_branch_str[ii+1].x1*2+arr_branch_str[ii+1].x2)/3+branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/9*sin(-pi/4);
        arr_branch_str[ii+1].pl1y = (arr_branch_str[ii+1].y1*2+arr_branch_str[ii+1].y2)/3+branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/9*cos(-pi/4);
        arr_branch_str[ii+1].pl2x = (arr_branch_str[ii+1].x1+arr_branch_str[ii+1].x2)/2+branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/8*sin(-pi/4);
        arr_branch_str[ii+1].pl2y = (arr_branch_str[ii+1].y1+arr_branch_str[ii+1].y2)/2+branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/8*cos(-pi/4);
        arr_branch_str[ii+1].pl3x = (arr_branch_str[ii+1].x1+arr_branch_str[ii+1].x2*3)/4+branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/16*sin(-pi/4);
        arr_branch_str[ii+1].pl3y = (arr_branch_str[ii+1].y1+arr_branch_str[ii+1].y2*3)/4+branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/16*cos(-pi/4);
        
        arr_branch_str[ii+1].pr1x = (arr_branch_str[ii+1].x1*2+arr_branch_str[ii+1].x2)/3-branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/9*sin(-pi/4);
        arr_branch_str[ii+1].pr1y = (arr_branch_str[ii+1].y1*2+arr_branch_str[ii+1].y2)/3-branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/9*cos(-pi/4);
        arr_branch_str[ii+1].pr2x = (arr_branch_str[ii+1].x1+arr_branch_str[ii+1].x2)/2-branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/10*sin(-pi/4);
        arr_branch_str[ii+1].pr2y = (arr_branch_str[ii+1].y1+arr_branch_str[ii+1].y2)/2-branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/10*cos(-pi/4);
        arr_branch_str[ii+1].pr3x = (arr_branch_str[ii+1].x1+arr_branch_str[ii+1].x2*3)/4-branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/14*sin(-pi/4);
        arr_branch_str[ii+1].pr3y = (arr_branch_str[ii+1].y1+arr_branch_str[ii+1].y2*3)/4-branch_length(arr_branch_str[ii+1].x1, arr_branch_str[ii+1].y1, arr_branch_str[ii+1].x2, arr_branch_str[ii+1].y2)/14*cos(-pi/4);
        
    }
    
    for (int ii =1; ii<=num_bra; ii++){
        ofSetColor((int)((float)50*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX));
        ofLine(arr_branch_str[ii].x1,arr_branch_str[ii].y1,arr_branch_str[ii].x2,arr_branch_str[ii].y2);
        ofSetColor((int)((float)50*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX));
    }

    //葉の描画

    for (int ii =2; ii<=num_bra; ii++){
        
        ofSetColor((int)((float)50*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX));
        ofBeginShape();
        ofCurveVertex(arr_branch_str[ii].x1, arr_branch_str[ii].y1);
        ofCurveVertex(arr_branch_str[ii].x1, arr_branch_str[ii].y1);
        ofCurveVertex(arr_branch_str[ii].pl1x, arr_branch_str[ii].pl1y);
        ofCurveVertex(arr_branch_str[ii].pl2x, arr_branch_str[ii].pl2y);
        ofCurveVertex(arr_branch_str[ii].pl3x, arr_branch_str[ii].pl3y);
        ofCurveVertex(arr_branch_str[ii].x2, arr_branch_str[ii].y2);
        ofCurveVertex(arr_branch_str[ii].x2, arr_branch_str[ii].y2);
        ofEndShape();
        ofSetColor((int)((float)50*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX));
        ofBeginShape();
        ofCurveVertex(arr_branch_str[ii].x1, arr_branch_str[ii].y1);
        ofCurveVertex(arr_branch_str[ii].x1, arr_branch_str[ii].y1);
        ofCurveVertex(arr_branch_str[ii].pr1x, arr_branch_str[ii].pr1y);
        ofCurveVertex(arr_branch_str[ii].pr2x, arr_branch_str[ii].pr2y);
        ofCurveVertex(arr_branch_str[ii].pr3x, arr_branch_str[ii].pr3y);
        ofCurveVertex(arr_branch_str[ii].x2, arr_branch_str[ii].y2);
        ofCurveVertex(arr_branch_str[ii].x2, arr_branch_str[ii].y2);
        ofEndShape();
        ofSetColor((int)((float)50*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX));
        
    }
    ofSetColor((int)((float)50*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX),(int)((float)255*rand()/RAND_MAX));
    
    
    //scale = scale-0.005*num_c;
    //num_bra = num_bra+1;
    //add_ang = add_ang+0.0005*num_c;

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
		scale = scale+1;
	}
    
    if (key == 'x'){
		scale = scale-1;
	}
    
    if (key == 'a'){
		num_bra = num_bra+1;
	}
    
    if (key == 'z'){
		num_bra = num_bra-1;
	}
    
    if (key == 'c'){
		num_bra = 0;
	}
    
    if (key == 'o'){
		add_ang = add_ang+0.1;
	}
    
    if (key == 'p'){
		add_ang = add_ang-0.1;
	}
    
    if (key == 'k'){
		slope = slope+0.01;
	}
    
    if (key == 'l'){
		slope = slope-0.01;
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