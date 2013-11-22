//
//  Position.h
//  jenMax
//
//  Created by Mitchell Nordine on 3/08/13.
//
//

#ifndef __jenMax__Position__
#define __jenMax__Position__

/* Header Includes */

#include "ofMain.h"
//#include "TimeLength.h"

/* Class */

class Position {
    
    public:
        
        /* Constructor */
        
        Position(){
            totalOccurences = 0;
            currentOccurence = 0;
            currentPosition = 0.0f;
        }
        
        /* Functions */
        
        void setup(int current, int *_total);
        float getCurrentPosition();
        
        /* Variable Declaration */
        
        int totalOccurences;
        int currentOccurence;
        float currentPosition;
        
        /* Class Instances */
        
        
        
};

#endif /* defined(__jenMax__Position__) */
