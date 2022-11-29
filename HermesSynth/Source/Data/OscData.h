/*
  ==============================================================================

    OscData.h
    Created: 28 Nov 2022 9:25:47pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);

    
private:
    
    
};
