/*
  ==============================================================================

    AdsrData.h
    Created: 28 Nov 2022 6:50:30pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR (const float attack, const float decay, const float sustain, const float release);
    
    
private:
    juce::ADSR::Parameters adsrParams;
};
