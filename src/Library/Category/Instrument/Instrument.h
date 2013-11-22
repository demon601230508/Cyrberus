//
//  Instrument.h
//  jenMax
//
//  Created by Mitchell Nordine on 24/07/13.
//
//

#ifndef __jenMax__Instrument__
#define __jenMax__Instrument__

/* Inheritance */

#include "ofMain.h"
#include "Oscillator.h"
#include "Frequency.h"

#define TWO_THOUSAND_HERTZ 0.1

/* Class */

class Instrument {
    
public:
    
    /* Pointers */
    
    Instrument(){
        initialise();
    }
    
    ~Instrument(){
        
    }
    
    /* Functions */
    
    void setup(GUI *_gui);
    void initialise();
    void addOscillator();
    void removeOscillator();
    void removeOscillator(int i);
    
    /* Analysis Functions */
    
    double getNormaliser();
    void analyseInstrument();
    double getSampleLoudness(double ratio);
    double getSampleNoiseyness(double ratio);
    double getSampleMeanFrequency(double ratio);
    double getAmplitudeAtSample(int sample);
    double getAmplitudeAtRatio(double ratio);
    double getAutoMixer();
    float compareToInstrument(Instrument *instrument);
    
    void play();
    
    void printAnalysisData();
    
    /* Variable Declaration */
    
    string name;
    int numOfOscillators;
    float intensity;
    float difference;           /* Used for overall instrument comparison and
                                 selection. */
    double normaliser;           /* When multiplied by inst amp, highest point
                                 == 1.0. */
    double loudness;            /* Used to rate the "Perceived Loudness". */
    Frequency meanFrequency;    /* Average Frequency */
    double noiseyness;          /* Rates the perceived "noiseyness" of the
                                 instrument. */
    double relativeLoudness;    /* relative to current inst selection */
    double relativeNoiseyness;
    
    TimeLength duration;
    vector<Oscillator> oscillators;
    
    /* Class Instances */
    
    GUI *gui;
    GuiGlobal *guiGlobal;
    
private:
    
    double previousRatio;
    
};


#endif /* defined(__jenMax__Instrument__) */
