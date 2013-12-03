//
//  DspPhasor.cpp
//  Cyrberus
//
//  Created by Joshua Batty on 25/11/13.
//
//

#include "DspPhasor.h"

//--------------------------------------------------------------------------------//
// SETUP PHASOR
//--------------------------------------------------------------------------------//

void DspPhasor::setup(){
    
}

//--------------------------------------------------------------------------------//
// SET RANGE
//--------------------------------------------------------------------------------//

void DspPhasor::setRange(float fMin, float fMax){
    phasor.Range(fMin, fMax);
}

//--------------------------------------------------------------------------------//
// SET RATE
//--------------------------------------------------------------------------------//

void DspPhasor::setRate(float rate){
    phasor.Rate(rate);
}

//--------------------------------------------------------------------------------//
// SET FEEDBACK
//--------------------------------------------------------------------------------//

void DspPhasor::setFeedback(float fb){
    feedback = fb;
    phasor.Feedback(feedback);
}

//--------------------------------------------------------------------------------//
// SET DEPTH
//--------------------------------------------------------------------------------//

void DspPhasor::setDepth(float depth){
    phasor.Depth(depth);
}

//--------------------------------------------------------------------------------//
// PROCESS!!!
//--------------------------------------------------------------------------------//

void DspPhasor::process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels )
{
	
	// loop through all the frames
	for ( int i=0; i<numFrames; i++ )
	{
		for ( int j=0; j<numOutChannels; j++ )
		{
			output[i*numOutChannels+j] = phasor.Update(input[i*numInChannels+j]);
            //output[i*numOutChannels+j] += input[i*numInChannels+j];
		}
	}
}

