//
//  Instrument.cpp
//  jenMax
//
//  Created by Mitchell Nordine on 24/07/13.
//
//

#include "Instrument.h"

//--------------------------------------------------------------------------------//
// INSTRUMENT SETUP
//--------------------------------------------------------------------------------//

void Instrument::setup(GUI *_gui)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    duration.setup(gui);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// INITIALISE INSTRUMENT CONTENTS
//--------------------------------------------------------------------------------//

void Instrument::initialise()
{
    
    name = "";
    
    numOfOscillators = 0;
    
    intensity = 0.0f;
    difference = 0.0f;
    
    normaliser = 1.0;
    
    loudness = 0.0;
    noiseyness = 0.0;
    relativeLoudness = 0.0;
    relativeNoiseyness = 0.0;
    
    oscillators.clear();
    
    duration.initialise();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD OSCILLATOR
//--------------------------------------------------------------------------------//

void Instrument::addOscillator()
{
    
    Oscillator *newOscillator = new Oscillator;
    
    newOscillator->initialiseOscillator();
    
    newOscillator->setup(gui, &duration, &normaliser, JEN_SINE);
    
    oscillators.push_back(*newOscillator);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// REMOVE OSCILLATOR
//--------------------------------------------------------------------------------//
/* Remove oscillator from end */
void Instrument::removeOscillator()
{
    
    oscillators.erase(oscillators.end());
    
    return;
    
}

/* Remove oscillator at position "i" in oscillator vector */
void Instrument::removeOscillator(int i)
{
    
    oscillators.erase(oscillators.begin()+i);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET NORMALISER
//--------------------------------------------------------------------------------//

double Instrument::getNormaliser()
{
    
    double ratio = 0.0;
    double amplitude = 0.0;
    double highestAmplitude = 0.0;
    
    /* Walk through each sample */
    for (int i=0; i < duration.getSamples(); i++) {
        
        /* Determine ratio of position within duration of instrument */
        ratio = (double)i / (double)duration.getSamples();
        
        /* Determine absolute amplitude at sample */
        amplitude = abs(getAmplitudeAtRatio(ratio));
        
        /* Find highest amplitude */
        if (amplitude > highestAmplitude) {
            highestAmplitude = amplitude;
        }
        
    }
    
    if (highestAmplitude <= 0.0) {
        normaliser = 1.0;
    }
    else{
        normaliser = 1.0 / highestAmplitude;
    }
    
    return normaliser;
    
}

//--------------------------------------------------------------------------------//
// ANALYSE SAMPLES
//--------------------------------------------------------------------------------//

void Instrument::analyseInstrument()
{
    
    float ratio = 0;
    previousRatio = 0;
    int samples = duration.getSamples();
    
    float sampleLoudness;
    float totalLoudness = 0.0f;
    
    float sampleMeanFrequency;
    float totalMeanFrequency = 0.0f;
    
    double sampleNoiseyness = 0.0;
    double totalNoiseyness = 0.0;
    
    float loudestValue = 0.0;
    float focalPointTime = 0.0;
    
    
    
    getNormaliser();
    
    /* Walk through each sample */
    for (int i=0; i < samples; i++) {
        
        /* Get time value within duration (start = 0.0f, end = 1.0f) */
        ratio = (double)i / (double)samples;
        
        /* Find "loudness" factor for each sample */
        sampleLoudness = getSampleLoudness(ratio);
        totalLoudness += sampleLoudness;
        
        /* Find "meanFrequency for each sample */
        sampleMeanFrequency = getSampleMeanFrequency(ratio);
        totalMeanFrequency += sampleMeanFrequency;
        
        /* Find "noiseyness" factor for each sample */
        if (i != 0) {
            sampleNoiseyness = getSampleNoiseyness(ratio);
            totalNoiseyness = totalNoiseyness + sampleNoiseyness;
        }
        
        /* If is highest value, assign to highest */
        if (sampleLoudness > loudestValue) {
            loudestValue = sampleLoudness;
            focalPointTime = ratio;
        }
        
        previousRatio = ratio;
        
    }
    
    /* Assign Instrument Loudness Factor */
    loudness = totalLoudness / (float)samples;
    
    /* Assign Instrument Mean Frequency */
    meanFrequency.setFrequencyRatio((double)totalMeanFrequency / (double)samples);
    
    /* Assign Instrument Noiseyness */
    noiseyness = totalNoiseyness / ((double)samples-1.0);
    
    /* Push focal point into FocalPoint object */
    duration.focalPoint.setPosition(focalPointTime);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET SAMPLE LOUDNESS
//--------------------------------------------------------------------------------//

double Instrument::getSampleLoudness(double ratio)
{
    
    float sampleLoudness = 0.0f;
    double tempAmpValue;
    double tempFreqValue;
    double tempValue;
    double bassWeight;
    Envelope *envAmp;
    Envelope *envFreq;
    
    for (int i=0; i < numOfOscillators; i++) {
        
        /* Get amp and freq from oscillator at current sample*/
        tempAmpValue = abs(oscillators.at(i).getAmplitudeAtRatio(ratio)
                           * normaliser);
        tempFreqValue = oscillators.at(i).frequency.getValue(ratio);
        
        /* Weight 2khz */
        if (tempFreqValue <= TWO_THOUSAND_HERTZ) {
            tempValue = tempAmpValue
                * ((tempFreqValue/TWO_THOUSAND_HERTZ)
                + (0.9f * (TWO_THOUSAND_HERTZ-tempFreqValue)));
        }
        else if (tempFreqValue > TWO_THOUSAND_HERTZ) {
            tempValue = tempAmpValue
                * ((abs(tempFreqValue-1.0f))/(1.0f-TWO_THOUSAND_HERTZ)
                + (0.9f * ((1.0f-TWO_THOUSAND_HERTZ)-abs(tempFreqValue-1.0f))));
        }
        
        /* Sum values for each oscillator at each sample */
        sampleLoudness += tempValue;
        
    }
    
    return sampleLoudness;
    
}

//--------------------------------------------------------------------------------//
// GET SAMPLE MEAN FREQUENCY
//--------------------------------------------------------------------------------//

double Instrument::getSampleMeanFrequency(double ratio)
{
    
    if (ratio <= 0.0) {
        return 0.0;
    }
    else {}
    
    double sampleMeanFrequency;
    double totalAmp = 0.0;
    double percentageMultiplier;
    double weightedFreq = 0.0;
    double totalWeightedFreq = 0.0;
    double amplitudeWeight;
    
    /* For each activated oscillator */
    for (int i=0; i < numOfOscillators; i++) {
        
        /* Determine collective amplitude of oscillators */
        totalAmp += oscillators.at(i).amplitude.getValue(ratio);
    
    }
    
    /* Determine percentage multiplier for weighting */
    percentageMultiplier = 1.0 / totalAmp;
    
    /* For each activated oscillator */
    for (int i=0; i < numOfOscillators; i++) {
        
        /* Apply weighting multiplier to amplitude to get amp w/ weightpercentage */
        amplitudeWeight = oscillators.at(i).amplitude.getValue(ratio)
                            * percentageMultiplier;
        
        /* Find weighted freq depending on waveform (weighted by amplitudeWeight) */
        if (oscillators.at(i).waveform == JEN_NOISE) {
            weightedFreq = 0.5 * amplitudeWeight;
        }
        else if (oscillators.at(i).waveform == JEN_GAUSSIAN) {
            double tempFreq = oscillators.at(i).frequency.getValue(ratio);
            weightedFreq = pow(tempFreq, 1.5 + tempFreq/2.0)
                        * (MAX_FREQUENCY_B / MAX_FREQUENCY)
                        * amplitudeWeight;
        }
        else {
            weightedFreq = oscillators.at(i).frequency.getValue(ratio)
                        * amplitudeWeight;
        }
        
        /* Add weighted freq to total weighted freq across oscillators */
        totalWeightedFreq += weightedFreq;
        
    }
    
    /* Determine mean frequency for sample */
    sampleMeanFrequency = totalWeightedFreq / (double)numOfOscillators;
    
    return sampleMeanFrequency;
    
}

//--------------------------------------------------------------------------------//
// GET SAMPLE NOISEYNESS
//--------------------------------------------------------------------------------//

double Instrument::getSampleNoiseyness(double ratio)
{
    
    double sampleNoiseyness;
    
    double totalAmp = 0.0;
    double sampleDifference = 0.0;
    double percentageMultiplier;
    double weightedDifference = 0.0;
    double totalWeightedDifference = 0.0;
    
    double amplitudeWeight;
    
    /* For each activated oscillator */
    for (int i=0; i < numOfOscillators; i++) {
        
        /* Determine collective amplitude of oscillators */
        totalAmp += oscillators.at(i).amplitude.getValue(ratio);
        
    }
    
    percentageMultiplier = 1.0 / totalAmp;
    
    for (int i=0; i < numOfOscillators; i++) {
        
        /* Apply weighting multiplier to amplitude to get amp w/ weightpercentage */
        amplitudeWeight = oscillators.at(i).amplitude.getValue(ratio)
                            * percentageMultiplier;
        
        /* Determine sample difference (noise influence for each waveform) */
        if (oscillators.at(i).waveform == JEN_NOISE) {
            sampleDifference = 1.0;
        }
        
        if (oscillators.at(i).waveform == JEN_NOISE_WALK || JEN_GAUSSIAN) {
            sampleDifference =
                        abs(oscillators.at(i).frequency.getValue(previousRatio)
                          - oscillators.at(i).frequency.getValue(ratio)) * 1000.0;
            sampleDifference += (1.0 - sampleDifference) * 0.5;
        }
        
        if (oscillators.at(i).waveform == JEN_SAW || JEN_SQUARE) {
            sampleDifference =
                        abs(oscillators.at(i).frequency.getValue(previousRatio)
                          - oscillators.at(i).frequency.getValue(ratio)) * 1000.0;
            sampleDifference += (1.0 - sampleDifference) * 0.25;
        }
        
        if (oscillators.at(i).waveform == JEN_SINE) {
            sampleDifference =
                        abs(oscillators.at(i).frequency.getValue(previousRatio)
                          - oscillators.at(i).frequency.getValue(ratio)) * 1000.0;
        }
        
        /* Weight difference using amplitude weighting */
        weightedDifference = sampleDifference * amplitudeWeight * numOfOscillators;
        
        /* Add each oscillators difference to total difference */
        totalWeightedDifference += weightedDifference;
        
    }
    
    //cout << totalWeightedDifference << endl;
    
    sampleNoiseyness = totalWeightedDifference / (double)numOfOscillators;
    
    //cout << sampleNoiseyness << endl;
    
    return sampleNoiseyness;
    
}

//--------------------------------------------------------------------------------//
// GET AMPLITUDE AT
//--------------------------------------------------------------------------------//

double Instrument::getAmplitudeAtSample(int sample)
{
    
    double sampleTime = sample / duration.getSamples();
    
    if (sampleTime > 1.0f || sampleTime < 0.0f) {
        cout << "Sample input error - must be within instrument duration!" << endl;
        return;
    }
    else {}
    
    return getAmplitudeAtRatio(sampleTime);
    
}

//--------------------------------------------------------------------------------//
// GET AMPLITUDE AT (CURRENT SAMPLE / DURATION.GETSAMPLES())
//--------------------------------------------------------------------------------//

double Instrument::getAmplitudeAtRatio(double ratio)
{
    
    if (ratio > 1.0f || ratio < 0.0f) {
        cout << "Sample input error - must be within instrument duration!" << endl;
        return;
    }
    else {}
    
    double amplitude = 0;
    
    /* Get amplitude for each oscillator */
    for (int i=0; i < numOfOscillators; i++) {
        
        /* Sum values for each oscillator at each sample */
        amplitude += oscillators.at(i).getAmplitudeAtRatio(ratio);
        
    }
    
    return amplitude;
    
}

//--------------------------------------------------------------------------------//
// COMPARE TO ANOTHER INSTRUMENT (AND SET DIFFERENCE)
//--------------------------------------------------------------------------------//

float Instrument::compareToInstrument(Instrument *instrument)
{
    
    /* Find Initial Differences */
    double loudnessDifference = abs(relativeLoudness - instrument->loudness);
    
    double noiseynessDifference = abs(relativeNoiseyness - instrument->noiseyness);
    
    double meanFrequencyDifference =
                    meanFrequency.findDifference(&instrument->meanFrequency);
    
    float durationDifference = duration.findDifference(&instrument->duration);
    
    /* Weight duration difference */
    durationDifference *= 3.0f;
    
    /* Weight meanFrequency difference */
    meanFrequencyDifference *= 3.0;
    
    /* Get total difference by adding all differences */
    difference = loudnessDifference
    + noiseynessDifference
    + meanFrequencyDifference
    + durationDifference;
    
    return difference;
    
}

//--------------------------------------------------------------------------------//
// PLAYBACK INSTRUMENT
//--------------------------------------------------------------------------------//

void Instrument::play()
{
    
    for (int i=0; i < numOfOscillators; i++) {
        
        oscillators.at(i).play();
        
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
// PRINT ANALYSED DATA TO CONSOLE
//--------------------------------------------------------------------------------//

void Instrument::printAnalysisData()
{
    
    cout << "\n";
    cout << ofToString(name)
    + "\n\t| normaliser: "
    + ofToString(normaliser)
    + "\n\t| Loudness: "
    + ofToString(loudness)
    + "\n\t| Relative Loudness: "
    + ofToString(relativeLoudness)
    + "\n\t| Mean Frequency: "
    + ofToString(meanFrequency.frequencyRatio)
    + " || " + ofToString(meanFrequency.hz) + "hz"
    + "\n\t| Noiseyness: "
    + ofToString(noiseyness)
    + "\n\t| Relative Noiseyness: "
    + ofToString(relativeNoiseyness)
    << endl;
    cout <<
    "\t| Focal Point: ";
    for (int i=0; i<duration.focalPoint.positions.size(); i++) {
        cout << ofToString(duration.focalPoint.positions.at(0)) + " | ";
    }
    cout << "\n";
    
    
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//


