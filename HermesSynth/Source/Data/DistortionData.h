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
    void process(juce::AudioBuffer<float>& buffer, float gain, float level);
    
private:
    
};
