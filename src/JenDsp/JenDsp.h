//
//  jenDsp.h
//  jenMax
//
//  Created by Mitchell Nordine on 1/08/13.
//
//

#ifndef __jenMax__jenDsp__
#define __jenMax__jenDsp__

/* Header Includes */

#include "ofMain.h"
#include "ofSoundMixer.h"
#include "ofVolume.h"
#include "InstrumentEditor.h"
#include "DspReverb.h"
#include "DspRedux.h"
#include "DspFBDistortion.h"
#include "DspPhasor.h"

/* Class */

class JenDsp {
    
public:
    
    /* Constructor */
    
    JenDsp(){
        ieVol = 0.5;
    }
    
    /* Functions */
    
    void setup(InstrumentEditor *_instrumentEditor);
    void updateInstrumentEditorChannels();
    
    /* Variables */
    
    
    
    /* temp */
    float 	ieVol = 0.8;
    
    /* Class Instances */
    
    Instrument *instrument;
    Oscillator *oscillator;
    
    InstrumentEditor *ie;
    
    /* DSP Process */
    DspReverb reverb;
    DspRedux  redux;
    DspFBDistortion distortion;
    DspPhasor phasor;
    
    /* Channels */
    ofSoundMixer ieMixer;
    ofSoundMixer soundMixer;
    ofSoundEffectVolume ieVolume;
    
};

#endif /* defined(__jenMax__jenDsp__) */
