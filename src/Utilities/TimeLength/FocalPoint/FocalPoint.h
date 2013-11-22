//
//  FocalPoint.h
//  GenMax
//
//  Created by Mitchell Nordine on 4/11/2013.
//
//

#ifndef __GenMax__FocalPoint__
#define __GenMax__FocalPoint__

/* Header Includes */

#include "ofMain.h"
#include "GUI.h"

/* Class */

class FocalPoint {
    
public:
    
    /* Constructors & Destructors */
    
    FocalPoint(){
        
    }
    
    ~FocalPoint(){
        
    }
    
    /* Functions */
    
    void setup(GUI *_gui);
    void setup(GUI *_gui, float _position);
    void setup(GUI *_gui, vector<float> _positions);
    void initialise();
    float setPosition(float _position);
    float addPosition(float _position);
    vector<float> addPositions(vector<float> _positions);
    
    /* Variable Declaration */
    
    vector<float> positions;
    
    /* Class Instances */
    
    GUI *gui;
    GuiGlobal *guiGlobal;
    
};

#endif /* defined(__GenMax__FocalPoint__) */
