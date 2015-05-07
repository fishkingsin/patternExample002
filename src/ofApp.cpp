#include "ofApp.h"
void addPoint(vector<ofVec3f> &pos,vector<ofFloatColor> &color,vector<ofVec3f> &normal,vector<ofVec2f> &tex_coord, ofVec3f a) {
    
    ofVec3f _normal = a.normalize();
    ofFloatColor _color = ofFloatColor::fromHsb(0,0.0,ofRandom(0.5,1.0) , 0.5);
    pos.push_back(a);
    
    color.push_back(_color);
    
    normal.push_back(_normal);
    
    tex_coord.push_back(ofVec2f(0,0));
}
//--------------------------------------------------------------
void addFace(vector<ofVec3f> &pos,vector<ofFloatColor> &color,vector<ofVec3f> &normal,vector<ofVec2f> &tex_coord, ofVec3f a, ofVec3f b, ofVec3f c) {
    
    ofVec3f _normal = ((b - a).cross(c - a)).normalize();
    ofFloatColor _color = ofFloatColor::fromHsb(0,0.0,ofRandom(0.5,1.0));
    pos.push_back(a);
    pos.push_back(b);
    pos.push_back(c);
    
    color.push_back(_color);
    color.push_back(_color);
    color.push_back(_color);
    
    normal.push_back(_normal);
    normal.push_back(_normal);
    normal.push_back(_normal);
    
    tex_coord.push_back(ofVec2f(0,0));
    tex_coord.push_back(ofVec2f(1,1));
    tex_coord.push_back(ofVec2f(0,1));
}

//--------------------------------------------------------------
void addFace(vector<ofVec3f> &pos,vector<ofFloatColor> &color,vector<ofVec3f> &normal,vector<ofVec2f> &tex_coord, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d , bool revert) {
    
    float offset_value = 0;
    
    if(revert)
    {
        ofVec3f offset(offset_value,offset_value,0);
        addFace(pos,color,normal, tex_coord, a+offset, b+offset, c+offset);
        addFace(pos,color,normal, tex_coord, a-offset, c-offset, d-offset);
    }
    else{
        ofVec3f offset(-offset_value,offset_value,0);
        addFace(pos,color,normal, tex_coord, a-offset, b-offset, c-offset);
        addFace(pos,color,normal, tex_coord, a+offset, c+offset, d+offset);
    }
}
//--------------------------------------------------------------
ofVec3f calcSphereVec(float r ,float s , float R_Norm ,float S_Norm ,float radius)
{
    
    ofVec3f v;
    v.y = sin( -M_PI_2 + M_PI * r * R_Norm ) * radius;
    v.x = cos(2*M_PI * s * S_Norm) * sin( M_PI * r * R_Norm ) * radius;
    v.z = sin(2*M_PI * s * S_Norm) * sin( M_PI * r * R_Norm ) * radius;
    return v;
    
}
void createSphere( vector<ofVec3f> &pos,vector<ofFloatColor> &color,vector<ofVec3f> &normal,vector<ofVec2f> &tex_coord, float radius, unsigned int rings, unsigned int sectors)
{
    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;
    
    for(r = 0; r < rings; r++)
    {
        for(s = 0; s < sectors; s++)
        {
            ofVec3f nw = calcSphereVec(r,s,R,S,radius);
            ofVec3f ne = calcSphereVec(r+1,s,R,S,radius);
            ofVec3f sw = calcSphereVec(r,s+1,R,S,radius);
            ofVec3f se = calcSphereVec(r+1,s+1,R,S,radius);
            addFace(pos,color,normal,tex_coord, nw,ne,se,sw,false);
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    center.set(0,0);
    total = 0;
    createSphere(pos, color, normal, tex_coord , ofGetWidth(), 64 , 64);
    total = pos.size();
    
    vboMesh.setVertexData(pos.data(), total, GL_DYNAMIC_DRAW);
    
    vboMesh.setColorData(color.data(), total, GL_DYNAMIC_DRAW);
    vboMesh.setNormalData(normal.data(), total, GL_DYNAMIC_DRAW);
    vboMesh.setTexCoordData(tex_coord.data(), total, GL_DYNAMIC_DRAW);
    vert = pos;
    
    cam.setVFlip(true);
    current = 0;
    gui.setup();
    gui.add(drawMode.set("GL_DRAW_MODE", GL_POINTS, GL_POINTS, GL_POLYGON));
    gui.add(drawModeString.set("GL_POINTS"));
    drawMode.addListener(this, &ofApp::drawModeChanged);
    gui.loadFromFile("settings.xml");
}
//--------------------------------------------------------------
void ofApp::update(){
    float noise_density = 0.001;
    float wave_density = 0.001;
    float feq = 0.001;
    float t = ofGetElapsedTimef()*feq;
    float pow = 10;

    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofEnableAlphaBlending();
    glPushAttrib(GL_ENABLE_BIT);
    
    // setup gl state
    glEnable(GL_DEPTH_TEST);
    cam.begin();
    vboMesh.bind();
    vboMesh.updateVertexData(pos.data(), total);
    vboMesh.updateColorData(color.data(), total);
    vboMesh.updateNormalData(normal.data(), total);
    
    vboMesh.draw(drawMode , 0,total);
    vboMesh.unbind();
    cam.end();
    glDisable(GL_DEPTH_TEST);
    glPopAttrib();
    
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key)
    {
            case 'f':
            ofToggleFullscreen();
            break;
    }

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

void ofApp::drawModeChanged(GLint &drawMode)
{
    switch (drawMode) {
        case GL_POINTS:
            drawModeString = "GL_POINTS";
            break;
        case GL_LINES :
            drawModeString = "GL_LINES";
            break;
        case GL_LINE_LOOP :
            drawModeString = "GL_LINE_LOOP";
            break;
        case GL_LINE_STRIP :
            drawModeString = "GL_LINE_STRIP";
            break;
        case GL_TRIANGLES :
            drawModeString = "GL_TRIANGLES";
            break;
        case GL_TRIANGLE_STRIP :
            drawModeString = "GL_TRIANGLE_STRIP";
            break;
        case GL_TRIANGLE_FAN :
            drawModeString = "GL_TRIANGLE_FAN";
            break;
        case GL_QUADS :
            drawModeString = "GL_QUADS";
            break;
        case GL_QUAD_STRIP :
            drawModeString = "GL_QUAD_STRIP";
            break;
        case GL_POLYGON :
            drawModeString = "GL_POLYGON";
            break;
        default:
            break;
    }
}