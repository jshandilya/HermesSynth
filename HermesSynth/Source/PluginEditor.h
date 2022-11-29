/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"

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
    juce::ComboBox oscSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttachment;
    
    HermesSynthAudioProcessor& audioProcessor;
    AdsrComponent adsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HermesSynthAudioProcessorEditor)
};
