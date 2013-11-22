//
//  InstrumentEditor.h
//  jenMax
//
//  Created by Mitchell Nordine on 7/08/13.
//
//

#ifndef __jenMax__InstrumentEditor__
#define __jenMax__InstrumentEditor__

/* Header Includes */

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
#include "Library.h"

#define KIT 0
#define BASS 1
#define MELODIC 2
#define CHORDAL 3
#define ATMOS 4

#define TAB_BAR_WIDTH 80

#define MAX_OSCILLATORS 10

#define ENV_WIDTH 900

#define WAVEFORM_HEIGHT 166

/* Class */

class InstrumentEditor {
    
public:
    
    /* Constructors & Destructors */
    
    InstrumentEditor(){
        
    }
    
    ~InstrumentEditor(){
        
    }
    
    /* Functions */
    
    ofxUICanvas* setup(GUI *_gui, Library *_library);
    ofxUICanvas* returnGuiIEb();
    void setupCanvases();
    void addWidgets();
    void addListeners();
    
    /* Add IEa Widgets */
    
    void addCategorySelectWidgets();
    void addInstrumentSelectWidgets();
    void addInstrumentNameWidgets();
    void addInstrumentDeleteWidgets();
    void addIntensityWidgets();
    void addSaveInstrumentWidgets();
    
    /* Add IEb Widgets */
    void addDurationWidgets();
    void addNumOfOscillatorsWidgets();
    void addWaveformSelectWidgets();
    void addEnvelopeEditorWidgets();
    
    /* Draw Waveform */
    void addDrawInstrumentWaveformWidgets();
    void drawInstrumentWaveformRealtime();
    void drawInstrumentWaveformFuntion();
    void updateSample();
    
    /* Check for widget events */
    void guiEventsIEa(ofxUIEventArgs &e);
    void guiEventsIEb(ofxUIEventArgs &e);
    
    void guiEventCategorySelect(ofxUIEventArgs &e);
    void guiEventInstrumentSelect(ofxUIEventArgs &e);
    void guiEventInstrumentName(ofxUIEventArgs &e);
    void guiEventInstrumentDelete(ofxUIEventArgs &e);
    void guiEventIntensity(ofxUIEventArgs &e);
    void guiEventSaveInstrument(ofxUIEventArgs &e);
    
    void guiEventDuration(ofxUIEventArgs &e);
    void guiEventNumOfOscillators(ofxUIEventArgs &e);
    void guiEventWaveformSelect(ofxUIEventArgs &e);
    void guiEventRealtimeToggle(ofxUIEventArgs &e);
    
    /* Other functions */
    void initialiseInst();
    void adjustGUI(Instrument instrument);
    void assignSelectedOscillatorEnvelopes();
    void assignSelectedOscillatorWaveform();
    void adjustOscillatorVectorSize();
    void initialiseOscillators();
    void setupOscillator();
    void setCurrentSaveCategory(string categoryName);
    
    void oscillatorErrorCheck();
    
    void draw();
    void exit();
    
    /* Variable Declaration */
    
    int selectedOscillator;
    string categoryOfDeletion;
    
    /* These variablese are for drop down menu select checks */
    string currentCategory;
    vector<string> categories;
    string currentSaveCategory;
    vector<string> saveCategories;
    string currentInstrumentName;
    vector<string> instrumentNames;
    string currentWaveform;
    vector<string> waveforms;
    
    /* Canvas Pointers */
    
    ofxUICanvas *guiIEa;
    ofxUICanvas *guiIEb;
    
    /* Widget Pointers */
    
    GuiEnvelope *envAmp;
    GuiEnvelope *envFreq;
    ofxUIDropDownList *ddlInst;
    ofxUIDropDownList *ddlCat;
    ofxUIDropDownList *ddlCatSave;
    ofxUIDropDownList *ddlWave;
    ofxUITextInput *textInstName;
    ofxUISlider *sliderIntensity;
    ofxUISlider *sliderJS;
    ofxUISlider *sliderTD;
    ofxUISlider *sliderFA;
    ofxUISlider *sliderSA;
    ofxUINumberDialer *dialDuration;
    ofxUINumberDialer *dialTotalOscillators;
    ofxUINumberDialer *dialSelectedOscillator;
    
    ofxUISpacer *instrumentWaveform;
    ofxUIToggle *realtimeToggle;
    vector<double> sample;
    bool realtime = true;
    bool waitForDraw;
    
    /* Class Pointers */
    
    map<string, Instrument*> instruments;
    Instrument *inst;
    GUI *gui;
    GuiGlobal *guiGlobal;
    Library *library;
    //ofxXmlSettings *xmlData;
    
};

#endif /* defined(__jenMax__InstrumentEditor__) */
