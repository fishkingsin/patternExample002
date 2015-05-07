#pragma once

#include "ofMain.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofVbo vboMesh;
    vector<ofVec3f> pos;
    vector<ofVec3f> vert;
    vector<ofVec3f> point;
    vector<ofVec3f> normal;
    vector<ofFloatColor> color;
    vector<ofVec2f> tex_coord;
    ofVec3f center;
    int total;
    int WIDTH;
    int HEIGHT;
    int space;
    ofEasyCam cam;
    float current;
    
    ofxPanel gui;
    ofParameter<GLint> drawMode;
    ofParameter<string> drawModeString;
    void drawModeChanged(GLint &drawMode);
};
