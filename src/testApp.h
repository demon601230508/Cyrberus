#pragma once

#include "ofMain.h"
#include "GUI.h"
#include "InstrumentEditor.h"
#include "Library.h"
#include "JenDsp.h"

class testApp : public ofBaseApp{

public:
    
    /* Functions */
    
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
    
    void audioOut(float *output, int bufferSize, int nChannels);
    
    /* Variables */
    
    string libraryFilePath = "Library.xml";
    
    /* Classes */
    
    GUI gui;
    Library library;
    InstrumentEditor instrumentEditor;
    JenDsp jenDsp;
    ofSoundStream soundStream;
		
};
