//
//  Algebraic.h
//  jenMax
//
//  Created by Mitchell Nordine on 5/08/13.
//
//

#ifndef __jenMax__Algebraic__
#define __jenMax__Algebraic__

/* Header Includes */

#include "ofMain.h"
#include "JenGaussian.h"

#define JEN_SINE 0
#define JEN_SAW 1
#define JEN_SQUARE 2
#define JEN_NOISE 3
#define JEN_NOISE_WALK 4
#define JEN_GAUSSIAN 5

/* Class */

class Algebraic {
    
public:
    
    /* Constructors & Destructors */
    
    Algebraic(){
        value = 1.0f;
        originalValue = 1.0f;
        pointX = 1.0f;
        pointY = 0.0f;
        gradient = 1.0f;
        bezierDepth = 0.0f;
        frequency = 1.0f;
        amplitude = 1.0f;
        min = 0.0f;
        max = 0.0f;
        bezier = 0.0f;
    }
    
    ~Algebraic(){
        
    }
    
    /* Functions */
    void setup(float value);
    float setGradient(float pointX, float pointY);
    float setMin(float _min);
    float setMax(float _max);
    float setMinMax(float _min, float _max);
    
    double getWaveformValue(int waveform);
    
    float getSine();
    float getSaw();
    float getSquare();
    float getRandom();
    float getNoiseWalk();
    float getGaussian();
    
    float getSignal(float value);
    float getSignal();
    
    float getBezier();
    float getBezierPt(float n1, float n2, float perc);
    float setBezierDepth(float _depth);
    
    float setFrequency(float _frequency);
    float setAmplitude(float _amplitude);
    float getWithAmplitude(float value);
    
    /* Variable Declaration */
    
    float value;
    float originalValue;
    float pointX;
    float pointY;
    float min;
    float max;
    
    float gradient;
    
    float bezier;
    float bezierDepth;
    
    float frequency;
    float amplitude;
    
    /* Class Instances */
    
};


#endif /* defined(__jenMax__Algebraic__) */
