#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mySerial.setup(0, 9600); // update port no and baud rate according to your system.
    curVal = 0.0;
    ofSetLineWidth(4);

    
    wave.allocate(ofGetWidth(), ofGetHeight());
    blurPassOne.allocate(ofGetWidth(), ofGetHeight());
    blurPassTwo.allocate(ofGetWidth(), ofGetHeight());
    
    shaderBlurX.load("blurX");
    shaderBlurY.load("blurY");
    
    bg.loadImage("galBG.jpg");
    bg.resize(ofGetWidth(),ofGetHeight());
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
        
        readVal=ofToFloat(str);
        
        if(readVal<50 && readVal>-50){
            curVal = (curVal+readVal)/2;
        }
        
        printf("\n");
        
    } while (str!="");

    lineRight.clear();
    lineLeft.clear();
    
    float i;
    int j;
    float freq = ((float)(curVal*2)+100)/2;
    
    for(i=0;i<ofGetWidth();i+=10){
        for(j=0;j<ofGetHeight();j++){
            vertYRight = ofGetHeight()/2+(sin(i/freq)*100);
            vertYLeft = ofGetHeight()/2-(sin(i/freq)*100);
            lineRight.addVertex(i+ofGetWidth()/2,vertYRight);
            lineLeft.addVertex(ofGetWidth()/2-i,vertYLeft);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //ofBackground(0,0,0,20);
    
    
    wave.begin();
        ofClear(0,0,0,0);
        ofSetColor(255-(curVal*5),255-(abs(curVal*10)),255+(curVal*5));
        lineRight.draw();
        lineLeft.draw();
    wave.end();
    /*
    blurPassOne.begin();
    ofClear(0,0,0,0);
        shaderBlurX.begin();
            shaderBlurX.setUniform1f("blurAmnt", 0.5);
            wave.draw(0,0);
        shaderBlurX.end();
    blurPassOne.end();

    blurPassTwo.begin();
     ofClear(0,0,0,0);
    
        shaderBlurY.begin();
            shaderBlurY.setUniform1f("blurAmnt", 0.5);
            blurPassOne.draw(0,0);
        shaderBlurY.end();
    blurPassTwo.end();
    */
    bg.draw(0,0);
    
    //blurPassTwo.draw(0,0);
    wave.draw(0,0);
    
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
