//
//  InstrumentEditor.cpp
//  jenMax
//
//  Created by Mitchell Nordine on 7/08/13.
//
//

#include "InstrumentEditor.h"

//--------------------------------------------------------------------------------//
// SETUP INSTRUMENT EDITOR
//--------------------------------------------------------------------------------//

ofxUICanvas* InstrumentEditor::setup(GUI *_gui, Library *_library)
{
    
    gui = _gui;
    guiGlobal = &gui->guiGlobal;
    library = _library;
    
    /* Sets up IEa & IEb GUI canvases */
    setupCanvases();
    
    /* Adds widgets to both canvases */
    addWidgets();
    
    /* Initialises Instrument Pointer */
    initialiseInst();
    
    /* Adds Listeners for all widgets */
    addListeners();
    
    return guiIEa;
    
}

//--------------------------------------------------------------------------------//
// SETUP CANVASES
//--------------------------------------------------------------------------------//

void InstrumentEditor::setupCanvases()
{
    
    /* Setup IEa */
    
    guiIEa = new ofxUICanvas(TAB_BAR_WIDTH,
                             0,
                             ofGetWidth()-TAB_BAR_WIDTH,
                             ofGetHeight());
    
    guiIEa->setVisible(true);
    guiIEa->setName("IEa");
    
    /* Setup IEb */
    
    guiIEb = new ofxUICanvas(TAB_BAR_WIDTH,
                             0,
                             ofGetWidth()-TAB_BAR_WIDTH,
                             ofGetHeight());
    
    guiIEb->setVisible(false);
    guiIEb->setName("IEb");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addWidgets()
{
    
    /* Add IEa Widgets */
    addCategorySelectWidgets();
    addInstrumentSelectWidgets();
    addInstrumentNameWidgets();
    addInstrumentDeleteWidgets();
    addIntensityWidgets();
    addSaveInstrumentWidgets();
    
    /* Add IEb Widgets */
    addDurationWidgets();
    addNumOfOscillatorsWidgets();
    addWaveformSelectWidgets();
    addEnvelopeEditorWidgets();
    addDrawInstrumentWaveformWidgets();
    
    
    
}

//--------------------------------------------------------------------------------//
// ADD LISTENERS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addListeners()
{
    
    /* Listen for IEa Widget events */
    ofAddListener(guiIEa->newGUIEvent, this,
                  &InstrumentEditor::guiEventsIEa);
    
    /* Listen for IEb Widget events */
    ofAddListener(guiIEb->newGUIEvent, this,
                  &InstrumentEditor::guiEventsIEb);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// RETURN 2ND IE CANVAS
//--------------------------------------------------------------------------------//

ofxUICanvas* InstrumentEditor::returnGuiIEb()
{
    
    return guiIEb;
    
}

//--------------------------------------------------------------------------------//
// ADD CATEGORY SELECT DROPDOWN MENU
//--------------------------------------------------------------------------------//

void InstrumentEditor::addCategorySelectWidgets()
{
    
    /* Initialise categories list */
    categories.clear();
    instrumentNames.clear();
    
    /* Setup categories list */
    categories.push_back("KIT");
    categories.push_back("BASS");
    categories.push_back("MELODIC");
    categories.push_back("CHORDAL");
    categories.push_back("ATMOS");
    
    /* JEN MAX | SONG INFORMATION */
    guiIEa->addWidgetDown(new ofxUILabel
                          ("JEN MAX | INSTRUMENT EDITOR A", OFX_UI_FONT_LARGE));
    
    /* SouthSpacer */
    guiIEa->addWidgetSouthOf(new ofxUISpacer
                             (0, 10, "JEN MAX | INSTRUMENT EDITOR A SOUTHSPACER"),
                             "JEN MAX | INSTRUMENT EDITOR A");
    
    /* Add Category Dropdown List */
    
    ddlCat = new ofxUIDropDownList ("CATEGORY SELECT", categories, 200, 0, 0,
                                    OFX_UI_FONT_MEDIUM);
    
    guiIEa->addWidgetSouthOf(ddlCat, "JEN MAX | INSTRUMENT EDITOR A SOUTHSPACER");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD INSTRUMENT SELECT WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addInstrumentSelectWidgets()
{
    
    instrumentNames.clear();
    //instrumentNames.reserve(100);
    instrumentNames.push_back("EMPTY");
    
    /* Spacer east of Category Dropdown List */
    guiIEa->addWidgetEastOf(new ofxUISpacer(5,0, "CATEGORY SELECT EASTSPACER"),
                            "CATEGORY SELECT");
    
    /* Add Instrument Dropdown List */
    ddlInst = new ofxUIDropDownList("INSTRUMENT SELECT",
                                               instrumentNames, 200, 0, 0,
                                               OFX_UI_FONT_MEDIUM);
    
    guiIEa->addWidgetEastOf(ddlInst, "CATEGORY SELECT EASTSPACER");
    
    //ddlInst->addToggle("EMPTY");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD INSTRUMENT NAME WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addInstrumentNameWidgets()
{
    
    guiIEa->addWidgetEastOf(new ofxUISpacer(5,0, "INSTRUMENT SELECT EASTSPACER"),
                            "INSTRUMENT SELECT");
    
    guiIEa->addWidgetEastOf(new ofxUILabel("INST. NAME", OFX_UI_FONT_MEDIUM),
                            "INSTRUMENT SELECT EASTSPACER");
    
    textInstName = new ofxUITextInput ("INSTRUMENT NAME", "INSTRUMENT NAME",
                                       200, 20, 0, 0, OFX_UI_FONT_SMALL);
    
    guiIEa->addWidgetSouthOf(textInstName, "INST. NAME");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD INSTRUMENT DELETE WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addInstrumentDeleteWidgets()
{
    
    guiIEa->addWidgetSouthOf(new ofxUISpacer(0,10, "INSTRUMENT NAME SOUTHSPACER"), "INSTRUMENT NAME");
    
    guiIEa->addWidgetSouthOf(new ofxUILabelButton("DELETE INST.", 300,200,
                                                  OFX_UI_FONT_SMALL),
                             "INSTRUMENT NAME SOUTHSPACER");
    
}

//--------------------------------------------------------------------------------//
// ADD INTENSITY WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addIntensityWidgets()
{
    
    /* Add Spacer */
    guiIEa->addWidgetSouthOf(new ofxUISpacer(0,10, "DELETE INST. SOUTHSPACER"),
                             "DELETE INST.");
    
    guiIEa->addWidgetSouthOf(new ofxUILabel("INTENSITY", OFX_UI_FONT_MEDIUM),
                             "DELETE INST. SOUTHSPACER");
    
    /* Add Intensity Slider */
    sliderIntensity = new ofxUISlider(140,16,0.0f,1.0f,0.5f,"INTENSITY SLIDER");
    
    guiIEa->addWidgetSouthOf(sliderIntensity, "INTENSITY");
    
    guiIEa->addWidgetSouthOf(new ofxUISpacer(0,10, "INTENSITY SLIDER SOUTHSPACER"), "INTENSITY SLIDER");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD SAVE INSTRUMENT WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addSaveInstrumentWidgets()
{
    
    /* Header */
    guiIEa->addWidgetSouthOf(new ofxUILabel("SAVE INSTRUMENT",
            OFX_UI_FONT_MEDIUM), "INTENSITY SLIDER SOUTHSPACER");
    
    guiIEa->addWidgetSouthOf(new ofxUITextArea
                             ("SAVE INSTRUMENT TEXT",
                              "This will save the current instrument as INST. NAME in selected category. If INST. NAME already exists, the associated instrument will be over-written.", 250.0f, 130.0f,
                              OFX_UI_FONT_SMALL_SIZE), "SAVE INSTRUMENT");
    
    guiIEa->addWidgetSouthOf(new ofxUILabelButton("SAVE INST.",300,200,
                                                  OFX_UI_FONT_SMALL),
                             "SAVE INSTRUMENT TEXT");
    
    guiIEa->addWidgetSouthOf(new ofxUISpacer(0,10,"SAVE INST. SOUTHSPACER"),
                             "SAVE INST.");
    
    /* Category Save Drop-Down Select */
    
    /* Initialise categories list */
    saveCategories.clear();
    
    /* Setup categories list */
    saveCategories.push_back("KIT");
    saveCategories.push_back("BASS");
    saveCategories.push_back("MELODIC");
    saveCategories.push_back("CHORDAL");
    saveCategories.push_back("ATMOS");
    
    ddlCatSave = new ofxUIDropDownList
            ("CAT. SAVE SELECT", saveCategories, 200, 0, 0, OFX_UI_FONT_MEDIUM);
    
    guiIEa->addWidgetEastOf(ddlCatSave, "SAVE INST. SOUTHSPACER");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD DURATION WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addDurationWidgets()
{
    
    /* JEN MAX | SONG INFORMATION */
    guiIEb->addWidgetDown(new ofxUILabel
                          ("JEN MAX | INSTRUMENT EDITOR B", OFX_UI_FONT_LARGE));
    
    /* SouthSpacer */
    guiIEb->addWidgetSouthOf(new ofxUISpacer
                             (0, 10, "JEN MAX | INSTRUMENT EDITOR B SOUTHSPACER"),
                             "JEN MAX | INSTRUMENT EDITOR B");
    
    guiIEb->addWidgetSouthOf(new ofxUILabel("DURATION", OFX_UI_FONT_MEDIUM),
                             "JEN MAX | INSTRUMENT EDITOR B SOUTHSPACER");
    
    /* Add Duration Dial */
    dialDuration = new ofxUINumberDialer(1.0, 20000.0f, 200.0f, 2,
                                         "DURATION DIAL", OFX_UI_FONT_SMALL);
    
    guiIEb->addWidgetSouthOf(dialDuration, "DURATION");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD NUMBER OF OSCILLATORS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addNumOfOscillatorsWidgets()
{
    
    guiIEb->addWidgetSouthOf(new ofxUISpacer(0,10, "DURATION DIAL SOUTHSPACER"),
                             "DURATION DIAL");
    
    /* Total number of oscillators */
    
    guiIEb->addWidgetSouthOf(new ofxUILabel
                             ("TOTAL OSCILLATORS", OFX_UI_FONT_MEDIUM), "DURATION DIAL SOUTHSPACER");
    
    dialTotalOscillators = new ofxUINumberDialer
            (1, MAX_OSCILLATORS, 1, 0, "TOTAL OSCILLATORS DIAL", OFX_UI_FONT_SMALL);
    
    guiIEb->addWidgetSouthOf(dialTotalOscillators, "TOTAL OSCILLATORS");
    
    guiIEb->addWidgetSouthOf(new ofxUISpacer(0,5,"TOTAL OSCILLATORS DIAL SOUTHSPACER"),
                             "TOTAL OSCILLATORS DIAL");
    
    /* Current selected oscillator */
    
    guiIEb->addWidgetSouthOf(new ofxUILabel
                             ("SELECTED OSCILLATOR", OFX_UI_FONT_MEDIUM),
                             "TOTAL OSCILLATORS DIAL SOUTHSPACER");
    
    dialSelectedOscillator = new ofxUINumberDialer
            (1, MAX_OSCILLATORS, 1, 0, "SELECTED OSCILLATOR DIAL", OFX_UI_FONT_SMALL);
    
    guiIEb->addWidgetSouthOf(dialSelectedOscillator, "SELECTED OSCILLATOR");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD WAVEFORM SELECT WIDGETS
//--------------------------------------------------------------------------------//

void InstrumentEditor::addWaveformSelectWidgets()
{
    
    waveforms.clear();
    
    waveforms.push_back("SINE");
    waveforms.push_back("SAW");
    waveforms.push_back("SQUARE");
    waveforms.push_back("NOISE");
    waveforms.push_back("NOISE_WALK");
    waveforms.push_back("GAUSSIAN");
    
    guiIEb->addWidgetSouthOf(new ofxUISpacer
                            (0,10, "SELECTED OSCILLATOR DIAL SOUTHSPACER"),
                            "SELECTED OSCILLATOR DIAL");
    
    /* Add Waveform Dropdown List */
    ddlWave = new ofxUIDropDownList
                ("WAVEFORM SELECT", waveforms, 200, 0, 0, OFX_UI_FONT_MEDIUM);
    
    guiIEb->addWidgetSouthOf(ddlWave, "SELECTED OSCILLATOR DIAL SOUTHSPACER");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD ENVELOPE EDITOR
//--------------------------------------------------------------------------------//

void InstrumentEditor::addEnvelopeEditorWidgets()
{
    
    guiIEb->addWidgetEastOf(new ofxUISpacer
                            (30,0, "JEN MAX | INSTRUMENT EDITOR B EASTSPACER"),
                             "JEN MAX | INSTRUMENT EDITOR B");
    
	guiIEb->addWidgetEastOf(new ofxUILabel("ENVELOPE EDITORS", OFX_UI_FONT_MEDIUM),
                             "JEN MAX | INSTRUMENT EDITOR B EASTSPACER");
    
    envAmp = new GuiEnvelope("AMP", ofPoint((120)*.5,120*.5), ENV_WIDTH, 300);
    envFreq = new GuiEnvelope("FREQ", ofPoint((120)*.5,120*.5), ENV_WIDTH, 300);
    
    guiIEb->addWidgetSouthOf(envAmp, "ENVELOPE EDITORS");
    guiIEb->addWidgetSouthOf(envFreq, "AMP");
    
    envFreq->isFrequency == true;
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD DRAW INSTRUMENT WAVEFORM
//--------------------------------------------------------------------------------//

void InstrumentEditor::addDrawInstrumentWaveformWidgets()
{
    
    guiIEb->addWidgetSouthOf(new ofxUISpacer(0,0, "FREQ SOUTHSPACER"),
                             "FREQ");
    
    instrumentWaveform = new ofxUISpacer(ENV_WIDTH, WAVEFORM_HEIGHT, "DRAW INSTRUMENT WAVEFORM");
    
    
    guiIEb->addWidgetSouthOf(instrumentWaveform, "FREQ SOUTHSPACER");
    
    realtimeToggle = new ofxUIToggle("REALTIME TOGGLE", true, 30, 30);
    
    guiIEb->addWidgetWestOf(realtimeToggle, "DRAW INSTRUMENT WAVEFORM");
    
    return;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
// GUI EVENTS FOR IE.A
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventsIEa(ofxUIEventArgs &e)
{
    
    guiEventCategorySelect(e);
    guiEventInstrumentSelect(e);
    guiEventInstrumentName(e);
    guiEventInstrumentDelete(e);
    guiEventIntensity(e);
    guiEventSaveInstrument(e);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS FOR IE.B
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventsIEb(ofxUIEventArgs &e)
{
    
    guiEventDuration(e);
    guiEventNumOfOscillators(e);
    guiEventWaveformSelect(e);
    guiEventRealtimeToggle(e);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - CATEGORY SELECT
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventCategorySelect(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "CATEGORY SELECT")
    {
        
        vector<ofxUIWidget *> &selected = ddlCat->getSelected();
        ddlCat->setShowCurrentSelected(true);
        ddlCat->setAutoClose(true);
        
        for (int i=0; i<selected.size(); i++) {
            
            for (int j=0; j<categories.size(); j++){
                
                /* Only do this for "category name" when "category name" is
                 selected and is different from already selected "category name" */
                if (selected.at(i)->getName() == categories.at(j) &&
                    selected.at(i)->getName() != currentCategory) {
                    
                    currentCategory = selected.at(i)->getName();
                    
                    /* Assigns "Save Category" dropdown to same as selected */
                    setCurrentSaveCategory(currentCategory);
                    
                    /* Initialises Instrument Pointer */
                    initialiseInst();
                    
                    /* Setup instruments map */
                    library->loadLibraryXML();
                    instruments.clear();
                    instruments =
                            library->getMapOfInstrumentPointers(currentCategory);
                    
                    /* Clears Instrument Dropdown List toggles */
                    ddlInst->clearToggles();
                    
                    /* Initialises currentInstrumentName to empty */
                    currentInstrumentName = "EMPTY";
                    
                    /* Initialise Instrument Name vector */
                    instrumentNames.clear();
                    instrumentNames.push_back("EMPTY");
                    
                    /* Adds each instrument found under category to name vector */
                    for (std::map<string,Instrument*>::iterator it=instruments.begin(); it!=instruments.end(); ++it) {
                        instrumentNames.push_back(it->first);
                    }
                    
                    /* Add a toggle to Inst dropdown for each instrument name */
                    ddlInst->addToggles(instrumentNames);
                    ddlInst->activateToggle("EMPTY");
                    
                    updateSample();
                    
                }
                
            } /* categories - j */
            
        } /* selected - i */
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - INSTRUMENT SELECT
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventInstrumentSelect(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "INSTRUMENT SELECT")
    {
        
        vector<ofxUIWidget *> &selected = ddlInst->getSelected();
        ddlInst->setShowCurrentSelected(true);
        ddlInst->setAutoClose(true);
        
        for (int i=0; i<selected.size(); i++) {
            
            for (int j=0; j<instrumentNames.size(); j++) {
                
                /* Only do this for "instrument name" when "instrument name" is
                 selected and is different from already selected "instrument name"*/
                if (selected.at(i)->getName() == instrumentNames.at(j) &&
                    selected.at(i)->getName() != currentInstrumentName) {
                    
                    currentInstrumentName = selected.at(i)->getName();
                    
                    setCurrentSaveCategory(currentCategory);
                    inst = instruments[currentInstrumentName];
                    initialiseOscillators();
                    setupOscillator();
                    adjustGUI(*inst);
                    updateSample();
                    
                }
                
            } /* instrumentNames - j */
            
            /* In the case that "EMPTY" is selected */
            if (selected.at(i)->getName() == "EMPTY"){
                currentInstrumentName = selected.at(i)->getName();
                initialiseInst();
                updateSample();
            }
            
        } /* selected - i */
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - INSTRUMENT NAME
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventInstrumentName(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "INSTRUMENT NAME")
    {
        
        if (textInstName->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER) {
            cout << "ON ENTER: \n";
        }
        else if (textInstName->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS) {
            cout << "ON FOCUS: \n";
        }
        else if (textInstName->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS) {
            cout << "ON BLUR: \n";
        }
        
        inst->name = textInstName->getTextString();

        cout << inst->name << endl;
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - INSTRUMENT DELETE
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventInstrumentDelete(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "DELETE INST.")
    {
        
        ofxUILabelButton *deleteInstButton = (ofxUILabelButton *) e.widget;
        
        /* Save when mouse released after pressing button */
        if (deleteInstButton->getValue() == 1) {
            
            library->deleteInstrumentFromXML(inst->name, currentCategory);
            
            cout << "Instrument '" + inst->name
            + "' has been deleted from " + currentCategory << endl;
            
            initialiseInst();
            
        }
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - DURATION
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventDuration(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "DURATION DIAL")
    {
        ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget;
        inst->duration.ms = dialer->getValue();
    }
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - INTENSITY
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventIntensity(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "INTENSITY SLIDER")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        inst->intensity = slider->getScaledValue();
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - TOTAL OSCILLATORS DIAL
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventNumOfOscillators(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "TOTAL OSCILLATORS DIAL")
    {
        
        inst->numOfOscillators = dialTotalOscillators->getValue();
        
        /* Check and adjust selected oscillator value to <= numOfOscillators */
        if (selectedOscillator > inst->numOfOscillators) {
            dialSelectedOscillator->setValue(inst->numOfOscillators);
            selectedOscillator = inst->numOfOscillators;
            setupOscillator();
        }
        
    }
    
    //------------------------------//
    
    if(e.widget->getName() == "SELECTED OSCILLATOR DIAL")
    {
        
        /* Check that selected oscillator is < numOfOscillators */
        if (dialSelectedOscillator->getValue() <= inst->numOfOscillators) {
            selectedOscillator = dialSelectedOscillator->getValue();
            setupOscillator();
        }
        
        /* If selected oscillator is > numOfOscillators, limit to max */
        else { dialSelectedOscillator->setValue(inst->numOfOscillators); }
        
    }
    
    
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - SAVE INSTRUMENT
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventSaveInstrument(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "SAVE INST.")
    {
        
        ofxUILabelButton *saveInstButton = (ofxUILabelButton *) e.widget;
        
        /* Save when mouse released after pressing button */
        if (saveInstButton->getValue() == 1) {
            if (currentSaveCategory != "") {
                library->deleteInstrumentFromXML(inst->name, currentSaveCategory);
                library->saveInstrumentToXML(inst, currentSaveCategory);
                cout << "Instrument '" + inst->name
                + "' Saved to " + currentSaveCategory << endl;
            }
        }
        
    }
    
    //------------------------------//
    
    if(e.widget->getName() == "CAT. SAVE SELECT")
    {
        
        vector<ofxUIWidget *> &selected = ddlCatSave->getSelected();
        ddlCatSave->setShowCurrentSelected(true);
        ddlCatSave->setAutoClose(true);
        
        for (int i=0; i<selected.size(); i++) {
            
            for (int j=0; j<saveCategories.size(); j++){
                
                /* Only do this for "currentSaveCategory" when "currentSaveCategory"
                 is selected and is different from already selected
                 "currentSaveCategory" */
                if (selected.at(i)->getName() == saveCategories.at(j) &&
                    selected.at(i)->getName() != currentSaveCategory) {
                    
                    currentSaveCategory = selected.at(i)->getName();
                    
                }
                
            } /* saveCategories - j */
            
        } /* selected - i */
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - WAVEFORM SELECT
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventWaveformSelect(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "WAVEFORM SELECT")
    {
        
        ofxUIDropDownList *ddlWave = (ofxUIDropDownList *) e.widget;
        
        vector<ofxUIWidget *> &selected = ddlWave->getSelected();
        ddlWave->setShowCurrentSelected(true);
        ddlWave->setAutoClose(true);
        
        for (int i=0; i<selected.size(); i++) {
            
            for (int j=0; j<waveforms.size(); j++) {
                
                /* Only do this for "waveform" when "waveform" is selected
                 and is different from already selected "waveform" */
                if (selected.at(i)->getName() == waveforms.at(j) &&
                    selected.at(i)->getName() != currentWaveform) {
                    
                    currentWaveform = selected.at(i)->getName();
                    
                    /* Assign selected waveform to current inst oscillator */
                    inst->oscillators.at(selectedOscillator-1).
                    getWaveformInt(currentWaveform);
                    
                }
                
            } /* waveforms - j */
            
        } /* selected - i */
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EVENTS - REALTIME TOGGLE
//--------------------------------------------------------------------------------//

void InstrumentEditor::guiEventRealtimeToggle(ofxUIEventArgs &e)
{
    
    if(e.widget->getName() == "REALTIME TOGGLE")
    {
        
        realtime = realtimeToggle->getValue();
        cout << realtime << endl;
        
    }
    
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
// SET CURRENT SAVE CATEGORY
//--------------------------------------------------------------------------------//

void InstrumentEditor::setCurrentSaveCategory(string categoryName)
{
    
    currentSaveCategory = categoryName;
    
    ddlCatSave->activateToggle(currentSaveCategory);
    ddlCatSave->setLabelText(currentSaveCategory);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SETUP OSCILLATOR
//--------------------------------------------------------------------------------//

void InstrumentEditor::setupOscillator()
{
    
    for (int i=0; i < inst->oscillators.size(); i++) {
        inst->oscillators.at(i).duration = &inst->duration;
        inst->oscillators.at(i).normaliser = &inst->normaliser;
    }
    
    assignSelectedOscillatorEnvelopes();
    assignSelectedOscillatorWaveform();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// INITIALISE OSCILLATORS
//--------------------------------------------------------------------------------//

void InstrumentEditor::initialiseOscillators()
{
    
    inst->oscillators.reserve(MAX_OSCILLATORS);
    
    int initialSize = inst->oscillators.size();
    
    for (int i=0; i < inst->oscillators.capacity() - initialSize; i++) {
        
        Oscillator *tempOscillator = new Oscillator;
        
        tempOscillator->setup(gui, &inst->duration, &inst->normaliser);
        tempOscillator->waveform = JEN_SINE;
        currentWaveform = tempOscillator->getWaveformString();
        tempOscillator->amplitude.addPoint(0.0f, 0.0f, 0.0f);
        tempOscillator->amplitude.addPoint(1.0f, 0.0f, 0.0f);
        tempOscillator->frequency.addPoint(0.0f, 0.0f, 0.0f);
        tempOscillator->frequency.addPoint(1.0f, 0.0f, 0.0f);
        
        inst->oscillators.push_back(*tempOscillator);
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ASSIGN SELECTED OSCILLATOR WAVEFORM
//--------------------------------------------------------------------------------//

void InstrumentEditor::assignSelectedOscillatorWaveform()
{
    
    /* Assign correct waveform to waveform dropdown */
    ddlWave->activateToggle(inst->oscillators.at(selectedOscillator-1).
                      getWaveformString());
    
    ddlWave->setLabelText(inst->oscillators.at(selectedOscillator-1).
                    getWaveformString());
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ASSIGN SELECTED OSCILLATOR ENVELOPES
//--------------------------------------------------------------------------------//

void InstrumentEditor::assignSelectedOscillatorEnvelopes()
{
    
    envAmp->setupEnvelope(&inst->oscillators.at(selectedOscillator-1).amplitude);
    
    envFreq->setupEnvelope(&inst->oscillators.at(selectedOscillator-1).frequency);
    envFreq->isFrequency = true;
    
    return;
    
}

//--------------------------------------------------------------------------------//
// INITIATE INSTRUMENT
//--------------------------------------------------------------------------------//

void InstrumentEditor::initialiseInst()
{
    
    inst = new Instrument;
    
    inst->name = "EMPTY";
    
    ddlInst->activateToggle(inst->name);
    ddlInst->setLabelText(inst->name);
    
    inst->duration.setup(gui);
    inst->duration.ms = 200.0f;
    
    inst->meanFrequency.setup(gui);
    
    inst->intensity = 0.5f;
    
    inst->numOfOscillators = 1;
    
    initialiseOscillators();
    
    adjustGUI(*inst);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADJUST GUI - (ACCORING TO SELECTED INSTRUMENT DATA)
//--------------------------------------------------------------------------------//

void InstrumentEditor::adjustGUI(Instrument instrument)
{
    
    /* Instrument Name */
    textInstName->setTextString(instrument.name);
    
    /* Duration */
    dialDuration->setValue(instrument.duration.ms);
    
    /* Intensity */
    sliderIntensity->setValue(instrument.intensity);
    
    /* Selected Oscillator */
    dialSelectedOscillator->setValue(1);
    selectedOscillator = 1;
    
    /* Total Number of Oscillators */
    dialTotalOscillators->setValue(instrument.numOfOscillators);
    
    /* Select Correct Waveform in Dropdownlist */
    assignSelectedOscillatorWaveform();
    
    /* Assign SELECTED OSCILLATOR envelope */
    assignSelectedOscillatorEnvelopes();
    
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



//--------------------------------------------------------------------------------//
// UPDATE INSTRUMENT WAVEFORM IN REAL TIME
//--------------------------------------------------------------------------------//

void InstrumentEditor::drawInstrumentWaveformRealtime()
{
    
    instrumentWaveform->setColorOutline(ofxUIColor(200, 200, 200, 200));
    instrumentWaveform->setColorFill(ofxUIColor(10, 10, 10, 150));
    instrumentWaveform->drawOutline();
    
    double ratio;
    double prevRatio;
    double value;
    double prevValue = 0.0;
    
    double currentX;
    double currentY;
    double previousX;
    double previousY;
    
    double xPos = (double)instrumentWaveform->getRect()->getX();
    double width = (double)ENV_WIDTH;
    
    double yPos = (double)instrumentWaveform->getRect()->getY();
    double height = (double)WAVEFORM_HEIGHT;
    
    Instrument instrument = *inst;
    int samples = instrument.duration.getSamples();
    
    
    for (int i=0; i < samples; i++) {
        
        ratio = (double)i / samples;
        value = instrument.getAmplitudeAtRatio(ratio)*instrument.normaliser;
        
        currentX = ratio * width + xPos;
        currentY = value * (height/2.1) + yPos + (height/2.0);
        previousX = prevRatio * width + xPos;
        previousY = prevValue * (height/2.1) + yPos + (height/2.0);
        
        ofCircle(currentX, currentY, 1);
        
        ofLine(previousX, previousY, currentX, currentY);
        
        prevValue = value;
        prevRatio = ratio;
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// DRAW INSTRUMENT WAVEFORM FUNCTION
//--------------------------------------------------------------------------------//

void InstrumentEditor::drawInstrumentWaveformFuntion()
{
    
    instrumentWaveform->setColorOutline(ofxUIColor(200, 200, 200, 200));
    instrumentWaveform->setColorFill(ofxUIColor(10, 10, 10, 150));
    instrumentWaveform->drawOutline();
    
    double ratio;
    
    double xPos = (double)instrumentWaveform->getRect()->getX();
    double width = (double)ENV_WIDTH;
    
    double yPos = (double)instrumentWaveform->getRect()->getY();
    double height = (double)WAVEFORM_HEIGHT;
    double halfHeight = height/2.0;
    double lessThanHalfHeight = height/2.1;
    
    double currentX;
    double currentY;
    double previousX;
    double previousY;
    
    Instrument instrument = *inst;
    
    for (int i=0; i < sample.size(); i++) {
        
        ratio = (double)i / sample.size();
        
        currentX = ratio * width + xPos;
        currentY = sample.at(i) * lessThanHalfHeight + yPos + halfHeight;
        
        ofCircle(currentX, currentY, 1);
        
        if (i == 0) {
            break;
        }
        
        previousX = ((double)(i-1)/sample.size()) * width + xPos;
        previousY = sample.at(i-1) * lessThanHalfHeight + yPos + halfHeight;
        
        ofLine(previousX, previousY, currentX, currentY);
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// UPDATE SAMPLE
//--------------------------------------------------------------------------------//

void InstrumentEditor::updateSample()
{
    
    double ratio;
    int size = inst->duration.getSamples();
    
    sample.clear();
    sample.reserve(size);
    for (int i=0; i<size; i++) {
        ratio = (double)i/(double)size;
        sample.push_back(inst->getAmplitudeAtRatio(ratio)*inst->normaliser);
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// DRAW
//--------------------------------------------------------------------------------//

void InstrumentEditor::draw()
{
    
    /* Checks that canvas is selected */
    if (guiIEb->isVisible()) {
        
        /* Checks toggle for drawing either real-time or post-mouseReleased */
        if (realtime == true) {
            drawInstrumentWaveformRealtime();
        }
        else if (realtime == false){
            drawInstrumentWaveformFuntion();
        }
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GUI EXIT
//--------------------------------------------------------------------------------//

void InstrumentEditor::exit()
{
	
    guiIEa->saveSettings("GUI/guiSettings.xml");
    delete guiIEa;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//
