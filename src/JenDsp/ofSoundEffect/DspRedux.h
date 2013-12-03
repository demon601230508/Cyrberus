//
//  DspRedux.h
//  Cyrberus
//
//  Created by Joshua Batty on 25/11/13.
//
//

#ifndef __Cyrberus__DspRedux__
#define __Cyrberus__DspRedux__

/* Header Includes */

#include "ofMain.h"
#include "ofSoundEffect.h"
#include "ofxDSP.h"

/* Class */

class DspRedux : public ofSoundEffect{
    
public:
    
    /* Constructor */
    
    DspRedux(){
        rate				= .10f;
        bits                = 32;
        setup();
    }
    
    /* Functions */
    void setup();
    void setBits(float _value);
    void setRate(float _value);

    void process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels );
    
    /// Return our name
	string getName() { return "ofSoundEffectVolume"; }
	void setSampleRate ( int rate ){};
    
    /* Variables */
    int   bits;
    float rate;

    
    /* temp */
    
    /* Class Instances */
    ofxCrush redux;
    
};

#endif /* defined(__Cyrberus__DspRedux__) */