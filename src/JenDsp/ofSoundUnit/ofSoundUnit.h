/*
 *  ofSoundUnit.h
 *  ofSound
 *
 *  Created by damian on 10/01/11.
 *  Copyright 2011 frey damian@frey.co.nz. All rights reserved.
 *
 */

#pragma once

#include "ofSoundStream.h"
#include "ofTypes.h"
#include <vector>

class ofSoundSource;


/** ofSoundUnit
 
 Base class for sound units that can be strung together into a DSP-style chain.
 
 @author damian
 */

class ofSoundUnit
{
public:	
	virtual ~ofSoundUnit() {};
	
	/// Return the name of this synth unit.
	virtual string getName() = 0;

	/// Return our inputs in a vector (but at ofSoundUnit level we have no inputs).
	virtual vector<ofSoundSource*> getInputs()  { return vector<ofSoundSource*>(); }
	
protected:
	
	
};


/** ofSoundSource
 
 Base class for ofSoundUnits that generate some kind of sound output.
 
 @author damian
 */


class ofSoundSource: public virtual ofSoundUnit
{
public:
	virtual ~ofSoundSource() {};
    
	/// Set the sample rate. If you need to know about sample rate changes, override this function.
	virtual void setSampleRate( int rate ) {};
	
	/// Fill buffer with (numFrames*numChannels) floats of data, interleaved
	virtual void audioRequested( float* buffer, int numFrames, int numChannels ) = 0;
	
protected:
	
	
};


/** ofSoundBuffer
 
 Wrapper for an interleaved floating point buffer holding a fixed number of frames
 of a fixed number of channels of audio.
 
 @author damian
 */

class ofSoundBuffer
{
public:
	
	float* buffer;
	int numFrames;
	int numChannels;
	
	ofSoundBuffer();
	ofSoundBuffer( const ofSoundBuffer& other );
	ofSoundBuffer( int nFrames, int nChannels );
	ofSoundBuffer& operator=( const ofSoundBuffer& other );
	
	~ofSoundBuffer();
	void copyFrom( const ofSoundBuffer& other );
	/// Set audio data to 0.
	void clear();
	
	/// Allocate the buffer to the given size if necessary.
	void allocate( int nFrames, int nChannels );
	
	/// Copy just a single channel to output. output should have space for numFrames floats.
	void copyChannel( int channel, float* output ) const ;
	
	/// Copy safely to out. Copy as many frames as possible, repeat channels as necessary.
	void copyTo( float* outBuffer, int outNumFrames, int outNumChannels );
    
    
};


/** ofSoundSink
 
 Base class for ofSoundUnits that receive audio data, either by pulling from upstream 
 inputs, or from the audioReceived function which is called from outside in special 
 cases (eg when used as microphone/line input).
 
 @author damian
 */

class ofSoundSink: public virtual ofSoundUnit
{
public:
	ofSoundSink() { input = NULL; sampleRate = 44100; }
	virtual ~ofSoundSink() {};
	
	/// Set the sample rate of this synth unit. If you overload this remember to call the base class.
	virtual void setSampleRate( int rate );

	/// Add an input to this unit from the given source unit. If overloading remember to call base.
	virtual bool addInputFrom( ofSoundSource* source );
	
	/// Return our inputs in a vector.
	virtual vector<ofSoundSource*> getInputs();
	
	/// Receive incoming audio from elsewhere (eg coming from a microphone or line input source)
	virtual void audioReceived( float* buffer, int numFrames, int numChannels );
	
protected:
	// fill our input buffer from the upstream source (input)
	void fillInputBufferFromUpstream( int numFrames, int numChannels );
	
	// walk the DSP graph and see if adding test_input as an input to ourselves; return true if it would.
	bool addingInputWouldCreateCycle( ofSoundSource* test_input );

	
	void lock() { mutex.lock(); }
	void unlock() { mutex.unlock(); }	
	ofMutex mutex;
		
	
	
	ofSoundSource* input;
	ofSoundBuffer inputBuffer;

	int sampleRate;
};











