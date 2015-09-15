#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mySerial.setup(0, 9600); // update port no and baud rate according to your system.
    curVal = 0;
    ofSetLineWidth(2);
    lastVal=0;
    dVal=0;
}

// trim trailing spaces

string ofxTrimStringRight(string str) {
    
    size_t endpos = str.find_last_not_of(" \t\r\n");
    
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
    
}

// trim trailing spaces

string ofxTrimStringLeft(string str) {
    
    size_t startpos = str.find_first_not_of(" \t\r\n");
    
    return (string::npos != startpos) ? str.substr(startpos) : str;
    
}



string ofxTrimString(string str) {
    
    return ofxTrimStringLeft(ofxTrimStringRight(str));;
    
}

string ofxGetSerialString(ofSerial &serial, char until) {
    
    static string str;
    
    stringstream ss;
    
    char ch;
    
    int ttl=1000;
    //&& ttl->0
    while ((ch=serial.readByte())>0 && ch!=until) {
        
        ss << ch;
        
    }
    
    str+=ss.str();
    
    if (ch==until) {
        
        string tmp=str;
        
        str="";
        
        return ofxTrimString(tmp);
        
    } else {
        
        return "";
        
    }
    
}



//--------------------------------------------------------------
void ofApp::update(){
    // Receive String from Arduino
    
    string str;
    
    do {
        
        str = ofxGetSerialString(mySerial,'\n'); //read until end of line
        
        if (str=="") continue;
        
        
        
        for(int i = 0; i < str.length(); i++) {
            printf("%c",str[i]);
        }
        
        curVal = ofToInt(str);
        
        printf("\n");
        
        
        
    } while (str!="");
    
    dVal=curVal-lastVal;

    lineRight.clear();
    lineLeft.clear();
    
    float i;
    int j;
    float freq = ((float)(dVal*2)+100)/2;
    
    for(i=0;i<ofGetWidth();i+=2){
        for(j=0;j<ofGetHeight();j++){
            vertYRight = 200+(sin(i/freq)*100);
            vertYLeft = 200-(sin(i/freq)*100);
            lineRight.addVertex(i+ofGetWidth()/2,vertYRight);
            lineLeft.addVertex(ofGetWidth()/2-i,vertYLeft);
        }
    }
    lastVal=curVal;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(128);
    ofSetColor(255-(dVal*5),255-(abs(dVal*10)),255+(dVal*5));
    
    lineRight.draw();
    lineLeft.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
