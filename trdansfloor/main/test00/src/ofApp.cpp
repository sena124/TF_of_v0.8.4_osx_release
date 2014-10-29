#include "ofApp.h"

void ofApp::setup(){
    using namespace std;
    osc::init();
    ofSetFrameRate(config::FPS);
    ofBackground(ofColor::black);
    if(config::DEBUG){
        using namespace config;
        const int debug_window_height = HEIGHT * HEIGHT / DIVIDED_WIDTH / 4;
        ofSetWindowShape(HEIGHT, DIVIDED_WIDTH + debug_window_height);
    }else{
        ofSetWindowShape(config::HEIGHT, config::DIVIDED_WIDTH);
    }
    scene = new TestScene();
    
    
    //Kinect//////////
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();		// opens first available kinect

    
#ifdef USE_TWO_KINECTS
    kinect2.init();
    kinect2.open();
#endif
    
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
    
    nearThreshold = 230;
    farThreshold = 70;
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    // start from the front
    bDrawPointCloud = false;
    
    
    const int DIVIDED_WIDTH = 360;
    const int WIDTH = 4 * DIVIDED_WIDTH;
    const int HEIGHT = 640;
    const int debug_window_height = HEIGHT * HEIGHT / DIVIDED_WIDTH / 4;
    
    
    //Kinect//////////
    
    
    
    
}

void ofApp::update(){
    
    //Kinect//////////
    
    ofBackground(100, 100, 100);
    
    kinect.update();
    
    // there is a new frame and we are connected
    if(kinect.isFrameNew()) {
        
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            
            // or we do it ourselves - show people how they can work with the pixels
            unsigned char * pix = grayImage.getPixels();
            
            int numPixels = grayImage.getWidth() * grayImage.getHeight();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        
        // update the cv images
        grayImage.flagImageChanged();
        
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
        
    }
    
#ifdef USE_TWO_KINECTS
    kinect2.update();
#endif
    
    for (int i=0; i<contourFinder.getSize()-1; i++ ){
        
        vecTmpPointX = contourFinder.getCenterX(0, 0, 640, 360);
        vecTmpPointY = contourFinder.getCenterY(0, 0, 640, 360);
        
        possFromKinect.set(vecTmpPointX[i]/640, vecTmpPointY[i]/360);
        vecPossFromKinect.push_back(possFromKinect);
        
        
        cout << vecTmpPointX[i] << "," << vecTmpPointY[i] << endl;
    }
    
    osc::update(vecPossFromKinect);
    scene->update();
    
    vecPossFromKinect.clear();
    vecTmpPointX.clear();
    vecTmpPointY.clear();
    osc::buffer.clear();
    
    //Kinect//////////
    
    

    
    
}

void ofApp::draw(){
    ofPushMatrix();
    ofPushMatrix();
    ofRotateZ(90);
    ofTranslate(-config::WINDOW_ID * config::DIVIDED_WIDTH, -config::HEIGHT);
    float scale = config::HEIGHT;
    ofScale( scale, scale);
    scene->draw();
    ofPopMatrix();
    if(config::DEBUG){
        {
            ofPushMatrix();
            ofTranslate(0, config::DIVIDED_WIDTH);
            {
                ofPushStyle();
                ofSetColor(ofColor::black);
                ofRect(0, 0, config::HEIGHT, config::DIVIDED_WIDTH);
                ofSetColor(*(new ofColor(255, 255, 255, 60)));
                ofRect(0, 0, config::HEIGHT, config::DIVIDED_WIDTH);
                ofPopStyle();
            }
            {
                ofPushMatrix();
                float scale = config::HEIGHT * config::HEIGHT / config::WIDTH ;
                ofScale( scale, scale);
                scene->draw();
                for(float i = 0; i < 4; i++){
                    ofSetLineWidth(0.02);
                    ofLine(i * config::ASPECT_RATIO / 4, 0,
                           i * config::ASPECT_RATIO / 4, 1);
                    if( i == config::WINDOW_ID ){
                        ofPushStyle();
                        ofSetColor(*(new ofColor(255, 255, 255, 60)));
                        ofRect( i * config::ASPECT_RATIO / 4, 0,
                               config::ASPECT_RATIO / 4, 1);
                        ofPopStyle();
                    }
                }
                ofPopMatrix();
            }
            ofPopMatrix();
        }
    }
    ofPopMatrix();
    
    ofPushStyle();
    ofSetLineWidth(10);
    ofSetColor(255, 255, 255,100);
    ofRect(0,0,config::HEIGHT,config::DIVIDED_WIDTH);
    ofPopStyle();
    
    
    
    
    //Kinect//////////
    
    ofSetColor(255, 255, 255);
    
    if(bDrawPointCloud) {
        easyCam.begin();
        drawPointCloud();
        easyCam.end();
    } else {
    grayImage.draw(0, 0, 640, 360);
    contourFinder.draw(0, 0, 640, 360);
        
#ifdef USE_TWO_KINECTS
    kinect2.draw(420, 320, 400, 300);
#endif
    }
    
    //Kinect//////////
    
}


//Kinect//////////
void ofApp::drawPointCloud() {
    int w = 640;
    int h = 360;
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    int step = 2;
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            if(kinect.getDistanceAt(x, y) > 0) {
                mesh.addColor(kinect.getColorAt(x,y));
                mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
            }
        }
    }
    glPointSize(3);
    ofPushMatrix();
    // the projected points are 'upside down' and 'backwards'
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000); // center the points a bit
    ofEnableDepthTest();
    mesh.drawVertices();
    ofDisableDepthTest();
    ofPopMatrix();
}
void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
#ifdef USE_TWO_KINECTS
    kinect2.close();
#endif
}
//Kinect//////////



// for only debug
void ofApp::keyPressed(int key){
    char key_of_scene = (char) key;
    if ( key_of_scene >= '0' && key_of_scene <= '9' )
        delete scene;
    if (key_of_scene == '0' ){
        scene = new TestScene();
    } else if (key_of_scene == '1' ){
        scene = new BibibiScene();
    } else if (key_of_scene == '2' ){
        //        scene = new CrackScene();
    } else if (key_of_scene == '3' ){
        scene = new MoireScene();
    } else if (key_of_scene == '4' ){
        scene = new OrgelScene();
    } else if (key_of_scene == '5' ){
        //        scene = new SakanaScene();
    } else if (key_of_scene == '6' ){
        scene = new ScratchScene();
    } else if (key_of_scene == '7' ){
        //        scene = new TaraiScene();
    } else if (key_of_scene == '8' ){
        scene = new TileScene();
    } else if (key_of_scene == '9' ){
        //        scene = new DetectorScene();
    } else if (key_of_scene == '>' ){
        farThreshold ++;
        if (farThreshold > 255) farThreshold = 255;
    } else if (key_of_scene == '<' ){
        farThreshold --;
        if (farThreshold < 0) farThreshold = 0;
    }
    
}

void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){ }
