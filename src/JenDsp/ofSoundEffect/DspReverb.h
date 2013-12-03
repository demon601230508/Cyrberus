//
//  DspReverb.h
//  Cyrberus
//
//  Created by Joshua Batty on 23/11/13.
//
//

#ifndef __Cyrberus__DspReverb__
#define __Cyrberus__DspReverb__

/* Header Includes */

#include "ofMain.h"
#include "ofSoundEffect.h"
#include "ofxDSP.h"

/* Class */

class DspReverb : public ofSoundEffect{
    
public:
    
    /* Constructor */
    
    DspReverb(){
        wetness				= 0.94f;
        verbRoomSize		= 0.92f;
        verbDamp			= 0.1f;
        verbWidth			= 0.199f;
        numsamples          = 1;
        skip                = 1;
        setup();
    }
    
    /* Functions */
    void setup();
    void setRoomSize(float _value);
    void setDamping(float _value);
    void setWidth(float _value);
    void setWet(float _value);
    void setDry(float _value);
    void process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels );
    
    /// Return our name
	string getName() { return "ofSoundEffectVolume"; }
	void setSampleRate ( int rate ){};
    
    /* Variables */
    float wetness;
    float verbRoomSize;
    float verbDamp;
    float verbWidth;
    long numsamples;
    int skip;
    
    /* temp */
    
    /* Class Instances */
    ofxReverb reverb;
    
};

#endif /* defined(__Cyrberus__DspReverb__) */