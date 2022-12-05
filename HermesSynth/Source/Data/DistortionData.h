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
    void process(const int choice, juce::AudioBuffer<float>& buffer, float gain, float level, int numChannels);
    
private:

};
