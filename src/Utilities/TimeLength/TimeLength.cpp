//
//  Duration.cpp
//  jenMax
//
//  Created by Mitchell Nordine on 2/08/13.
//
//

#include "TimeLength.h"

//--------------------------------------------------------------------------------//
// SETUP TIMELENGTH
//--------------------------------------------------------------------------------//

void TimeLength::setup(GUI *_gui)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    focalPoint.setup(gui);
    
    return;
    
}

void TimeLength::setup(GUI *_gui, float focalPointPosition)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    focalPoint.setup(gui, focalPointPosition);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// INITIALISE TIMELENGTH OBJECT
//--------------------------------------------------------------------------------//

void TimeLength::initialise()
{
    
    ms = 0.0f;
    num = 0;
    te = 0;
    teType = HALVE;
    
    smallestMS = 0.0f;
    smallestSamples = 0;
    largestMS = 0.0f;
    largestSamples = 0;
    ratio = 0.0f;
    scaleCurve = 0.0f;
    
    focalPoint.initialise();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET DURATION IN MILLISECONDS
//--------------------------------------------------------------------------------//

float TimeLength::setMS(float _ms)
{
    
    ms = _ms;
    
    getSamples();
    
    return ms;
    
}

//--------------------------------------------------------------------------------//
// GET DURATION IN MS
//--------------------------------------------------------------------------------//

float TimeLength::getMs()
{
    
    /* Convert from Transport Events */
    if (num > 0 && te >= BAR) {
        teToMs();
    }
    
    /* Convert from Sample Rate */
    else if (samples != 0) {
        samplesToMs();
    }
    
    return ms;
    
}

//--------------------------------------------------------------------------------//
// GET BAR LENGTH IN MS
//--------------------------------------------------------------------------------//

float TimeLength::getBarMS()
{
    
    return ((float)MINUTE_MS / guiGlobal->tempo)
            * (4 * guiGlobal->timeSig.first
            / guiGlobal->timeSig.second);
    
}

//--------------------------------------------------------------------------------//
// SET DURATION IN SAMPLES
//--------------------------------------------------------------------------------//

int TimeLength::setSamples(int _samples)
{
    
    samples = _samples;
    
    getMs();
    
    return samples;
    
}

//--------------------------------------------------------------------------------//
// GET DURATION IN SAMPLES
//--------------------------------------------------------------------------------//

int TimeLength::getSamples()
{
    
    /* Convert from Transport Events */
    if (num != 0 && te >= BAR) {
        teToMs();
        msToSamples();
    }
    
    /* Convert from ms */
    else if (ms > 0) {
        msToSamples();
    }
    
    return samples;
    
}

//--------------------------------------------------------------------------------//
// GET BAR LENGTH IN SAMPLES
//--------------------------------------------------------------------------------//

int TimeLength::getBarSamples()
{
    
    return ((float)MINUTE_MS / guiGlobal->tempo)
    * (4 * guiGlobal->timeSig.first
       / guiGlobal->timeSig.second) * guiGlobal->sampleRate / 1000.0f;
    
}

//--------------------------------------------------------------------------------//
// CONVERT MS TO SAMPLES
//--------------------------------------------------------------------------------//

int TimeLength::msToSamples()
{
    
    /* There are "global.sampleRate" number of samples per second, and 1ms
     is the equivalent of 1/1000seconds. Thus... */
    samples = (ms * guiGlobal->sampleRate) / 1000.0f;
    
    return samples;
    
}

int TimeLength::msToSamples(float _ms)
{
    
    /* There are "global.sampleRate" number of samples per second, and 1ms
     is the equivalent of 1/1000seconds. Thus... */
    int _samples = (_ms * guiGlobal->sampleRate) / 1000.0f;
    
    return _samples;
    
}

//--------------------------------------------------------------------------------//
// CONVERT SAMPLES TO MS
//--------------------------------------------------------------------------------//

float TimeLength::samplesToMs()
{
    
    /* There are "global.sampleRate" number of samples per second, and 1ms
     is the equivalent of 1/1000seconds. Thus... */
    ms = (samples / guiGlobal->sampleRate) * 1000;
    
    return ms;
    
}

float TimeLength::samplesToMs(int _samples)
{
    
    /* There are "global.sampleRate" number of samples per second, and 1ms
     is the equivalent of 1/1000seconds. Thus... */
    float _ms = (_samples / guiGlobal->sampleRate) * 1000;
    
    return _ms;
    
}

//--------------------------------------------------------------------------------//
// CONVERT TIME EVENTS TO MS
//--------------------------------------------------------------------------------//

float TimeLength::teToMs()
{
    
    if (teType == HALVE) {
        ms = (getBarMS() * pow(0.5f, (te-1.0f))) * num;
    }
    
    else if (teType == THIRD) {
        ms = ((getBarMS() * pow(0.5f, (te-2.0f))) / 3.0f) * num;
    }
    
    /* If no type declared, teType "halve" will be assumed and set */
    else{
        teType = HALVE;
        ms = (getBarMS() * pow(0.5f, (te-1.0f))) * num;
    }
    
    return ms;
    
}

//--------------------------------------------------------------------------------//
// SETUP WITH TIME EVENTS (including time event division type)
//--------------------------------------------------------------------------------//

void TimeLength::setTimeEvents(int _num, int _te, bool _teType)
{
    
    num = _num;
    te = _te;
    teType = _teType;
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SETUP WITH TIME EVENTS
//--------------------------------------------------------------------------------//

void TimeLength::setTimeEvents(int _num, int _te)
{
    
    num = _num;
    te = _te;
    
    if (teType != 0) {
        teType = HALVE;
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// CONVERT TIME EVENTS TO MS
//--------------------------------------------------------------------------------//

float TimeLength::getTimeEventsMS(int _num, int _te, bool _teType)
{
    
    float tempMS;
    
    if (_teType == HALVE) {
        tempMS = (getBarMS() * pow(0.5f, (_te-1.0f))) * _num;
    }
    
    else if (_teType == THIRD) {
        tempMS = ((getBarMS() * pow(0.5f, (_te-2.0f))) / 3.0f) * _num;
    }
    
    /* If no type declared, teType "halve" will be assumed and set */
    else{
        _teType = HALVE;
        tempMS = (getBarMS() * pow(0.5f, (_te-1.0f))) * _num;
    }
    
    return tempMS;
    
}

//--------------------------------------------------------------------------------//
// GET TIME VALUE IN MILLISECONDS
//--------------------------------------------------------------------------------//

float TimeLength::getTimeValueMS(int _num, int _divisions)
{
    
    return getBarMS() * _num / _divisions;
    
}

//--------------------------------------------------------------------------------//
// GET TIME VALUE IN SAMPLES
//--------------------------------------------------------------------------------//

int TimeLength::getTimeValueSamples(int _num, int _divisions)
{
    
    return getBarSamples() * _num / _divisions;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------//
//
//------------------------------------ SCALE -------------------------------------//
//
//--------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------//
// SET SCALE IN MS
//--------------------------------------------------------------------------------//

void TimeLength::setScaleMS(float _smallestMS, float _largestMS)
{
    
    smallestMS = _smallestMS;
    largestMS = _largestMS;
    
    smallestSamples = msToSamples(smallestMS);
    largestSamples = msToSamples(largestMS);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET SMALLEST IN MS
//--------------------------------------------------------------------------------//

void TimeLength::setSmallestMS(float _smallestMS)
{
    
    smallestMS = _smallestMS;
    
    smallestSamples = msToSamples(smallestMS);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET LARGEST IN MS
//--------------------------------------------------------------------------------//

void TimeLength::setLargestMS(float _largestMS)
{
    
    largestMS = _largestMS;
    
    largestSamples = msToSamples(largestMS);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET SCALE IN SAMPLES
//--------------------------------------------------------------------------------//

void TimeLength::setScaleSamples(int _smallestSamples, int _largestSamples)
{
    
    smallestSamples = _smallestSamples;
    largestSamples = _largestSamples;
    
    smallestMS = samplesToMs(smallestSamples);
    largestMS = samplesToMs(largestSamples);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET SMALLEST IN SAMPLES
//--------------------------------------------------------------------------------//

void TimeLength::setSmallestSamples(int _smallestSamples)
{
    
    smallestSamples = _smallestSamples;
    
    smallestMS = samplesToMs(smallestSamples);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET LARGEST IN SAMPLES
//--------------------------------------------------------------------------------//

void TimeLength::setLargestSample(float _largestSamples)
{
    
    largestSamples = _largestSamples;
    
    largestMS = samplesToMs(largestSamples);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET SCALE WITH TIME EVENTS
//--------------------------------------------------------------------------------//

void TimeLength::setScaleTE(int _numSmall, int _teSmall, bool _teTypeSmall,
                            int _numLarge, int _teLarge, bool _teTypeLarge)
{
    
    smallestNum = _numSmall; smallestTe = _teSmall; smallestTeType = _teTypeSmall;
    largestNum = _numLarge; largestTe = _teLarge; largestTeType = _teTypeLarge;
    
    setScaleMS(getTimeEventsMS(smallestNum, smallestTe, smallestTeType),
               getTimeEventsMS(largestNum, largestTe, largestTeType));
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET SMALLEST WITH TIME EVENT
//--------------------------------------------------------------------------------//

void TimeLength::setSmallestTE(int _smallestNum, int _smallestTe, int _smallestTeType)
{
    
    smallestNum = _smallestNum;
    smallestTe = _smallestTe;
    smallestTeType = _smallestTeType;
    
    setSmallestMS(getTimeEventsMS(smallestNum, smallestTe, smallestTeType));
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET LARGEST WITH TIME EVENT
//--------------------------------------------------------------------------------//

void TimeLength::setLargestTE(int _largestNum, int _largestTe, int _largestTeType)
{
    
    largestNum = _largestNum;
    largestTe = _largestTe;
    largestTeType = _largestTeType;
    
    setLargestMS(getTimeEventsMS(largestNum, largestTe, largestTeType));
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET RATIO
//--------------------------------------------------------------------------------//

float TimeLength::getRatio()
{
    
    return ratio = getRatioMS(getMs());
    
}

//--------------------------------------------------------------------------------//
// GET RATIO
//--------------------------------------------------------------------------------//

float TimeLength::getRatioMS(float _ms)
{
    
    ratio = ofMap(_ms, smallestMS, largestMS, 0.0f, 1.0f);
    
    ratio = pow(ratio, 1.0f / (1.0f + scaleCurve));
    
    return ratio;
    
}

//--------------------------------------------------------------------------------//
// GET RATIO
//--------------------------------------------------------------------------------//

float TimeLength::getRatioSamples(int _samples)
{
    
    ratio = ofMap(_samples, smallestSamples, largestSamples, 0.0f, 1.0f);
    
    ratio = pow(ratio, 1.0f / (1.0f + scaleCurve));
    
    return ratio;
    
}

//--------------------------------------------------------------------------------//
// GET MS FROM RATIO
//--------------------------------------------------------------------------------//

float TimeLength::getMSfromRatio(float _ratio)
{
    
    _ratio = pow(_ratio, 1.0f + scaleCurve);
    
    ms = ofMap(_ratio, 0.0f, 1.0f, smallestMS, largestMS);
    
    return ms;
    
}

//--------------------------------------------------------------------------------//
// SET RATIO
//--------------------------------------------------------------------------------//

void TimeLength::setRatio(float _ratio)
{
    
    ratio = _ratio;
    
    setMS(getMSfromRatio(ratio));
    
    return;
    
}

//--------------------------------------------------------------------------------//
// COMPARE TO ANOTHER TIME LENGTH OBJECT
//--------------------------------------------------------------------------------//

float TimeLength::findDifference(TimeLength *duration)
{
    
    float difference;
    
    scaleCurve = duration->scaleCurve;
    setScaleMS(duration->smallestMS, duration->largestMS);
    getRatioMS(ms);
    
    difference = abs(ratio - duration->ratio);
    
    return difference;
    
}

//--------------------------------------------------------------------------------//
// RETURN THE RATIO AT BEAT
//--------------------------------------------------------------------------------//

float TimeLength::getRatioAtBeat()
{
    
    float tempMS = getTimeEventsMS(1, BEAT, HALVE);
    
    float tempRatio = (tempMS, smallestMS, largestMS, 0.0f, 1.0f);
    
    tempRatio = pow(tempRatio, 1.0f / (1.0f + scaleCurve));
    
    return tempRatio;
    
}

//--------------------------------------------------------------------------------//
// FIND RATIO OF NEAREST TIME EVENT
//--------------------------------------------------------------------------------//

void TimeLength::setDurationAtNearestTE()
{
    
    float tempMS, closestMS, differenceMS, lowestDifferenceMS;
    int tempNum, tempTe, tempTeType;
    
    //cout << largestNum << endl;
    
    /* Assuming largest num is set in bars... */
    for (int i=largestNum; i > 0; i--) {
        
        /* If largestNum / i == whole number of bars... */
        if (largestNum % i == 0) {
            
            tempMS = getTimeEventsMS(i, 1, HALVE);
            differenceMS = abs(ms-tempMS);
            
            if (differenceMS < lowestDifferenceMS) {
                lowestDifferenceMS = differenceMS;
                closestMS = tempMS;
                tempNum = i;
                tempTe = 1;
                tempTeType = HALVE;
            }
            
        }
        
    }
    
    /* Check each level of resolution */
    for (int i=1; i < guiGlobal->timeSig.first; i++) {
        
        /* Checks half divisions of bar */
        tempMS = getTimeEventsMS(1, i, HALVE);
        differenceMS = abs(ms-tempMS);
        
        if (differenceMS < lowestDifferenceMS) {
            lowestDifferenceMS = differenceMS;
            closestMS = tempMS;
            tempNum = 1;
            tempTe = i;
            tempTeType = HALVE;
        }
        
        /* Checks third divisions of bar */
        tempMS = getTimeEventsMS(1, i, THIRD);
        differenceMS = abs(ms-tempMS);
        
        if (differenceMS < lowestDifferenceMS) {
            lowestDifferenceMS = differenceMS;
            closestMS = tempMS;
            tempNum = 1;
            tempTe = i;
            tempTeType = THIRD;
        }
        
    }
    
    setMS(closestMS);
    
    getRatioMS(closestMS);
    
    setTimeEvents(tempNum, tempTe, tempTeType);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// FIND DIFFERENCE TO BEAT
//--------------------------------------------------------------------------------//

float TimeLength::findDifferenceToBeatMS()
{
    
    /* Find the difference to quaver (most common duration of "beat rhythm" inst */
    differenceToBeatMS = ms - getTimeEventsMS(1, QUAVER, HALVE);
    
    return differenceToBeatMS;
    
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