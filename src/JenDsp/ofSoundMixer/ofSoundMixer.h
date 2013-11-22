//
//  ofSoundMixer.h
//  synthesis
//
//  Created by Mitchell Nordine on 30/07/13.
//
//

#ifndef __synthesis__ofSoundMixer__
#define __synthesis__ofSoundMixer__

#include "ofSoundEffect.h"

/** ofSoundMixer
 
 Mixes together inputs from multiple ofSoundSources.
 
 @author damian
 */

class ofSoundMixer : public ofSoundSink, public ofSoundSource
{
public:
	ofSoundMixer() { working = NULL; masterVolume = 1.0f; }
	ofSoundMixer( const ofSoundMixer& other ) { copyFrom( other ); }
	ofSoundMixer& operator=( const ofSoundMixer& other ) { copyFrom( other ); return *this; }
	~ofSoundMixer();
	
	string getName() { return "ofSoundMixer"; }
	
	/// Set the master out volume of this mixer
	void setMasterVolume( float vol ) { if ( !isnan(vol) && isfinite(vol) ) { masterVolume = vol; } }
	/// Set the volume of the mixer input for the given unit to vol.
	void setVolume( ofSoundSource* input, float vol );
	/// Set the pan of the mixer input for the given unit to pan
	void setPan( ofSoundSource* input, float pan );
	
	/// Add an input to this unit from the given source unit.
	bool addInputFrom( ofSoundSource* source );
	
	
	/// Remove an input from the mixer
	bool removeInputFrom(ofSoundSource* source);
	
	/// render
	void audioRequested( float* buffer, int numFrames, int numChannels );
	
	/// return all our inputs
	vector<ofSoundSource*> getInputs();
	
	/// pass sample rate changes on to inputs
	void setSampleRate( int rate );
	
private:
	// safely copy from the other mixer (probably a bad idea though)
	void copyFrom( const ofSoundMixer& other );
	
	// Inputs into the mixer, with volume and pan
	struct MixerInput
	{
		ofSoundSource* input;
		ofSoundBuffer inputBuffer;
		float volume;
		float pan;
		MixerInput( ofSoundSource* i, float v, float p )
		{
			input = i;
			volume = v;
			pan = p;
		}
	};
	vector<MixerInput*> inputs;
    
	float masterVolume;
	
	float* working;
};


#endif /* defined(__synthesis__ofSoundMixer__) */
