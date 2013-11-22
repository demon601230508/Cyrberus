//
//  Frequency.h
//  GenMax
//
//  Created by Mitchell Nordine on 12/11/2013.
//
//

#ifndef __GenMax__Frequency__
#define __GenMax__Frequency__

/* Header Includes */

#include "ofMain.h"
#include "GUI.h"

#define MAX_FREQUENCY 20000.0
#define MAX_FREQUENCY_B 17500.0
#define MIN_FREQUENCY 20.0

#define CYR_HIGHEST_FREQUENCY 20000.0f
#define CYR_LOWEST_FREQUENCY 20.0f

/* Class */

class Frequency {
    
public:
    
    /* Constructors & Destructors */
    
    Frequency(){
        initialise();
    }
    
    ~Frequency(){
        
    }
    
    /* Functions */
    
    void setup(GUI *_gui);
    void initialise();
    void setScaleRatio(double _scaleRatio);
    void setFrequencyRatio(double _frequencyRatio);
    void setFrequencyHz(double _frequencyHz);
    double getScaleRatio();
    double getFrequencyRatio();
    float findDifference(Frequency *frequency);
    
    /* Variable Declaration */
    
    double hz;
    double scaleRatio;
    double frequencyRatio;
    double highestFrequency;
    double lowestFrequency;
    double scaleCurve;
    
    /* Class Instances */
    
    GUI *gui;
    GuiGlobal *guiGlobal;
    
};

#endif /* defined(__GenMax__Frequency__) */
