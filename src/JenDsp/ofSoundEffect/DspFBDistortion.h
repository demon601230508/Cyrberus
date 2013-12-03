//
//  DspFBDistortion.h
//  Cyrberus
//
//  Created by Joshua Batty on 25/11/13.
//
//

#ifndef __Cyrberus__DspFBDistortion__
#define __Cyrberus__DspFBDistortion__


/* Header Includes */

#include "ofMain.h"
#include "ofSoundEffect.h"
#include "ofxDSP.h"

/* Class */

class DspFBDistortion : public ofSoundEffect{
    
public:
    
    /* Constructor */
    
    DspFBDistortion(){
        threshold	= .02f;
        setup();
    }
    
    /* Functions */
    void setup();
    void setThreshold(float _value);
    
    void process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels );
    
    /// Return our name
	string getName() { return "ofSoundEffectVolume"; }
	void setSampleRate ( int rate ){};
    
    /* Variables */
    float threshold;
    
    
    /* temp */
    
    /* Class Instances */
    ofxFoldBackDistortion distortion;
    
};

#endif /* defined(__Cyrberus__DspFBDistortion__) */