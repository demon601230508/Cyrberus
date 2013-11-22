//
//  Frequency.cpp
//  GenMax
//
//  Created by Mitchell Nordine on 12/11/2013.
//
//

#include "Frequency.h"

//--------------------------------------------------------------------------------//
// SETUP FREQUENCY
//--------------------------------------------------------------------------------//

void Frequency::setup(GUI *_gui)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    highestFrequency = CYR_HIGHEST_FREQUENCY;
    lowestFrequency = CYR_LOWEST_FREQUENCY;
    
    return;
    
}

//--------------------------------------------------------------------------------//
// INITIALISE FREQUENCY CONTENTS
//--------------------------------------------------------------------------------//

void Frequency::initialise()
{
    
    hz = 0.0;
    frequencyRatio = 0.0;
    scaleRatio = 0.0;
    highestFrequency = NULL;
    lowestFrequency = NULL;
    scaleCurve = 0.0;
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET FREQUENCY BY SCALE POSITION
//--------------------------------------------------------------------------------//

void Frequency::setScaleRatio(double _scaleRatio)
{
    
    if (_scaleRatio < 0.0 || _scaleRatio > 1.0) {
        cout <<
        "Entered frequency is out of scale range! Must be between 0.0f & 1.0f!"
        << endl;
    }
    
    scaleRatio = _scaleRatio;
    
    hz = pow(scaleRatio, 4.0 + scaleCurve)
            * (highestFrequency-lowestFrequency)
            + lowestFrequency;
    
    getFrequencyRatio();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET LINEAR FREQUENCY RATIO
//--------------------------------------------------------------------------------//

void Frequency::setFrequencyRatio(double _frequencyRatio)
{
    
    if (_frequencyRatio < 0.0 || _frequencyRatio > 1.0) {
        cout <<
        "Entered frequency is out of scale range! Must be between 0.0f & 1.0f!"
        << endl;
    }
    
    frequencyRatio = _frequencyRatio;
    
    hz = frequencyRatio * (MAX_FREQUENCY - MIN_FREQUENCY) + MIN_FREQUENCY;
    
    getScaleRatio();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET FREQUENCY BY HZ
//--------------------------------------------------------------------------------//

void Frequency::setFrequencyHz(double _frequencyHz)
{
    
    if (_frequencyHz < lowestFrequency || _frequencyHz > highestFrequency) {
        cout << "Entered frequency is out of hz range! Must be between "
        + ofToString(lowestFrequency) + "hz and "
        + ofToString(highestFrequency) + "hz!" << endl;
        return;
    }
    
    hz = _frequencyHz;
    
    getScaleRatio();
    
    getFrequencyRatio();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET RATIO OF FREQUENCY TO SCALE
//--------------------------------------------------------------------------------//

double Frequency::getScaleRatio()
{
    
    scaleRatio = pow(hz / (highestFrequency-lowestFrequency),
                1.0 / (4.0 + scaleCurve));
    
    return scaleRatio;
    
}

//--------------------------------------------------------------------------------//
// GET RATIO OF FREQUENCY LINEARLY
//--------------------------------------------------------------------------------//

double Frequency::getFrequencyRatio()
{
    
    frequencyRatio = hz / (MAX_FREQUENCY - MIN_FREQUENCY);
    
    return frequencyRatio;
    
}

//--------------------------------------------------------------------------------//
// COMPARE TO ANOTHER FREQUENCY OBJECT (AND FIND DIFFERENCE)
//--------------------------------------------------------------------------------//

float Frequency::findDifference(Frequency *frequency)
{
    
    float difference;
    
    Frequency tempFrequency;
    tempFrequency.setup(gui);
    tempFrequency.hz = hz;
    tempFrequency.scaleCurve = frequency->scaleCurve;
    
    tempFrequency.setScaleRatio(
            ofMap(tempFrequency.getScaleRatio(),
            tempFrequency.lowestFrequency, tempFrequency.highestFrequency,
            frequency->lowestFrequency, frequency->highestFrequency)
                           );
    
    difference = abs(tempFrequency.scaleRatio - frequency->scaleRatio);
    
    return difference;
    
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