//
//  TimeLength.h
//  jenMax
//
//  Created by Mitchell Nordine on 2/08/13.
//
//

#ifndef __jenMax__Duration__
#define __jenMax__Duration__

#define BAR 1
#define MINIM 2
#define BEAT 3
#define QUAVER 4
#define SEMI_QUAVER 5
#define DEMI_SEMI_QUAVER 6
#define HEMI_DEMI_SEMI_QUAVER 7

#define HALVE 0
#define THIRD 1

#define MINUTE_MS 60000

/* Header Includes */

#include "ofMain.h"
#include "FocalPoint.h"

/* Class */

class TimeLength {
    
public:
    
    /* Constructor */
    
    TimeLength(){
        initialise();
    }
    ~TimeLength(){
        
    }
    
    /* Functions */
    void setup(GUI *_gui);
    void setup(GUI *_gui, float focalPointPosition);
    void initialise();
    
    /* MS */
    float setMS(float _ms);
    float getMs();
    float getBarMS();
    
    /* Samples */
    int setSamples(int _samples);
    int getSamples();
    int getBarSamples();
    
    /* Time Events */
    void setTimeEvents(int _num, int _te, bool _teType);
    void setTimeEvents(int _num, int _te);
    
    /* Conversion*/
    float teToMs();
    int msToSamples();
    int msToSamples(float _ms);
    float samplesToMs();
    float samplesToMs(int _samples);
    float getTimeEventsMS(int _num, int _te, bool _teType);

    /* Transport Functions */
    float getTimeValueMS(int _num, int _divisions);
    int getTimeValueSamples(int _num, int _divisions);
    
    /* Scale */
    void setScaleMS(float _smallestMS, float _largestMS);
    void setScaleSamples(int _smallestSamples, int _largestSamples);
    void setScaleTE(int _numSmall, int _teSmall, bool _teTypeSmall,
                    int _numLarge, int _teLarge, bool _teTypeLarge);
    
    void setSmallestMS(float _smallestMS);
    void setSmallestSamples(int _smallestSamples);
    void setSmallestTE(int _smallestNum, int _smallestTe, int _smallestTeType);
    
    void setLargestMS(float _largestMS);
    void setLargestSample(float _largestSamples);
    void setLargestTE(int _largestNum, int _largestTe, int _largestTeType);
    
    float getRatio();
    float getRatioMS(float _ms);
    float getRatioSamples(int _samples);
    float getMSfromRatio(float _ratio);
    void setRatio(float _ratio);
    float getRatioAtBeat();
    void setDurationAtNearestTE();
    
    /* Comparison */
    float findDifference(TimeLength *duration);
    float findDifferenceToBeatMS();
    
    /* Variable Declaration */
    
    float ms = 0.0f; /* Duration in milliseconds */
    int samples = 0; /* Duration in samples */
    bool teType; /* Time Event resolution Type (ie.
                    halve (halve at resolution)
                    third (third at resolution) */
    int num = 0; /* Number of "te" (time events) */
    int te = 0; /* Time Event resolution where max is global->resolution 
             (ie. 1 = 1 bar || 2/3 bar
                  2 = 1/2 bar (minim) || 1/3 bar (triplet)
                  3 = 1/4 bar (beat) || 1/6 bar
                  4 = 1/8 bar (quaver) || 1/12 bar
                  5 = 1/16 bar (semi-quaver) || 1/24 bar
                  6 = 1/32 bar (demi-semi-quaver) || 1/48 bar
                  7 = 1/64 bar (hemi-demi-semi-quaver) || 1/96 bar
                  8 = 1/128 bar || 1/192 bar
                  9 = 1/256 bar || 1/384 bar */
    
    /* Scale */
    float smallestMS;
    float smallestSamples;
    int smallestNum, smallestTe, smallestTeType;
    int largestNum, largestTe, largestTeType;
    float largestMS;
    float largestSamples;
    float ratio;
    float scaleCurve;
    
    /* Difference */
    float differenceToBeatMS; // negative means smaller than beat.

    FocalPoint focalPoint;
    
    /* Class Instances */
    
    GUI *gui;
    GuiGlobal *guiGlobal;
    
};

#endif /* defined(__jenMax__Duration__) */
