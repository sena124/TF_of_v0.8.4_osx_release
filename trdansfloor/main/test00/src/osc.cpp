#include "osc.hpp"
namespace osc {
    
    ofxOscReceiver receiver;
    vector<ofVec2f> buffer;
    
    void init(){
        receiver.setup(config::OSC_RECV_PORT);
    }
    
    void update(vector<ofPoint> vecPossFromKinect){
//        buffer.clear();
//        while(receiver.hasWaitingMessages()){
//            ofxOscMessage msg;
//            receiver.getNextMessage(&msg);
//            ofVec2f pos(msg.getArgAsFloat(0),msg.getArgAsFloat(1));
//            cout << pos << endl;
//            buffer.push_back(pos);
//        }
        copy(vecPossFromKinect.begin(), vecPossFromKinect.end(), back_inserter(buffer) );
    }
    
    vector<ofVec2f> getpos_dummy(){
        static int count = 0;
        const int sec = 10;
        const int step = config::FPS * sec;
        const int max_people = 10;
        count ++;
        int pnum = (count / step) % max_people + 1 ;
        vector<ofVec2f> poss;
        for(int i = 0; i < pnum; i++) {
            ofVec2f pos( config::ASPECT_RATIO * double( count % step ) / step,
                         ( i + 0.5 ) / pnum );
            poss.push_back(pos);
        }
        return poss;
    }
    
    vector<ofVec2f> getpos_dummy2(){
        static int count = 0;
        const int sec = 10;
        const int step = config::FPS * sec;
        const int max_people = 10;
        count ++;
        int pnum = (count / step) % max_people + 1 ;
        vector<ofVec2f> poss;
        for(int i = 0; i < pnum; i++) {
            ofVec2f pos( config::ASPECT_RATIO * double( count % step ) / step + ofRandom(0.01) ,
                        ( i + 0.5 ) / pnum + ofRandom(0.01));
            poss.push_back(pos);
            
            for(int i = 0; i < pnum; i++) {
                ofVec2f pos2( config::ASPECT_RATIO * double( count % step ) / step + ofRandom(0.01) -0.5 ,
                             ( i + 0.5 ) / pnum + ofRandom(0.01));
                poss.push_back(pos2);
            }
        }
        return poss;
    }
    
    vector<ofVec2f> main_getpos(){
        return buffer;
    }
    
    vector<ofVec2f> getpos(bool isDummy){
//        if(isDummy)
//            return getpos_dummy2();
//        else
            return main_getpos();
    }
    
}