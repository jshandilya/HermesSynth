/*
  ==============================================================================

    DistortionData.h
    Created: 5 Dec 2022 6:35:11am
    Author:  Jahan Shandilya

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class DistortionData
{
public:
    void setDistortionType(const int choice, juce::AudioBuffer<float>& buffer, float gain, float level, int numChannels);
    
    void hardClip(juce::AudioBuffer<float>& buffer, float gain, float level, int numChannels);
    void softClip(juce::AudioBuffer<float>& buffer, float gain, float level, int numChannels);
    void distortionOff(juce::AudioBuffer<float>& buffer, float gain, float level, int numChannels);

    
private:

};
