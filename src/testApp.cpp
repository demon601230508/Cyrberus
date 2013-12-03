#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    /* Setup GUI */
    gui.setup();
    
    /* Setup Library */
    library.setup(&gui, libraryFilePath);
    
    /* Setup Instrument Editor */
    gui.guiTabBar->addCanvas(instrumentEditor.setup(&gui, &library));
    gui.guiTabBar->addCanvas(instrumentEditor.returnGuiIEb());
    
    /* Setup JenDSP */
    jenDsp.setup(&instrumentEditor);
    
    /* soundStream setup (audio playback begins as soon as this is called!) */
    soundStream.setup(this, 2, 0, gui.guiGlobal.sampleRate,
                      gui.guiGlobal.bufferSize, 4);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    /* Play instrumentEditor Oscillator with "P"*/
    if( key == 'p'){
        
        clock_t time1 = clock();
        
        /* This determines the instrument's normaliser */
        //instrumentEditor.inst->getNormaliser();
        
        //instrumentEditor.inst->analyseInstrument();
        //instrumentEditor.inst->printAnalysisData();
        //instrumentEditor.updateSample();
        
        jenDsp.updateInstrumentEditorChannels();
        instrumentEditor.inst->play();
        
        clock_t difference = clock() - time1;
        
        cout << "Time Taken = " + ofToString((float)difference / CLOCKS_PER_SEC)
        << endl;
        
    }
    
    return;
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------------------------//
// AUDIO OUTPUT
//--------------------------------------------------------------------------------//

void testApp::audioOut(float *output, int bufferSize, int nChannels)
{
    
    jenDsp.soundMixer.audioRequested(output, bufferSize, nChannels);
    
    return;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//
