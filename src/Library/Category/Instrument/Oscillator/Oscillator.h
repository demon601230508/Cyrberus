//
//  Oscillator.h
//  jenMax
//
//  Created by Mitchell Nordine on 2/08/13.
//
//

#ifndef __jenMax__Oscillator__
#define __jenMax__Oscillator__

/* Header Includes */

#include "ofMain.h"
#include "Utilities.h"
#include "TimeLength.h"
#include "ofSoundEffect.h"

#define JEN_SINE 0
#define JEN_SAW 1
#define JEN_SQUARE 2
#define JEN_NOISE 3
#define JEN_NOISE_WALK 4
#define JEN_GAUSSIAN 5

#define MAX_FREQUENCY 20000.0
#define MAX_FREQUENCY_B 17500.0
#define MIN_FREQUENCY 20.0

/* Class */

class Oscillator: public ofSoundSource {
    
public:
    
    /* Pointers */
    
    Oscillator(){
        waveform = JEN_SINE;
        phase = 0.0;
        sampleCount = 0;
        isPlaying = false;
        sampleDuration = 0;
        normaliser = NULL;
    }
    
    ~Oscillator(){
        
    }
    
    /* Functions */
    
    string getName() { return "Oscillator"; }
    
    void setup(GUI *_gui, TimeLength *_duration, double *_normaliser);
    void setup(GUI *_gui, TimeLength *_duration,
               double *_normaliser, string _waveform);
    void setup(GUI *_gui, TimeLength *_duration,
               double *_normaliser, int _waveform);
    int getWaveformInt(string _waveform);
    string getWaveformString();
    string getWaveformString(int _waveform);
    void initialiseOscillator();
    
    double getAmplitudeAtSample(int sample);
    double getAmplitudeAtRatio(double ratio);
    double getFrequencyAtRatio(double ratio);
    void setFrequency(double _freq);
    void updatePhase();
    
    void play();
    void setSampleRate(int rate){}; // Here for virtual void...
    void audioRequested( float* output, int numFrames, int numChannels );
    
    /* Variable Declaration */
    
    int waveform;
    double *normaliser;
    double *autoMixer;
    string waveformStr;
    Envelope amplitude;
    Envelope frequency;
    
    bool isPlaying;
    int sampleCount;
    int sampleDuration;
    
    /* Class Instances */
    
    GUI *gui;
    GuiGlobal *guiGlobal;
    TimeLength *duration;
    
private:
    
    double freq;
    double phase;
    double advancePerSample;
    Algebraic algebraic;
    
};

#endif /* defined(__jenMax__Oscillator__) */
