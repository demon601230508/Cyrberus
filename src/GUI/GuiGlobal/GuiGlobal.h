//
//  GuiGlobal.h
//  Cyrberus
//
//  Created by Mitchell Nordine on 22/11/2013.
//
//

#ifndef __Cyrberus__GuiGlobal__
#define __Cyrberus__GuiGlobal__

/* Header Includes */

#include "ofMain.h"
#include "ofxUI.h"

#define CYR_TEMPO 120.0f
#define CYR_NUM_OF_SUB_DIVISIONS 4
#define CYR_SUB_DIVISIONS 4
#define CYR_SAMPLE_RATE 44100
#define CYR_BUFFER_SIZE 512
#define TAB_BAR_WIDTH 80

/* Class */

class GuiGlobal {
    
public:
    
    /* Constructors & Destructors */
    
    GuiGlobal(){
        timeSig.first = CYR_NUM_OF_SUB_DIVISIONS;
        timeSig.second = CYR_SUB_DIVISIONS;
        bufferSize = CYR_BUFFER_SIZE;
        sampleRate = CYR_SAMPLE_RATE;
        tempo = CYR_TEMPO;
    }
    
    ~GuiGlobal(){
        
    }
    
    /* Functions */
    
    GuiGlobal* setup();
    void addWidgets();
    void addListeners(ofxUIEventArgs &e);
    
    /* Variable Declaration */
    
    float tempo;
    pair<int, int> timeSig;
    int bufferSize;
    int sampleRate;
    
    ofxUISuperCanvas* superCanvas;
    
    /* Class Instances */
    
    
    
};

#endif /* defined(__Cyrberus__GuiGlobal__) */
