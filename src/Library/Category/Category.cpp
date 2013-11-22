//
//  Category.cpp
//  jenMax
//
//  Created by Mitchell Nordine on 3/08/13.
//
//

#include "Category.h"

//--------------------------------------------------------------------------------//
// SETUP CATEGORY
//--------------------------------------------------------------------------------//

void Category::setup(GUI *_gui)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    
    /* Setup duration scale */
    durationScale.setup(gui);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET CATEGORY NAME
//--------------------------------------------------------------------------------//

void Category::setName(string _name)
{
    
    name = _name;
    getInt(name);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SET CATEGORY INTEGER ID
//--------------------------------------------------------------------------------//

void Category::setIntID(int ID)
{
    
    integer = ID;
    getName(integer);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET CATEGORY NAME
//--------------------------------------------------------------------------------//

string Category::getName(int categoryInt)
{
    
    integer = categoryInt;
    
    switch (categoryInt) {
        case KIT: name = "KIT"; break;
        case BASS: name = "BASS"; break;
        case MELODIC: name = "MELODIC"; break;
        case CHORDAL: name = "CHORDAL"; break;
        case ATMOS: name = "ATMOS"; break;
            
        default: name = "KIT"; break;
    }
    
    return name;
    
}

//--------------------------------------------------------------------------------//
// GET CATEGORY INTEGER REPRESENTATIVE
//--------------------------------------------------------------------------------//

int Category::getInt(string categoryName)
{
    
    name = categoryName;
    
    if (name == "KIT") { integer = 0; }
    else if (name == "BASS") { integer = 1; }
    else if (name == "MELODIC") { integer = 2; }
    else if (name == "CHORDAL") { integer = 3; }
    else if (name == "ATMOS") { integer = 4; }
    
    return integer;
    
}

//--------------------------------------------------------------------------------//
// GET VECTOR OF INSTRUMENT POINTERS FOR "CATEGORY NAME"
//--------------------------------------------------------------------------------//

vector<Instrument*> Category::getVectorOfInstrumentPointers()
{
    
    vector<Instrument*> instPtrList;
    
    for (int i=0; i < instrumentList.size(); i++) {
        
        instPtrList.push_back(instrumentList.at(i));
        
    }
    
    return instPtrList;
    
}

//--------------------------------------------------------------------------------//
// LOUDNESS COMPARISON
//--------------------------------------------------------------------------------//

void Category::instrumentRelativity()
{
    
    double highestLoudness = 0;
    double highestNoiseyness = 0;
    double loudnessMultiplier;
    double noiseynessMultiplier;
    float largestMS = 0.0f;
    float smallestMS;
    
    for (int i=0; i < instrumentList.size(); i++) {
        
        /* Loudness */
        if (instrumentList.at(i)->loudness > highestLoudness) {
            highestLoudness = instrumentList.at(i)->loudness;
        }
        
        /* Noiseyness */
        if (instrumentList.at(i)->noiseyness > highestNoiseyness) {
            highestNoiseyness = instrumentList.at(i)->noiseyness;
        }
        
        /* Duration Scale */
        if (instrumentList.at(i)->duration.getMs() > largestMS) {
            largestMS = instrumentList.at(i)->duration.getMs();
        }
        if (instrumentList.at(i)->duration.getMs() < smallestMS || i == 0) {
            smallestMS = instrumentList.at(i)->duration.getMs();
        }
        
    }
    
    /* Get loudness multiplier */
    loudnessMultiplier = 1.0 / highestLoudness;
    
    /* Get noiseyness multiplier */
    noiseynessMultiplier = 1.0 / highestNoiseyness;
    
    /* Apply multipliers to each instrument to get relative value */
    for (int i=0; i < instrumentList.size(); i++) {
        
        /* Set relativeLoudness */
        instrumentList.at(i)->relativeLoudness
                        = instrumentList.at(i)->loudness * loudnessMultiplier;
        
        /* Set relativeNoiseyness */
        instrumentList.at(i)->relativeNoiseyness
                        = instrumentList.at(i)->noiseyness * noiseynessMultiplier;
        
    }
    
    /* Set duration scale */
    durationScale.setScaleMS(smallestMS, largestMS);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET NUMBER OF INSTRUMENTS USING PERCENTAGE WEIGHT
//--------------------------------------------------------------------------------//

void Category::getNumOfInstruments(int totalNumOfInstruments)
{
    
    return numOfInstruments = percentageWeight * totalNumOfInstruments;
    
}

//--------------------------------------------------------------------------------//
// SET DURATION SCALE
//--------------------------------------------------------------------------------//

void Category::setDurationScale()
{
    
    float largestMS = 0.0f;
    float smallestMS;
    
    for (int i=0; i < instrumentList.size(); i++) {
        
        if (instrumentList.at(i)->duration.getMs() > largestMS) {
            largestMS = instrumentList.at(i)->duration.getMs();
        }
        
        if (instrumentList.at(i)->duration.getMs() < smallestMS || i == 0) {
            smallestMS = instrumentList.at(i)->duration.getMs();
        }
        
    }
    
    /* Set duration scale */
    durationScale.setScaleMS(smallestMS, largestMS);
    
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
// PRINT CATEGORY DATA
//--------------------------------------------------------------------------------//

void Category::printCategoryData()
{
    
    string underline = "";
    for (int i=0; i < name.length(); i++) {
        underline.push_back('-');
    }
    
    cout << "\n||==============================||\n\n";
    cout << name << endl;
    cout << underline + "\n" << endl;
    cout << "Number of instruments = " + ofToString(instrumentList.size()) << endl;
    
    for (int i=0; i < instrumentList.size(); i++) {
        
        instrumentList.at(i)->printAnalysisData();
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//