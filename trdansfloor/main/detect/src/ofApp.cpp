#include "ofApp.h"

void ofApp::setup(){
    gui.setup();
    gui.add(cam_id.setup("select kinect", true));
    gui.add(window_id.setup("window id",   0,     0,  3));
    gui.add(near.setup("near",             255,   0,  255));
    gui.add(far.setup("far",               0,     0,  255));
    gui.add(min_radius.setup("min_radius", 2000, 50,  8000));
    gui.add(max_radius.setup("max_radius", 4500, 50,  8000));
    gui.add(angle.setup("kinect angle",  0,     -30,  30));
    gui.add(thresh.setup("contour thresh", 255,   0,  255));
    gui.add(split.setup("split",           65,    5,  100));
    
    k.listDevices();
    k.init();
    k.open(k.nextAvailableId());
    
    kimage.allocate(k.width, k.height, OF_IMAGE_COLOR);
    dimage.allocate(k.width, k.height, OF_IMAGE_GRAYSCALE);
    fimage.allocate(k.width, k.height, OF_IMAGE_GRAYSCALE);
    
    ofSetWindowShape(3 * k.width / 2, k.height / 2);
    cout << "kinect.width, kinect.height: " << k.width << "," << k.height << endl;
}

void ofApp::update(){
    if( int(cam_id) != k.getDeviceId() ){
        k.close();
        k.open(int(cam_id));
    }
    
    k.update();
    if(k.isFrameNew()){
        kimage.setFromPixels(k.getPixels(), k.width, k.height, OF_IMAGE_COLOR);
        dimage.setFromPixels(k.getDepthPixels(), k.width, k.height, OF_IMAGE_GRAYSCALE);
        unsigned char * pix = dimage.getPixels();
        int numPixels = dimage.getWidth() * dimage.getHeight();
        for(int i = 0; i < numPixels; i++)
            pix[i] = (pix[i] < near && pix[i] > far)? 255: 0;
        for(int i = 0; i < numPixels; i++)
            if((i / k.width % split == 0) || (i % k.width % split == 0) )
                pix[i] = 0;
                
        fimage.setFromPixels(pix, k.width,k.height, OF_IMAGE_GRAYSCALE);
        ofxCvGrayscaleImage gray;
        gray.allocate(k.width, k.height);
        gray.setFromPixels(fimage.getPixels(), k.width, k.height);
        cntr.findContours(gray, min_radius, max_radius, 24, true, true);
    }
    k.setCameraTiltAngle(angle);
    
    ofxOscSender sender;
    sender.setup(TARGET_IP, OSC_SEND_PORT_OFFSET + window_id);
    for(int i = 0; i < cntr.nBlobs; i++){
        ofxCvBlob blob =  cntr.blobs.at(i);
        ofPoint pos = blob.boundingRect.getCenter();
        ofxOscMessage msg;
        msg.setAddress("/pos");
        float ratio = float(k.width) / k.height;
        msg.addFloatArg((float(pos.y) / k.height + window_id) / ratio);
        msg.addFloatArg(float(k.width - pos.x) / k.width);
        sender.sendMessage(msg);
    }
}

void ofApp::draw(){
    ofPushMatrix();
    {
        ofScale(.5, .5);
//        ofRotateZ(90);
//        ofTranslate(0, -1 * k.height);
        kimage.draw(0,           0,     k.width, k.height);
        dimage.draw(k.width,     0,     k.width, k.height);
        fimage.draw(2 * k.width, 0,     k.width, k.height);
        ofPushStyle();
        ofPushMatrix();
        {
            ofSetColor(255, 0, 0, 100);
            ofTranslate(2 * k.width, 0);
            for(int i = 0 ; i < cntr.nBlobs; i++){
                ofxCvBlob blob =  cntr.blobs.at(i);
                ofCircle(blob.boundingRect.getCenter(), 5);
            }
        }
        ofPopMatrix();
        ofPopStyle();
        cntr.draw(2 * k.width, 0, k.width, k.height);
    }
    ofPopMatrix();
    gui.draw();
}

void ofApp::keyPressed(int key){
}
void ofApp::keyReleased(int key){
}
void ofApp::mouseMoved(int x, int y ){
}
void ofApp::mouseDragged(int x, int y, int button) {
    cout << "x,y:" << x << "," << y << endl;
    cout << float(x) / k.width << "," << float(y) / k.height << endl;
    ofxOscMessage msg;
}
void ofApp::mousePressed(int x, int y, int button){
}
void ofApp::mouseReleased(int x, int y, int button){
}
void ofApp::windowResized(int w, int h){
}
void ofApp::gotMessage(ofMessage msg){
}
void ofApp::dragEvent(ofDragInfo dragInfo){ 
}
