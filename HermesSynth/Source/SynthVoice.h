/*
  ==============================================================================

    SynthVoice.h
    Created: 14 Nov 2022 10:49:05pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/OscData.h"
#include "Data/AdsrData.h"
#include "Data/FilterData.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSample) override;
    
    void updateAdsr (const float attack, const float decay, const float sustain, const float release);
    void updateFilter(const int filterType, const float cutoff, const float res);
    void updateModAdsr (const float attack, const float decay, const float sustain, const float release);

    OscData& getOscillator() { return osc; }
    
private:
    juce::AudioBuffer<float> synthBuffer;
    
    OscData osc;
    AdsrData adsr;
    FilterData filter;
    AdsrData modAdsr;
    juce::dsp::Gain<float> gain;
    
    bool isPrepared { false };
    

};
