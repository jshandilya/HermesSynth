/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"

//==============================================================================
/**
*/
class HermesSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HermesSynthAudioProcessorEditor (HermesSynthAudioProcessor&);
    ~HermesSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    HermesSynthAudioProcessor& audioProcessor;
    
    OscComponent osc;
    AdsrComponent adsr;
    FilterComponent filter;
    AdsrComponent modAdsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HermesSynthAudioProcessorEditor)
};
