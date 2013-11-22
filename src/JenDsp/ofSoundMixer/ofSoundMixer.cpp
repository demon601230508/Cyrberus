//
//  ofSoundMixer.cpp
//  synthesis
//
//  Created by Mitchell Nordine on 30/07/13.
//
//

#include "ofSoundMixer.h"

ofSoundMixer::~ofSoundMixer() {
	if ( working )
		delete[] working;
	for ( int i =0; i<(int)inputs.size(); i++ ) {
		delete inputs[i];
	}
}

void ofSoundMixer::copyFrom( const ofSoundMixer& other ) {
	ofLog( OF_LOG_WARNING, "Copying ofSoundMixer, this will probably make things break" );
	working = NULL;
	for ( int i=0; i<(int)other.inputs.size(); i++ ) {
		addInputFrom( other.inputs[i]->input );
		setVolume( other.inputs[i]->input, other.inputs[i]->volume );
		setPan( other.inputs[i]->input, other.inputs[i]->pan );
	}
	masterVolume = other.masterVolume;
}

void ofSoundMixer::setVolume( ofSoundSource* input, float vol ) {
	if ( isnan(vol) || !isfinite(vol) ) {
		return;
	}
	for ( int i=0; i<(int)inputs.size(); i++ ) {
		if ( inputs[i]->input == input ) {
			inputs[i]->volume = vol;
		}
	}
}

void ofSoundMixer::setPan( ofSoundSource* input, float pan ) {
	if ( isnan(pan) || !isfinite(pan) ) {
		return;
	}
	pan = min(1.0f,max(0.0f,pan));
	bool found = false;
	for ( int i=0; i<(int)inputs.size(); i++ ) {
		if ( inputs[i]->input == input ) {
			found = true;
			inputs[i]->pan = pan;
		}
	}
	if ( !found ) {
		ofLog( OF_LOG_WARNING, "ofSoundMixer: setPan couldn't find input for '%s' (%x), not setting pan", input->getName().c_str(), input );
		
	}
}




// Render the DSP chain. output is interleaved and has space for
// numFrames*numChannels floats.
void ofSoundMixer::audioRequested( float* output, int numFrames, int numChannels )
{
	// advance DSP
	if ( numChannels != 1 && numChannels != 2 ) {
		ofLog( OF_LOG_ERROR, "only 1 or 2 channels supported");
		return;
	}
	// write to output
	// clear output array
	memset( output, 0, numFrames*numChannels*sizeof(float) );
	
	mutex.lock();
	
	// allocate working space
	if ( !working ) {
		working = new float[numFrames*numChannels];
	}
	vector<float> volumePerChannel;
	volumePerChannel.resize( numChannels );
	for ( int i=0; i<(int)inputs.size(); i++ ) {
		// clear working
		memset( working, 0, numFrames*numChannels*sizeof(float) );
		
		// render input into working
		inputs[i]->input->audioRequested( working, numFrames, numChannels );
		
		// construct precalculated volume + pan array (for efficiency)
		float vol_l = inputs[i]->volume*(1.0f-inputs[i]->pan);
		float vol_r = inputs[i]->volume*inputs[i]->pan;
		for ( int j=0; j<numChannels; j++ ) {
			volumePerChannel[j] = (j==0?vol_l:vol_r) * masterVolume;
		}
		// mix working into output, respecting pan and volume and preserving interleaving
		float *working_ptr = working;
		float *output_ptr = output;
		for ( int j=0; j<numFrames; j++ ) {
			for ( int k=0; k<numChannels; k++ ) {
				*output_ptr++ += *working_ptr++ * volumePerChannel[k];
			}
		}
	}
	
	mutex.unlock();
    
}



/// Add an input to this unit from the given source unit
bool ofSoundMixer::addInputFrom( ofSoundSource* source )
{
	// check for branches/cycles
	if ( addingInputWouldCreateCycle( source ) )
	{
		ofLog( OF_LOG_ERROR, "ofSoundMixer: can't connect '%s' (%x) to '%s' (%x): this would create a cycle in the DSP graph",
			  source->getName().c_str(), source, this->getName().c_str(), this );
		return false;
	}
    
	mutex.lock();
	inputs.push_back( new MixerInput( source, 1.0f, 0.5f ) );
	source->setSampleRate( sampleRate );
	mutex.unlock();
	return true;
}

/// Remove an input from the mixer
bool ofSoundMixer::removeInputFrom(ofSoundSource* source)
{
	mutex.lock();
	// search the triggers and delete the one we don't want
	for ( int i=0; i<(int)inputs.size(); i++ ) {
		if (inputs[i]->input == source) {
			inputs.erase(inputs.begin()+i);
			mutex.unlock();
			return true;
		}
	}
	ofLog( OF_LOG_ERROR, "ofSoundMixer: can't remove '%s' (%x) from '%s' (%x): it was not found in the inputs",
		  source->getName().c_str(), source, this->getName().c_str(), this );
	mutex.unlock();
	return false;
}

vector<ofSoundSource*> ofSoundMixer::getInputs()
{
	vector<ofSoundSource*> result;
	mutex.lock();
	for ( int i =0; i<(int)inputs.size(); i++ ) {
		result.push_back( inputs[i]->input );
	}
	mutex.unlock();
	return result;
}


void ofSoundMixer::setSampleRate( int rate )
{
	mutex.lock();
	for ( int i =0; i<(int)inputs.size(); i++ ) {
		inputs[i]->input->setSampleRate( rate );
	}
	mutex.unlock();
	ofSoundSource::setSampleRate( rate );
	ofSoundSink::setSampleRate( rate );
}