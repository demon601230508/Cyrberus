/*
 *  ofSound.h
 *  openFrameworksLib
 *
 *  Created by damian on 12/01/11.
 *  Copyright 2011 frey damian@frey.co.nz. All rights reserved.
 *
 */

#pragma once

#include "ofSoundUnit.h"
#include <vector>
#include <deque>
using namespace std;


/** ofSoundEffect
 
 Base class for a sound effect, which takes input from an upstream ofSoundSource and processes it.
 
 Subclasses implement the process() method to perform processing.
 
 @author damian
 */

class ofSoundEffect: public ofSoundSource, public ofSoundSink
{
public:
	
	/// Pass sample rate changes through; if your override this remember to call base.
	void setSampleRate( int rate );
	
	/// Override this function to do your own processing. Be sure to match numInChannels and numOutChannels
	virtual void process( float* input, float *output, int numFrames, int numInChannels, int numOutChannels ) = 0;
	
	
	/// implementation of the generate function from ofSoundSource
	void audioRequested( float* buffer, int numFrames, int numChannels );
	
};




/** ofSoundEffectPassthrough
 
 An ofSoundEffect that simply passes audio through, allowing access to the ofSoundBuffer of audio 
 passing through it. 
 
 @author damian
 */

class ofSoundEffectPassthrough: public ofSoundEffect
{
public:
	string getName() { return "ofSoundEffectPassthrough"; }
	
	virtual void process( float* input, float *output, int numFrames, int numInChannels, int numOutChannels );
	
	/// return the buffer we saw as we passed it through
	ofSoundBuffer& getBuffer() { return inputBuffer; }
};






