//
//  Envelope.h
//  jenMax
//
//  Created by Mitchell Nordine on 2/08/13.
//
//

#ifndef __jenMax__Envelope__
#define __jenMax__Envelope__

/* Header Includes */

#include "ofMain.h"
#include "Point.h"
#include "Algebraic.h"

bool pointCompare(Pt point1, Pt point2);

/* Class */

class Envelope {
    
public:
    
    /* Pointers */
    
    Envelope(){
        
    }
    
    /* Functions */
    
    void setup();
    void sortByPointTime();
    double getValue(double ratio);
    double interpolate(Pt start, Pt end);
    void addPoint(double time, double value, float curve);
    void addPoint(double time, double value);
    double convertToFrequency(double value);
    double convertToOriginal(double value);
    
    
    /* Variable Declaration */
    
    float ratio;
    
    vector<Pt> points;
    Algebraic algebraic;
    
};


#endif /* defined(__jenMax__Envelope__) */
