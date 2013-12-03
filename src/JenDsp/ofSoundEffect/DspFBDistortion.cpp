//
//  DspFBDistortion.cpp
//  Cyrberus
//
//  Created by Joshua Batty on 25/11/13.
//
//

#include "DspFBDistortion.h"


//--------------------------------------------------------------------------------//
// SETUP REDUX
//--------------------------------------------------------------------------------//

void DspFBDistortion::setup(){
    
}

//--------------------------------------------------------------------------------//
// SET DISTORTION THRESHOLD
//--------------------------------------------------------------------------------//

void DspFBDistortion::setThreshold(float _value){
    threshold = _value;
}

//--------------------------------------------------------------------------------//
// PROCESS!!!
//--------------------------------------------------------------------------------//

void DspFBDistortion::process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels )
{
	
	// loop through all the frames
	for ( int i=0; i<numFrames; i++ )
	{
		for ( int j=0; j<numOutChannels; j++ )
		{
			output[i*numOutChannels+j] = distortion.foldback(input[i*numInChannels+j], threshold);
            //output[i*numOutChannels+j] += input[i*numInChannels+j];
		}
	}
}

