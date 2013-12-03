//
//  DspPhasor.h
//  Cyrberus
//
//  Created by Joshua Batty on 25/11/13.
//
//

#ifndef __Cyrberus__DspPhasor__
#define __Cyrberus__DspPhasor__

/* Header Includes */

#include "ofMain.h"
#include "ofSoundEffect.h"
#include "ofxDSP.h"

/* Class */

class DspPhasor: public ofSoundEffect{
    
public:
    
    /* Constructor */
    
    DspPhasor(){
        setup();
    }
    
    /* Functions */
    void setRange( float fMin, float fMax );
    void setRate( float rate );
    void setFeedback( float fb );
    void setDepth( float depth );
    float update( float inSamp );
    
    void setup();
    void setThreshold(float _value);
    
    void process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels );
    
    /// Return our name
	string getName() { return "ofSoundEffectVolume"; }
	void setSampleRate ( int rate ){};
    
    /* Variables */
    float fMin, fMax;
    float rate;
    float feedback;
    float depth;
    
    
    /* temp */
    
    /* Class Instances */
    ofxPhasor phasor;
    
};

#endif /* defined(__Cyrberus__DspPhasor__) */