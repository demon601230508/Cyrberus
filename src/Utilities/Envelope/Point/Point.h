//
//  Point.h
//  jenMax
//
//  Created by Mitchell Nordine on 7/08/13.
//
//

#ifndef __jenMax__Point__
#define __jenMax__Point__

/* Header Includes */

#include "ofMain.h"

/* Class */

class Pt {
    
public:
    
    /* Constructor */
    
    Pt()   {time;
            value;
            curve = 0.0f;
    }
    
    /* Functions */
    
    void setup(float _time, float _value, float _curve);
    
    /* Variable Declaration */
    
    float time;
    float value;
    float curve;
    
    /* Class Instances */
    
    
    
};

#endif /* defined(__jenMax__Point__) */
