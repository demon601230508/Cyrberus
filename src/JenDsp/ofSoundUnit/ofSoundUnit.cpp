/*
 *  ofSoundUnit.cpp
 *  ofSound
 *
 *  Created by damian on 10/01/11.
 *  Copyright 2011 frey damian@frey.co.nz. All rights reserved.
 *
 */

#include "ofSoundUnit.h"
#include "ofUtils.h"

#include <deque>
using namespace std;

/*
vector<ofSoundSource*> ofSoundUnit::getInputs()
{
	ofLog(OF_LOG_WARNING, "ofSoundUnit::getInputs() called");
	// no inputs
	return vector<ofSoundSource*>();
}*/

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

void ofSoundSink::setSampleRate( int rate )
{

	vector<ofSoundSource*> inputs = getInputs();
	for ( int i=0; i<(int)inputs.size(); i++ )
	{ 
		inputs[i]->setSampleRate( rate ); 
	}
	sampleRate = rate;
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

bool ofSoundSink::addInputFrom( ofSoundSource* from ) 
{
	// check for existing input
	if ( input != NULL )
	{
		ofLog( OF_LOG_ERROR, "ofSoundUnit: can't connect '%s' (%x) to '%s' (%x): it already has an input",
			  from->getName().c_str(), from, this->getName().c_str(), this );
		return false;
	}
	// check for branches/cycles
	if ( addingInputWouldCreateCycle( from ) )
	{
		ofLog( OF_LOG_ERROR, "ofSoundUnit: can't connect '%s' (%x) to '%s' (%x): this would create a cycle in the DSP graph",
			  from->getName().c_str(), from, this->getName().c_str(), this );
		return false;
	}

	input = from;
	from->setSampleRate( sampleRate );
	return true;
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

vector<ofSoundSource*> ofSoundSink::getInputs()
{
	lock();
	vector<ofSoundSource*> result;
	if ( input )
	{
		result.push_back( input );
	}
	unlock();
	return result;
	
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

/// Receive incoming audio from elsewhere (eg coming from a microphone or line input source)
void ofSoundSink::audioReceived( float* buffer, int numFrames, int numChannels )
{
	lock();
	inputBuffer.allocate( numFrames, numChannels );
	memcpy( inputBuffer.buffer, buffer, numFrames*numChannels*sizeof(float) );
	unlock();
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

void ofSoundSink::fillInputBufferFromUpstream( int numFrames, int numChannels )
{
	// fetch data from input, and render via process() function
	// create/recreate input buffer if necessary
	if ( inputBuffer.numFrames != numFrames || inputBuffer.numChannels != numChannels )
	{
		inputBuffer.allocate( numFrames, numChannels );
	}
	
	// call input's generate
	if ( !input )
	{
		inputBuffer.clear();
	}
	else
	{
		input->audioRequested( inputBuffer.buffer, inputBuffer.numFrames, inputBuffer.numChannels );
	}
	
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

// Return true if adding this edge to the graph would create a cycle
bool ofSoundSink::addingInputWouldCreateCycle( ofSoundSource* test )
{
	// assuming the graph has no cycles from the start, can we already trace a path 
	// from test_input to ourselves? if we can, then adding test_input will create 
	// a cycle.
	
	// do a depth-first traversal
	deque<ofSoundUnit*> stack;
	stack.push_back( test );
	while ( !stack.empty() )
	{
		ofSoundUnit* u = stack.back();
		stack.pop_back();
		// if u is this, then we have looped round to the beginning
		if ( u == this ) {
			return true;
		}
		
		// fetch all immediate upstream neighbours
		vector<ofSoundSource*> upstream = u->getInputs();
		// copy downstream to the back of stack
		copy( upstream.begin(), upstream.end(), back_inserter( stack ) );
	}
	
	
	// if we made it here, the cycle test has failed to find a cycle
	return false;
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

ofSoundBuffer::ofSoundBuffer() {
	numFrames = 0;
	numChannels = 0;
	buffer = NULL;
}
ofSoundBuffer::ofSoundBuffer( const ofSoundBuffer& other ) {
	copyFrom( other );
}
ofSoundBuffer::ofSoundBuffer( int nFrames, int nChannels ) {
	numFrames = nFrames;
	numChannels = nChannels;
	buffer = new float[nFrames*nChannels];
}
ofSoundBuffer& ofSoundBuffer::operator=( const ofSoundBuffer& other ) {
	copyFrom( other );
	return *this;
}

ofSoundBuffer::~ofSoundBuffer() {
	if ( buffer ) {
		delete[] buffer;
	}
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

void ofSoundBuffer::copyFrom( const ofSoundBuffer& other ) {
	numFrames = 0; numChannels = 0;
	if ( other.buffer ) {
		allocate( other.numFrames, other.numChannels );
		memcpy( buffer, other.buffer, numFrames*numChannels*sizeof(float) );
	}
	else {
		buffer = NULL;
	}
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

/// Set audio data to 0.
void ofSoundBuffer::clear() {
	if ( buffer ) {
		memset( buffer, 0, sizeof(float)*numFrames*numChannels);
	}
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

/// Allocate the buffer to the given size if necessary.
void ofSoundBuffer::allocate( int nFrames, int nChannels ) {
	if ( !buffer || numFrames != nFrames || numChannels != nChannels ) {
		numFrames = nFrames; numChannels = nChannels;
		if ( buffer ) {
			delete[] buffer;
		}
		buffer = new float[numFrames*numChannels];
	}
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

/// Copy just a single channel to output. output should have space for numFrames floats.
void ofSoundBuffer::copyChannel( int channel, float* output ) const {
	if ( buffer && channel < numChannels ) {
		float * buffer_ptr = buffer;
		for ( int i=0; i<numFrames; i++ ) {
			*output++ = *(buffer_ptr+channel);
			buffer_ptr += numChannels;
		}
	}
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//

/// Copy safely to out. Copy as many frames as possible, repeat channels as necessary.
void ofSoundBuffer::copyTo( float* outBuffer, int outNumFrames, int outNumChannels ) {
	if ( numFrames == 0 || numChannels == 0 ) {
		ofLog( OF_LOG_WARNING, "ofSoundBuffer::copyTo: copy requested on empty buffer, returning nothing (check your addInputTo() methods!)" );
		memset( outBuffer, 0, sizeof(float)*outNumFrames*outNumChannels );
	}
	if ( outNumFrames>numFrames ||  outNumChannels>numChannels ) {
		ofLog( OF_LOG_WARNING, "ofSoundBuffer::copyTo: %i frames requested but only %i	are available", outNumFrames, numFrames );
		ofLog( OF_LOG_WARNING, "ofSoundBuffer::copyTo: %i channels requested but only %i are available, looping to make up the difference", outNumChannels, numChannels );
        
		for ( int i=0; i<min(numFrames,outNumFrames); i++ ) {
			for ( int j=0; j<outNumChannels; j++ ) {
				// copy input to output; in cases where input has fewer channels than output, loop through input frames repeatedly
				*outBuffer++ = buffer[i*numChannels+(j%numChannels)];
			}
		}
	}else{
		memcpy(outBuffer,buffer,outNumFrames*outNumChannels*sizeof(float));
	}
}












