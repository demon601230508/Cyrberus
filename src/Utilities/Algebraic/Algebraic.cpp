//
//  Algebraic.cpp
//  jenMax
//
//  Created by Mitchell Nordine on 5/08/13.
//
//

#include "Algebraic.h"

/*
 
 ABOUT ALGEBRAIC
 ***************
 
 Algebraic will return f(value) where value is passed in through
 setup(float _value).
 
 Without any input, Algebraic will return 1.0f.
 
 Algebraic will take into account any information you give it.
 
 It includes support for:
    - Sine
    - Sawtooth
    - Square
    - RandomWalk
    - Random
    - Triangle

    - Gradient
    - Bezier
    - Exponential

The signal is modulated by the following (REMEMBER, each of these can be
modulated with another "Algebraic" object):
    - Amplitude
    - Frequency 

The "gradient" is added to the result (determined by entering the x & y
co-ordinates).

 */

//--------------------------------------------------------------------------------//
// SETUP ALGEBRAIC
//--------------------------------------------------------------------------------//

void Algebraic::setup(float _value)
{
    
    originalValue = _value;
    value = originalValue;
    
    return;
    
}

//--------------------------------------------------------------------------------//
// RETURN SINE
//--------------------------------------------------------------------------------//

float Algebraic::getSine()
{
    
    float answer;
    
    answer = sin(TWO_PI * value * frequency / pointX);
    
    answer = getSignal(answer);
    
    //cout << answer << endl;
    
    return answer;
    
}

//--------------------------------------------------------------------------------//
// RETURN SAW
//--------------------------------------------------------------------------------//

float Algebraic::getSaw()
{
    
    float answer;
    
    answer = fmod(value * frequency / pointX, 1.0f) * 2 - 1;
    
    answer = getSignal(answer);
    
    return answer;
    
}

//--------------------------------------------------------------------------------//
// RETURN SQUARE
//--------------------------------------------------------------------------------//

float Algebraic::getSquare()
{
    
    float answer;
    
    answer = sin(TWO_PI * value * frequency / pointX);
    
    if (answer > 0) {
        answer = 1.0f;
    }
    else if (answer < 0) {
        answer = -1.0f;
    }
    
    answer = getSignal(answer);
    
    return answer;
    
}

//--------------------------------------------------------------------------------//
// RETURN RANDOM
//--------------------------------------------------------------------------------//

float Algebraic::getRandom()
{
    
    float answer;
    
    answer = ofRandom(-1.0f, 1.0f);
    
    answer = getSignal(answer);
    
    return answer;
    
}

//--------------------------------------------------------------------------------//
// RETURN NOISE WALK
//--------------------------------------------------------------------------------//

float Algebraic::getNoiseWalk()
{
    
    float answer;
    
    answer = ofSignedNoise(value * frequency / pointX);
    
    answer = getSignal(answer);
    
    return answer;
    
}

//--------------------------------------------------------------------------------//
// RETURN GAUSSIAN
//--------------------------------------------------------------------------------//

float Algebraic::getGaussian()
{
    
    float answer;
    float freq = JenGaussianAlt(frequency,0.01*frequency);
    
    //answer = sin(TWO_PI * value * freq / pointX);
    //answer = fmod(value * freq / pointX, 1.0f) * 2 - 1;
    answer = getSine();
    
    answer = getSignal(answer);
    
    return answer;
    
}

//--------------------------------------------------------------------------------//
// SET AMPLITUDE
//--------------------------------------------------------------------------------//

float Algebraic::setAmplitude(float _amplitude)
{
    
    amplitude = _amplitude;
    
    return amplitude;
    
}

//--------------------------------------------------------------------------------//
// SET FREQUENCY
//--------------------------------------------------------------------------------//

float Algebraic::setFrequency(float _frequency)
{
    
    frequency = _frequency;
    
    return frequency;
    
}

//--------------------------------------------------------------------------------//
// GET VALUE MULTIPLIED BY AMPLITUDE
//--------------------------------------------------------------------------------//

float Algebraic::getWithAmplitude(float value)
{
    
    /* Multiplies value with amplitude */
    value = value * amplitude;
    
    return value;
    
}

//--------------------------------------------------------------------------------//
// RETURN GRADIENT
//--------------------------------------------------------------------------------//

float Algebraic::setGradient(float _pointX, float _pointY)
{
    
    pointX = _pointX;
    pointY = _pointY;
    
    /* Find gradient by dividing y by x */
    gradient = (float)pointY / (float)pointX;
    
    /* Check if max has already been assigned. If not, assign pointX */
    if (max == 0.0f) {
        max = pointX;
    }
    
    /* Assign relative value by dividing by the max value */
    //value = originalValue / (max-min);
    
    return gradient;
    
}

//--------------------------------------------------------------------------------//
// GET SIGNAL
//--------------------------------------------------------------------------------//

float Algebraic::getSignal(float _value)
{
    
    float answer;
    
    /* Multiplies value with amplitude */
    answer = getWithAmplitude(_value);
    
    /* Add the signal onto the gradient & bezier */
    answer += getBezier();
    
    return answer;
    
}

float Algebraic::getSignal()
{
    
    return getBezier();
    
}

//--------------------------------------------------------------------------------//
// GET BEZIER
//--------------------------------------------------------------------------------//
/* This function uses the point used to determine the gradient, to instead
   interpolate along a bezier curve. The "x" value for the point influencing
   the curve is always halfway between 0.0f & pointX. It's "y" value is determined
   by the "BezierDepth" variable.
 */

float Algebraic::getBezier()
{
    
    /* Points needed for Bezier:
     float x1 = 0.0
     float x2 = pointX/2.0f
     float x3 = pointX
     float y1 = 0.0 */
     float y2 = (pointY/2.0f) + bezierDepth*(pointY/2.0f); /*
     float y3 = pointY
     */
    
    float valueRelative = value / pointX;
    float answer;
    
    /* Re-adjust linear trajectory for each step */
    
    //float xa = getBezierPt(0.0f, x2, value);
    float ya = getBezierPt(0.0f, y2, valueRelative);
    //float xb = getBezierPt(x2, pointX, value);
    float yb = getBezierPt(y2, pointY, valueRelative);
    
    /* Position */
    answer = getBezierPt(ya, yb, valueRelative);
    
    return answer;
    
}

//--------------------------------------------------------------------------------//

float Algebraic::getBezierPt(float n1, float n2, float perc)
{
    
    float difference = n2 - n1;
    
    return n1 + (difference * perc);
    
}

//--------------------------------------------------------------------------------//
// SET BEZIER DEPTH
//--------------------------------------------------------------------------------//

float Algebraic::setBezierDepth(float _depth)
{
    
    bezierDepth = _depth;
    
    return bezierDepth;
    
}

//--------------------------------------------------------------------------------//
// SET MIN
//--------------------------------------------------------------------------------//

float Algebraic::setMin(float _min)
{
    
    min = _min;
    
    return min;
    
}

//--------------------------------------------------------------------------------//
// SET MAX
//--------------------------------------------------------------------------------//

float Algebraic::setMax(float _max)
{
    
    max = _max;
    
    return max;
    
}

//--------------------------------------------------------------------------------//
// SET MIN & MAX
//--------------------------------------------------------------------------------//

float Algebraic::setMinMax(float _min, float _max)
{
    
    min = _min;
    max = _max;
    
    float difference = max - min;
    
    return difference;
    
}

//--------------------------------------------------------------------------------//
// GET WAVEFORM VALUE
//--------------------------------------------------------------------------------//

double Algebraic::getWaveformValue(int waveform)
{
    
    /* Check that entered int has assigned waveform */
    if (waveform < 0 || waveform > 5) {
        cout << "NO ALGEBRAIC WAVEFOROM FOR INPUT VALUE. RETURNING SINE \n";
        return getSine();
    }
    
    else {}
    
    switch (waveform) {
        case JEN_SINE: return getSine(); break;
        case JEN_SAW: return getSaw(); break;
        case JEN_SQUARE: return getSquare(); break;
        case JEN_NOISE: return getRandom(); break;
        case JEN_NOISE_WALK: return getNoiseWalk(); break;
        case JEN_GAUSSIAN: return getGaussian(); break;
            
        default: return getSine(); break;
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
