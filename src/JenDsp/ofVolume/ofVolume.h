//
//  ofVolume.h
//  synthesis
//
//  Created by Mitchell Nordine on 30/07/13.
//
//

#ifndef __synthesis__ofVolume__
#define __synthesis__ofVolume__

#include "ofSoundEffect.h"

/** ofSoundDeclickedFloat
 
 Declick a changing float value by using a 64 sample ramp (around 1.5ms at 44.1kHz).
 
 You must call rebuildRampIfNecessary before processing every audio block, in order to apply incoming
 value changes.
 
 Also, you must call frameTick() for every audio frame (sample) to advance the ramp.
 
 @author damian
 */

class ofSoundDeclickedFloat
{
public:
	ofSoundDeclickedFloat( float startValue=0.0f ) { rampPos = 0; current = startValue; setValue( startValue ); }
	
	/// Return the current value, declicked
	float getDeclickedValue() { return current; }
	/// Return the raw value (the target for declicking)
	float getRawValue() { return target; }
	/// Set a new value + rebuild ramp
	void setValue( float newValue ) { if ( !isnan(newValue)&&finite(newValue) ) { target = newValue; rampNeedsRebuild = true; } }
	
	/// Rebuild the ramp, if necessary. Call before processing a block of samples.
	void rebuildRampIfNecessary() { if ( rampNeedsRebuild ) rebuildRamp(); rampNeedsRebuild = false; }
	
	/// Update, to be called for every frame
	void frameTick() { current = ramp[rampPos]; ramp[rampPos] = target; rampPos = (rampPos+1)%64; }
	
	/// operator overloading
	ofSoundDeclickedFloat& operator=( float new_value ) { setValue( new_value ); return *this; }
	ofSoundDeclickedFloat& operator+=( float adjustment ) { setValue( target+adjustment ); return *this; }
	ofSoundDeclickedFloat& operator-=( float adjustment ) { setValue( target-adjustment ); return *this; }
	
private:
	
	void rebuildRamp() { float v = current; float step = (target-current)/63; for ( int i=0; i<64; i++ ) { ramp[(i+rampPos)%64] = v; v += step; } }
	
	float current;
	float target;
	
	bool rampNeedsRebuild;
	int rampPos;
	float ramp[64];
};


/** ofSoundEffectVolume
 
 An ofSoundEffect that applies a volume (gain) to audio samples passing through it.
 
 @author damian
 */

class ofSoundEffectVolume : public ofSoundEffect
{
public:
	ofSoundEffectVolume() { setVolume( 1.0f ); }
	
	/// Return our name
	string getName() { return "ofSoundEffectVolume"; }
	
	/// Set our volume to vol
	void setVolume( float vol ) { 	if ( !isnan(vol) && isfinite(vol) ) { volume = vol; } }
	/// Adjust our current volume by adjustment
	void adjustVolume( float adjustment ) { if ( !isnan(adjustment) && isfinite(adjustment) ) { volume += adjustment; } }
	/// Get current volume (not declicked)
	float getVolume() { return volume.getRawValue(); }
	
	void process( float* input, float* output, int numFrames, int numInChannels, int numOutChannels );
	
private:
	ofSoundDeclickedFloat volume;
	
	
};


#endif /* defined(__synthesis__ofVolume__) */
