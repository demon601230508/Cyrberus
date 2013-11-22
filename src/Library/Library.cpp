//
//  Library.cpp
//  GenMax
//
//  Created by Mitchell Nordine on 22/10/13.
//
//

#include "Library.h"

//--------------------------------------------------------------------------------//
// SETUP LIBRARY
//--------------------------------------------------------------------------------//

void Library::setup(GUI *_gui, string _filePath)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    filePath = _filePath;
    
    loadLibraryXML(filePath);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// LOAD LIBRARY FROM XML "filePath"
//--------------------------------------------------------------------------------//

Library* Library::loadLibraryXML(string _filePath)
{
    
    filePath = _filePath;
    
    /* Initialise instrumentNames list */
    categoryList.clear();
    
    /* Load XML file */
    if (xmlData.loadFile(filePath)) { cout << "Library loaded!\n"; }
    else { cout << "unable to load library.xml check data/ folder\n"; }
    
    /* Iterate through cataegories */
    for (int i=0; i<xmlData.getNumTags("CATEGORY"); i++) {
        
        xmlData.pushTag("CATEGORY", i);
        
        /* Assign category data */
        Category *tempCat = new Category;
        tempCat->setup(gui);
        categoryList.push_back(*tempCat);
        categoryList.at(i).name = xmlData.getValue("NAME", "");
        
        /* Iterate through all instrumentNames in category */
        for (int j=0; j<xmlData.getNumTags("INSTRUMENT"); j++) {
            
            xmlData.pushTag("INSTRUMENT", j);
            
            /* Use temporary instrument */
            Instrument *temp = new Instrument;
            
            /* Get name */
            temp->name = xmlData.getValue("NAME", "NO_NAME");
            
            /* Get duration */
            temp->duration.setup(gui);
            temp->duration.ms = xmlData.getValue("DURATION", 0);
            
            /* Get intensity */
            temp->intensity = xmlData.getValue("INTENSITY", 0.0f);
            
            /* Get Analysis Data */
            temp->normaliser = xmlData.getValue("NORMALISER", 1.0);
            temp->loudness = xmlData.getValue("LOUDNESS", 0.0);
            temp->meanFrequency.setup(gui);
            temp->meanFrequency.setFrequencyRatio
                                    (xmlData.getValue("MEANFREQUENCY", 0.0));
            temp->noiseyness = xmlData.getValue("NOISEYNESS", 0.0);
            temp->duration.focalPoint.positions.push_back
                            (xmlData.getValue("FOCALPOINT", 0.0));
            
            cout << temp->name + "'s Normaliser = "
            + ofToString(temp->normaliser) << endl;
            
            /* Oscillators */
            
            temp->numOfOscillators = xmlData.getNumTags("OSCILLATOR");
            
            for (int k=0; k<temp->numOfOscillators; k++) {
                
                Oscillator *tempOscillator = new Oscillator;
                tempOscillator->setup(gui, &temp->duration, &temp->normaliser);
                
                /* Setup oscillator */
                xmlData.pushTag("OSCILLATOR", k);
                
                tempOscillator->getWaveformInt(xmlData.getValue("WAVEFORM","SINE"));
                
                /* Setup amplitude envelope vector */
                xmlData.pushTag("AMPLITUDE");
                
                int numPoints = xmlData.getNumTags("PT");
                
                if (numPoints > 0) {
                    
                    tempOscillator->amplitude.points.clear();
                    
                    for (int l=0; l < numPoints; l++) {
                        
                        Pt *Ptr = new Pt;
                        
                        Ptr->setup(xmlData.getValue("PT:TIME", 0.0, l),
                                   xmlData.getValue("PT:VALUE", 0.0, l),
                                   xmlData.getValue("PT:CURVE", 0.0, l));
                        
                        tempOscillator->amplitude.points.push_back(*Ptr);
                        
                    }
                    
                    numPoints = 0;
                    
                }
                
                xmlData.popTag(); /* AMPLITUDE */
                
                /* Setup frequency envelope vector */
                xmlData.pushTag("FREQUENCY");
                
                numPoints = xmlData.getNumTags("PT");
                
                if (numPoints > 0) {
                    
                    tempOscillator->frequency.points.clear();
                    
                    for (int l=0; l < numPoints; l++) {
                        
                        Pt *Ptr = new Pt;
                        
                        Ptr->time = xmlData.getValue("PT:TIME", 0.0, l);
                        Ptr->value = xmlData.getValue("PT:VALUE", 0.0, l);
                        Ptr->curve = xmlData.getValue("PT:CURVE", 0.0, l);
                        
                        tempOscillator->frequency.points.push_back(*Ptr);
                        
                    }
                    
                    numPoints = 0;
                    
                }
                
                xmlData.popTag(); /* FREQUENCY */
                
                xmlData.popTag(); /* OSCILLATOR */
                
                temp->oscillators.push_back(*tempOscillator);
                
            } /* Oscillators */
            
            /* Perform instrument analysis */
            //temp->analyseInstrument();
            
            /* Place in Libraries instrumentList */
            instrumentList.push_back(*temp);
            
            /* Push instrument into instrumentList */
            categoryList.at(i).instrumentList.push_back(temp);
            
            xmlData.popTag(); /* INSTRUMENT */
            
        } /* Instruments */
        
        /* Category Loudness Comparison */
        categoryList.at(i).instrumentRelativity();
        
        xmlData.popTag(); /* CATEGORY */
        
    } /* Categories */
    
    /* Total Library Loudness Comparison */
    //loudnessComparison();
    
    printLibraryData();
    
    return this;
    
}

Library* Library::loadLibraryXML()
{
    
    return loadLibraryXML(filePath);
    
}

//--------------------------------------------------------------------------------//
// GENERATE INSTRUMENT MAP (FROM SELECTED CATEGORY)
//--------------------------------------------------------------------------------//

map<string, Instrument*> Library::getMapOfInstrumentPointers(string categoryName)
{
    
    instruments.clear();
    vector<Instrument*>* instList;
        
    for (int i=0; i < categoryList.size(); i++) {
        
        if (categoryList.at(i).name == categoryName) {
            
            instList = &categoryList.at(i).instrumentList;
            
            for (int j=0; j < instList->size(); j++) {
                instruments[instList->at(j)->name] = instList->at(j);
            }
            
        }
        
    }
    
    return instruments;
    
}

//--------------------------------------------------------------------------------//
// GET VECTOR OF INSTRUMENT POINTERS FOR "CATEGORY NAME"
//--------------------------------------------------------------------------------//

vector<Instrument*> Library::getVectorOfInstrumentPointers(string categoryName)
{
    
    vector<Instrument*> instPtrList;
    
    for (int i=0; i < categoryList.size(); i++) {
        
        if (categoryList.at(i).name == categoryName) {
            
            instPtrList = categoryList.at(i).getVectorOfInstrumentPointers();
            
        }
        
    }
    
    return instPtrList;
    
}

//--------------------------------------------------------------------------------//
// SAVE CURRENT INSTRUMENT (INST) TO XML
//--------------------------------------------------------------------------------//

void Library::saveInstrumentToXML(Instrument *inst, string catName)
{
    
    /* Load XML file */
    if (xmlData.loadFile("library.xml")) { cout << "library.xml loaded!\n"; }
    else { cout << "unable to load library.xml check data/ folder\n"; }
    
    inst->analyseInstrument();
    
    bool isFound = false;
    
    for (int i=0; i<xmlData.getNumTags("CATEGORY"); i++) {
        
        if (xmlData.getValue("CATEGORY:NAME", "", i) == catName) {
            
            xmlData.pushTag("CATEGORY", i);
            
            cout << "IN CATEGORY "
            + ofToString(catName) + " with this number of insts: "
            + ofToString(xmlData.getNumTags("INSTRUMENT"))
            << endl;
            
            insertInstrumentDataIntoXML(inst, xmlData.getNumTags("INSTRUMENT"));
            
            xmlData.popTag(); /* Category */
            
        }
        
    }
    
    
    
}

//--------------------------------------------------------------------------------//
// INSERT INSTRUMENT DATA INTO XML
//--------------------------------------------------------------------------------//

void Library::insertInstrumentDataIntoXML(Instrument *inst, int numOfInsts)
{
    
    xmlData.addTag("INSTRUMENT");
    
    xmlData.pushTag("INSTRUMENT", numOfInsts);
    
    /* Set Name */
    xmlData.addTag("NAME");
    xmlData.setValue("NAME", inst->name);
    
    /* Set Duration */
    xmlData.addTag("DURATION");
    xmlData.setValue("DURATION", inst->duration.ms);
    
    /* Set Intensity */
    xmlData.addTag("INTENSITY");
    xmlData.setValue("INTENSITY", inst->intensity);
    
    /* Set Normaliser */
    xmlData.addTag("NORMALISER");
    xmlData.setValue("NORMALISER", inst->normaliser);
    
    /* Set Loudness */
    xmlData.addTag("LOUDNESS");
    xmlData.setValue("LOUDNESS", inst->loudness);
    
    /* Set Mean Frequency */
    xmlData.addTag("MEANFREQUENCY");
    xmlData.setValue("MEANFREQUENCY", inst->meanFrequency.frequencyRatio);
    
    /* Set Noiseyness */
    xmlData.addTag("NOISEYNESS");
    xmlData.setValue("NOISEYNESS", inst->noiseyness);
    
    /* Set Focal Point */
    xmlData.addTag("FOCALPOINT");
    xmlData.setValue("FOCALPOINT", inst->duration.focalPoint.positions.at(0));
    
    for (int i=0; i < inst->numOfOscillators; i++) {
        
        xmlData.addTag("OSCILLATOR");
        
        xmlData.pushTag("OSCILLATOR", i);
        
        /* Set Waveform */
        xmlData.addTag("WAVEFORM");
        xmlData.setValue("WAVEFORM", inst->oscillators.at(i).getWaveformString());
        
        /* Set Amplitude Envelope */
        xmlData.addTag("AMPLITUDE");
        
        xmlData.pushTag("AMPLITUDE");
        
        for (int j=0; j < inst->oscillators.at(i).amplitude.points.size(); j++) {
            
            /* Set Point */
            xmlData.addTag("PT");
            xmlData.pushTag("PT", j);
            
            /* Set Point Time */
            xmlData.addTag("TIME");
            xmlData.setValue("TIME",
                             inst->oscillators.at(i).amplitude.points.at(j).time);
            
            /* Set Point Value */
            xmlData.addTag("VALUE");
            xmlData.setValue("VALUE",
                             inst->oscillators.at(i).amplitude.points.at(j).value);
            
            /* Set Point Curve */
            xmlData.addTag("CURVE");
            xmlData.setValue("CURVE",
                             inst->oscillators.at(i).amplitude.points.at(j).curve);
            
            xmlData.popTag(); /* PT */
            
        }
        
        xmlData.popTag(); /* Amplitude */
        
        /* Set Frequency Envelope */
        xmlData.addTag("FREQUENCY");
        
        xmlData.pushTag("FREQUENCY");
        
        for (int j=0; j < inst->oscillators.at(i).frequency.points.size(); j++) {
            
            /* Set Point */
            xmlData.addTag("PT");
            xmlData.pushTag("PT", j);
            
            /* Set Point Time */
            xmlData.addTag("TIME");
            xmlData.setValue("TIME",
                             inst->oscillators.at(i).frequency.points.at(j).time);
            
            /* Set Point Value */
            xmlData.addTag("VALUE");
            xmlData.setValue("VALUE",
                             inst->oscillators.at(i).frequency.points.at(j).value);
            
            /* Set Point Curve */
            xmlData.addTag("CURVE");
            xmlData.setValue("CURVE",
                             inst->oscillators.at(i).frequency.points.at(j).curve);
            
            xmlData.popTag(); /* PT */
            
        }
        
        xmlData.popTag(); /* Frequency */
        
        xmlData.popTag(); /* Oscillator */
        
    }
    
    xmlData.popTag(); /* Instrument */
    
    xmlData.saveFile();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// DELETE CURRENT INSTRUMENT (with name inst->instrumentName) FROM XML
//--------------------------------------------------------------------------------//

void Library::deleteInstrumentFromXML(string instName, string catName)
{
    
    /* Load XML file */
    if (xmlData.loadFile("library.xml")) { cout << "library.xml loaded!\n"; }
    else { cout << "unable to load library.xml check data/ folder\n"; }
    
    bool isFound = false;
    
    for (int i=0; i<xmlData.getNumTags("CATEGORY") && isFound == false; i++) {
        
        xmlData.pushTag("CATEGORY", i);
        
        if (xmlData.getValue("NAME", "NO_NAME") == catName) {
            
            /* Iterate through all instrumentNames in category */
            for (int j=0; j<xmlData.getNumTags("INSTRUMENT")
                 && isFound == false; j++) {
                
                if (xmlData.getValue("INSTRUMENT:NAME", "", j) == instName) {
                    
                    /* Instrument Deletion */
                    xmlData.removeTag("INSTRUMENT", j);
                    
                    isFound = true;
                }
                
                else {}
                
            }
            
        }
        
        xmlData.popTag(); /* Category */
        
    }
    
    xmlData.saveFile();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// LOUDNESS COMPARISON
//--------------------------------------------------------------------------------//

void Library::loudnessComparison()
{
    
    double highestLoudness = 0.0;
    double highestNoiseyness = 0.0;
    double loudnessMultiplier;
    double noiseynessMultiplier;
    vector<Instrument*> *instList;
    
    for (int i=0; i < categoryList.size(); i++) {
        
        instList = &categoryList.at(i).instrumentList;
        
        for (int j=0; j < instList->size(); j++) {
            
            if (instList->at(j)->loudness > highestLoudness) {
                highestLoudness = instList->at(j)->loudness;
            }
            
            if (instList->at(j)->noiseyness > highestNoiseyness) {
                highestNoiseyness = instList->at(j)->noiseyness;
            }
            
        }
        
    }
    
    loudnessMultiplier = 1.0 / highestLoudness;
    noiseynessMultiplier = 1.0 / highestNoiseyness;
    
    /* Set relativity */
    for (int i=0; i < categoryList.size(); i++) {
        
         instList = &categoryList.at(i).instrumentList;
        
        for (int j=0; j < instList->size(); j++) {
            
            instList->at(j)->relativeLoudness
                = instList->at(j)->loudness * loudnessMultiplier;
            
            instList->at(j)->relativeNoiseyness
                = instList->at(j)->noiseyness * noiseynessMultiplier;
            
        }
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// LOUDNESS COMPARISON (FOR CATEGORY)
//--------------------------------------------------------------------------------//

void Library::instrumentRelativity(Category *category)
{
    
    category->instrumentRelativity();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// PRINT LIBRARY DATA
//--------------------------------------------------------------------------------//

void Library::printLibraryData()
{
    
    for (int i=0; i < categoryList.size(); i++) {
        
        categoryList.at(i).printCategoryData();
        
    }
    
    cout << "\n\t--- END LIBRARY DATA ---\n";
    
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