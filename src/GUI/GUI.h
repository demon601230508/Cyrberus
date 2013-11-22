//
//  GUI.h
//  jenMax
//
//  Created by Mitchell Nordine on 1/06/13.
//
//

#ifndef __jenMax__GUI__
#define __jenMax__GUI__

#include "ofMain.h"
#include "GuiGlobal.h"
#include "ofxUI.h"

#define GUI_SONG 0
#define GUI_PROBABILITY 1
#define GUI_INSTRUMENTATION 2
#define ENVELOPE_EDITOR 3

#define TAB_BAR_WIDTH 80

class GUI {
    
    public:
    
    
    GUI(){
        sampleRate = 44100.0f;
        bufferSize = 512;
    }
    
    ~GUI(){
        
    }
    
    /* My Functions */
    
    void setup();
    void guiEvent(ofxUIEventArgs &e);
    void exit();
    
    /***** Variable Declaration *****/

    /* JenDAC */
    float sampleRate;
    int bufferSize;

    GuiGlobal guiGlobal;
    ofxUITabBar *guiTabBar;
    
    /***** Class instances *****/
    
    ofxUICanvas *gui;
    
    
};

#endif /* defined(__jenMax__GUI__) */
