//
//  ofVolume.cpp
//  synthesis
//
//  Created by Mitchell Nordine on 30/07/13.
//
//

#include "ofVolume.h"

void ofSoundEffectVolume::process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels )
{
	volume.rebuildRampIfNecessary();
	
	// loop through all the frames
	for ( int i=0; i<numFrames; i++ )
	{
		// write value to all the channels
		for ( int j=0; j<numOutChannels; j++ )
		{
			output[i*numOutChannels+j] = input[i*numInChannels+j] * volume.getDeclickedValue();
		}
		volume.frameTick();
	}
}
