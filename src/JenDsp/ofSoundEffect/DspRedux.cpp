//
//  DspRedux.cpp
//  Cyrberus
//
//  Created by Joshua Batty on 25/11/13.
//
//

#include "DspRedux.h"


//--------------------------------------------------------------------------------//
// SETUP REDUX
//--------------------------------------------------------------------------------//

void DspRedux::setup(){
    redux.setValues(bits, rate);
    
}

//--------------------------------------------------------------------------------//
// SET BIT DEPTH
//--------------------------------------------------------------------------------//

void DspRedux::setBits(float _value){
    bits = _value;
    redux.setValues(bits, rate);
}

//--------------------------------------------------------------------------------//
// SET DOWNSAMPLE AMOUNT
//--------------------------------------------------------------------------------//

void DspRedux::setRate(float _value){
    rate = _value;
    redux.setValues(bits, rate);
}

//--------------------------------------------------------------------------------//
// PROCESS!!!
//--------------------------------------------------------------------------------//

void DspRedux::process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels )
{
	
	// loop through all the frames
	for ( int i=0; i<numFrames; i++ )
	{
		for ( int j=0; j<numOutChannels; j++ )
		{
			output[i*numOutChannels+j] = redux.decimate(input[i*numInChannels+j]);
            //output[i*numOutChannels+j] += input[i*numInChannels+j];
		}
	}
}

