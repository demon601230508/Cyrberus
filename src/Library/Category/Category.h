//
//  Category.h
//  jenMax
//
//  Created by Mitchell Nordine on 3/08/13.
//
//

#ifndef __jenMax__Category__
#define __jenMax__Category__

#define KIT 0
#define BASS 1
#define MELODIC 2
#define CHORDAL 3
#define ATMOS 4

/* Header Includes */

#include "ofMain.h"
#include "Instrument.h"
#include "GUI.h"

/* Class */

class Category {
    
public:
    
    /* Constructors & Destructors */
    
    Category(){
        numOfInstruments = 0;
        rawWeight = 0.0f;
        percentageWeight = 0.0f;
    }
    
    ~Category(){
        
    }
    
    /* Functions */
    
    void setup(GUI *_gui);
    void setName(string _name);
    void setIntID(int ID);
    string getName(int categoryInt);
    int getInt(string categoryName);
    vector<Instrument*> getVectorOfInstrumentPointers();
    void instrumentRelativity();
    void getNumOfInstruments(int totalNumOfInstruments);
    void setDurationScale();
    void printCategoryData();
    
    /* Variable Declaration */
    
    string name;
    int integer;
    int numOfInstruments;
    int numOfDurationRanges;
    float rawWeight, percentageWeight;
    vector<Instrument*> instrumentList;
    
    TimeLength durationScale;
    
    /* Class Instances */
    
    GUI *gui;
    GuiGlobal *guiGlobal;
    
};

#endif /* defined(__jenMax__Category__) */
