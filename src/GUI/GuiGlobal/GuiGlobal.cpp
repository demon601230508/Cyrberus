//
//  GuiGlobal.cpp
//  Cyrberus
//
//  Created by Mitchell Nordine on 22/11/2013.
//
//

#include "GuiGlobal.h"

//--------------------------------------------------------------------------------//
// SETUP GUI GLOBAL (TEMPORARY TRANSPORT INPUT)
//--------------------------------------------------------------------------------//

GuiGlobal* GuiGlobal::setup()
{
    
    /* Makes the canvas */
    superCanvas = new ofxUISuperCanvas("GLOBAL DATA", TAB_BAR_WIDTH, ofGetHeight()*0.7f, 250, 500, OFX_UI_FONT_MEDIUM);
    
    /* Add all the widgets */
    addWidgets();
    
    /* Fit the canvas to the widgets */
    superCanvas->autoSizeToFitWidgets();
    
    /* Listen for super feels */
    ofAddListener(superCanvas->newGUIEvent, this, &GuiGlobal::addListeners);
    
    return this;
    
}

//--------------------------------------------------------------------------------//
// ADD WIDGETS
//--------------------------------------------------------------------------------//

void GuiGlobal::addWidgets()
{
    
    //------------------------------------//
    // HEADER
    //------------------------------------//
    
    superCanvas->addWidgetDown(new ofxUITextArea("GLOBAL DESCRIPTION", "This is used to temporarily represent input from the DAW or whatever.", 230.0f, 60.0f));
    
    //------------------------------------//
    // TEMPO
    //------------------------------------//
    
    /* Header */
    superCanvas->addWidgetSouthOf(new ofxUILabel("TEMPO", OFX_UI_FONT_MEDIUM), "GLOBAL DESCRIPTION");
    
    /* Dial */
    superCanvas->addWidgetSouthOf(new ofxUINumberDialer
                                  (1.0, 240.0, CYR_TEMPO, 2,"TEMPO DIAL", OFX_UI_FONT_SMALL),"TEMPO");
    
    superCanvas->addWidgetSouthOf(new ofxUISpacer(0,10,"TEMPO DIAL SOUTHSPACER"), "TEMPO DIAL");
    
    //------------------------------------//
    // TIME SIGNATURE
    //------------------------------------//
    
    /* Header */
    superCanvas->addWidgetSouthOf(new ofxUILabel("TIME SIGNATURE", OFX_UI_FONT_MEDIUM), "TEMPO DIAL SOUTHSPACER");
    
    /* Numerator Dial */
    superCanvas->addWidgetSouthOf(new ofxUINumberDialer(1, 12, 4, 0.25, "TIME SIG TOP", OFX_UI_FONT_SMALL), "TIME SIGNATURE");
    
    /* Denominator Dial */
    superCanvas->addWidgetSouthOf(new ofxUINumberDialer
                                  (4, 8, 4, 0.0625, "TIME SIG BOTTOM", OFX_UI_FONT_SMALL), "TIME SIG TOP");
    
    return;
    
}

//--------------------------------------------------------------------------------//
// ADD LISTENERS
//--------------------------------------------------------------------------------//

void GuiGlobal::addListeners(ofxUIEventArgs &e)
{
    
    //------------------------------------//
    // TEMPO
    //------------------------------------//
    
    if(e.widget->getName() == "TEMPO DIAL")
    {
        ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget;
        tempo = dialer->getValue();
    }
    
    //------------------------------------//
    // TIME SIGNATURE
    //------------------------------------//
    
    /* Numerator */
    
    if(e.widget->getName() == "TIME SIG TOP")
    {
        ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget;
        timeSig.first = dialer->getValue();
    }
    
    /* Denominator */
    
    if(e.widget->getName() == "TIME SIG BOTTOM")
    {
        ofxUINumberDialer *dialer = (ofxUINumberDialer *) e.widget;
        timeSig.second = dialer->getValue();
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