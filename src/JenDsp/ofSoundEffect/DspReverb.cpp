//
//  DspReverb.cpp
//  Cyrberus
//
//  Created by Joshua Batty on 23/11/13.
//
//

#include "DspReverb.h"

//--------------------------------------------------------------------------------//
// SETUP CATEGORY
//--------------------------------------------------------------------------------//

void DspReverb::setup(){
    reverb.setroomsize(verbRoomSize);
    reverb.setdamp(verbDamp);
    reverb.setwidth(verbWidth);
    reverb.setwet(wetness);
    reverb.setdry(1.0f - wetness);

}

//--------------------------------------------------------------------------------//
// SET ROOMSIZE
//--------------------------------------------------------------------------------//

void DspReverb::setRoomSize(float _value){
    verbRoomSize = _value;
    reverb.setroomsize(verbRoomSize);
}

//--------------------------------------------------------------------------------//
// SET DAMPING
//--------------------------------------------------------------------------------//

void DspReverb::setDamping(float _value){
    verbDamp = _value;
    reverb.setdamp(verbDamp);
}

//--------------------------------------------------------------------------------//
// SET STEREO WIDTH
//--------------------------------------------------------------------------------//

void DspReverb::setWidth(float _value){
    verbWidth = _value;
    reverb.setwidth(verbWidth);
}

//--------------------------------------------------------------------------------//
// SET WETNESS
//--------------------------------------------------------------------------------//

void DspReverb::setWet(float _value){
    wetness = _value;
    reverb.setwet(wetness);
}

//--------------------------------------------------------------------------------//
// SET DRYNESS
//--------------------------------------------------------------------------------//

void DspReverb::setDry(float _value){
    reverb.setdry(1.0f - wetness);
}

//--------------------------------------------------------------------------------//
// PROCESS!!!
//--------------------------------------------------------------------------------//

void DspReverb::process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels )
{
	
	// loop through all the frames
	for ( int i=0; i<numFrames; i++ )
	{

        //Pass left and right channels into reverb for processing
//        reverb.processreplace(&input[0], &input[1], &output[i*numOutChannels], &output[i*numOutChannels+1], numsamples, skip);
        
        //reverb.processmix(&input[0], &input[1], &output[0], &output[1], numsamples, skip);
        
       // cout << "after \n";
       // cout << input[0] << endl;
      //  cout << output[1] << endl;

		// write value to all the channels
		for ( int j=0; j<numOutChannels; j++ )
		{
            reverb.processreplace(&input[i*numInChannels], &input[i*numInChannels+j], &output[i*numOutChannels], &output[i*numOutChannels+j], numsamples, skip);

			//output[i*numOutChannels+j] = reverb.process(&input[0], &input[1], numsamples, skip);
            //	output[i*numOutChannels+j] += input[i*numInChannels+j];
		}
	}
}

