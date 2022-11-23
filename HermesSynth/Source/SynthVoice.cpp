/*
  ==============================================================================

    SynthVoice.cpp
    Created: 14 Nov 2022 10:49:05pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc.prepare(spec);
    gain.prepare(spec);
    
    osc.setFrequency(220.0f);
    gain.setGainLinear(0.01);
    s
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSample)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };
    osc.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
}

