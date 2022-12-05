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
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setWaveType(const int choice);
    void setGain (const float levelInDecibels);
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFMParams(const float depth, const float freq);
    
private:
    juce::dsp::Oscillator<float> fmOsc { [](float x) { return std::sin (x); } };
    juce::dsp::Gain<float> gain;
    float fmMod { 0.0f };
    float fmDepth { 0.0f };
    int lastMidiNote { 0 };

};
