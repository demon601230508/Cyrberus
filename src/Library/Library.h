//
//  Library.h
//  GenMax
//
//  Created by Mitchell Nordine on 22/10/13.
//
//

#ifndef __GenMax__Library__
#define __GenMax__Library__

#define NUM_OF_CATEGORIES 6

/* Header Includes */

#include "ofMain.h"
#include "Category.h"
#include "ofxXmlSettings.h"
#include "GUI.h"

/* Class */

class Library {
    
public:
    
    /* Constructors & Destructors */
    
    Library(){
        
    }
    
    ~Library(){
        
    }
    
    /* Functions */
    
    void setup(GUI *_gui, string _filePath);
    Library* loadLibraryXML(string _filePath);
    Library* loadLibraryXML();
    map<string, Instrument*> getMapOfInstrumentPointers(string categoryName);
    vector<Instrument*> getVectorOfInstrumentPointers(string categoryName);
    void saveInstrumentToXML(Instrument *inst, string catName);
    void insertInstrumentDataIntoXML(Instrument *inst, int numOfInsts);
    void deleteInstrumentFromXML(string instName, string catName);
    void loudnessComparison();
    void instrumentRelativity(Category *category);
    void printLibraryData();
    
    /* Variable Declaration */
    
    vector<Instrument> instrumentList;
    vector<Category> categoryList;
    ofxXmlSettings xmlData;
    map<string, Instrument*> instruments;
    string filePath;
    
    /* Class Instances */
    
    GUI *gui;
    GuiGlobal *guiGlobal;
    
};

#endif /* defined(__GenMax__Library__) */
