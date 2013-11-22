//
//  Oscillator.cpp
//  jenMax
//
//  Created by Mitchell Nordine on 2/08/13.
//
//

#include "Oscillator.h"

//--------------------------------------------------------------------------------//
// OSCILLATOR SETUP
//--------------------------------------------------------------------------------//

void Oscillator::setup(GUI *_gui, TimeLength *_duration, double *_normaliser)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    duration = _duration;
    normaliser = _normaliser;
    
    return;
    
}

void Oscillator::setup(GUI *_gui, TimeLength *_duration,
                       double *_normaliser, int _waveform)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    duration = _duration;
    normaliser = _normaliser;
    
    waveform = _waveform;
    getWaveformString();
    
    return;
    
}

void Oscillator::setup(GUI *_gui, TimeLength *_duration,
                       double *_normaliser, string _waveform)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    duration = _duration;
    normaliser = _normaliser;
    
    waveformStr = _waveform;
    getWaveformInt(_waveform);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET WAVEFORM INTEGER FROM STRING
//--------------------------------------------------------------------------------//

int Oscillator::getWaveformInt(string _waveform)
{

    waveformStr = _waveform;
    
    if (_waveform == "SINE") {
        waveform = JEN_SINE;
    }
    else if (_waveform == "SAW") {
        waveform = JEN_SAW;
    }
    else if (_waveform == "SQUARE") {
        waveform = JEN_SQUARE;
    }
    else if (_waveform == "NOISE") {
        waveform = JEN_NOISE;
    }
    else if (_waveform == "NOISE_WALK") {
        waveform = JEN_NOISE_WALK;
    }
    else if (_waveform == "GAUSSIAN") {
        waveform = JEN_GAUSSIAN;
    }
    else { waveform = JEN_SINE; }
    
    return waveform;
    
}

//--------------------------------------------------------------------------------//
// GET WAVEFORM IN STRING FORM
//--------------------------------------------------------------------------------//

string Oscillator::getWaveformString(int _waveform)
{
    
    waveform = _waveform;
    
    if (_waveform == JEN_SINE) {
        waveformStr = "SINE";
    }
    else if (_waveform == JEN_SAW) {
        waveformStr = "SAW";
    }
    else if (_waveform == JEN_SQUARE) {
        waveformStr = "SQUARE";
    }
    else if (_waveform == JEN_NOISE) {
        waveformStr = "NOISE";
    }
    else if (_waveform == JEN_NOISE_WALK) {
        waveformStr = "NOISE_WALK";
    }
    else if (_waveform == JEN_GAUSSIAN) {
        waveformStr = "GAUSSIAN";
    }
    else { waveformStr = "SINE"; }
    
    return waveformStr;
    
}

string Oscillator::getWaveformString()
{
    
    if (waveform == JEN_SINE) {
        waveformStr = "SINE";
    }
    else if (waveform == JEN_SAW) {
        waveformStr = "SAW";
    }
    else if (waveform == JEN_SQUARE) {
        waveformStr = "SQUARE";
    }
    else if (waveform == JEN_NOISE) {
        waveformStr = "NOISE";
    }
    else if (waveform == JEN_NOISE_WALK) {
        waveformStr = "NOISE_WALK";
    }
    else if (waveform == JEN_GAUSSIAN) {
        waveformStr = "GAUSSIAN";
    }
    else { waveformStr = "SINE"; }
    
    return waveformStr;
    
}

//--------------------------------------------------------------------------------//
// INITIALISE OSCILLATOR
//--------------------------------------------------------------------------------//

void Oscillator::initialiseOscillator()
{
    
    amplitude.points.clear();
    frequency.points.clear();
    
    amplitude.addPoint(0.0f, 0.0f, 0.0f);
    amplitude.addPoint(1.0f, 0.0f, 0.0f);
    
    frequency.addPoint(0.0f, 0.0f, 0.0f);
    frequency.addPoint(1.0f, 0.0f, 0.0f);
    
    return;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
// GET AMPLITUDE AT SAMPLE
//--------------------------------------------------------------------------------//

double Oscillator::getAmplitudeAtSample(int sample)
{
    
    double ratio = sample / duration->getSamples();
    
    return getAmplitudeAtRatio(ratio);
    
}

//--------------------------------------------------------------------------------//
// GET AMPLITUDE AT RATIO
//--------------------------------------------------------------------------------//

double Oscillator::getAmplitudeAtRatio(double ratio)
{
    
    double value = 0.0;
    
    /* Initialise phase if at start of ratio */
    if (ratio == 0) {
        phase = 0.0;
    }
    
    /* Pass phrase into algebraic (to return waveform later) */
    algebraic.setup(phase);
    
    /* Get value for phase */
    value = algebraic.getWaveformValue(waveform);
    
    /* Multiply signal by amplitude envelope */
    value *= amplitude.getValue(ratio);
    
    /* Set frequency to determine advancePerSample */
    setFrequency(getFrequencyAtRatio(ratio));
    
    /* Advance phase according to frequency */
    updatePhase();
    
    return value;
    
}

//--------------------------------------------------------------------------------//
// GET FREQUENCY AT RATIO
//--------------------------------------------------------------------------------//

double Oscillator::getFrequencyAtRatio(double ratio)
{
    
    if (waveform == JEN_GAUSSIAN) {
        double gaussianFrequency;
        gaussianFrequency = frequency.getValue(ratio);
        gaussianFrequency = gaussianFrequency * JenGaussianAlt(gaussianFrequency
        * gaussianFrequency, 1.0) * MAX_FREQUENCY_B - MIN_FREQUENCY + MIN_FREQUENCY;
        return gaussianFrequency;
    }
    else { }
    
    return frequency.getValue(ratio)* MAX_FREQUENCY - MIN_FREQUENCY + MIN_FREQUENCY;
    
}

//--------------------------------------------------------------------------------//
// SET FREQUENCY
//--------------------------------------------------------------------------------//

void Oscillator::setFrequency(double _freq)
{
    
    freq = _freq;
    
    if (waveform == JEN_SINE ||
        waveform == JEN_NOISE_WALK ||
        waveform == JEN_SQUARE ||
        waveform == JEN_SAW ||
        waveform == JEN_NOISE) {
        advancePerSample = ( 1.0 / guiGlobal->sampleRate ) * freq;
    }
    else if (waveform == JEN_GAUSSIAN) {
        freq = JenGaussianAlt(freq, 0.5);
        advancePerSample = ( 1.0 / guiGlobal->sampleRate ) * freq;
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// UPDATE PHASE
//--------------------------------------------------------------------------------//

void Oscillator::updatePhase()
{
    
    if (waveform == JEN_SINE ||
        waveform == JEN_NOISE_WALK ||
        waveform == JEN_SQUARE ||
        waveform == JEN_GAUSSIAN) {
        phase += advancePerSample;
    }
    else if (waveform == JEN_SAW ||
             waveform == JEN_NOISE) {
        phase += advancePerSample;
        phase = remainder(phase, 2.0f);
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// PLAY SOUND
//--------------------------------------------------------------------------------//
/* Trigger the sound for audio playback */

void Oscillator::play()
{
    
    isPlaying = false;
    sampleCount = 0;
    sampleDuration = duration->getSamples();;
    isPlaying = true;
    
    return;
    
}

//--------------------------------------------------------------------------------//
// AUDIO OUTPUT
//--------------------------------------------------------------------------------//

void Oscillator::audioRequested(float* output,int numFrames,int numChannels)
{
	
    double ratio, value;
    int i, j;
    
    /* i counts through each sample up to size of buffer */
    for ( i=0; i<numFrames; i++ ) {
        
        /* Check for "isPlaying" trigger and count through duration of sound */
        if ((isPlaying==true) && (sampleCount < sampleDuration)) {
            
            /* Determine ratio to determine envelope position to find */
            ratio = (double)sampleCount/(double)sampleDuration;
            
            /* Calculates each sample of waveform for oscillator */
            value = getAmplitudeAtRatio(ratio) * *normaliser;
            
        }
        
        /* Else if "isPlaying" trigger is not true, then remain silent */
        else {value = 0;}
        
        /* Copy value to all the channels */
        for ( j=0; j<numChannels; j++ ) {
            output[i*numChannels+j] = value;
        }
        
        /* Count through each sample */
        sampleCount++;
        
        /* When duration is reached, reset trigger and sample count */
        if (sampleCount >= sampleDuration) {
            isPlaying = false;
            sampleCount = 0;
        }
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//