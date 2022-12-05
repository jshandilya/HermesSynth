/*
  ==============================================================================

    OscComponent.h
    Created: 28 Nov 2022 9:52:39pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String osc1GainID, juce::String osc1PitchID, juce::String waveSelectorID, juce::String voicesSelectorID, juce::String fmFreqID, juce::String fmDepthID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using BoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    // Combo Boxes
    juce::ComboBox voicesSelector;
    std::unique_ptr<BoxAttachment> voicesSelectorAttachment;
    
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<BoxAttachment> oscWaveSelectorAttachment;
    
    // Sliders
    juce::Slider osc1GainSlider;
    juce::Slider osc1PitchSlider;

    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    std::unique_ptr<SliderAttachment> osc1GainAttachment;
    std::unique_ptr<SliderAttachment> osc1PitchAttachment;
    std::unique_ptr<SliderAttachment> fmFreqAttachment;
    std::unique_ptr<SliderAttachment> fmDepthAttachment;

    // Labels
    juce::Label voicesSelectorLabel { "Voices", "Voices" };
    
    juce::Label waveSelectorLabel { "Osc 1 Wave Type", "Wave Type" };

    juce::Label osc1GainLabel { "Osc 1 Gain", "Gain" };
    juce::Label osc1PitchLabel { "Osc 1 Pitch", "Pitch" };
    
    juce::Label fmFreqLabel { "Osc 1 FM Freq", "FM Freq" };
    juce::Label fmDepthLabel { "Osc 1 FM Depth", "FM Depth" };
    
    juce::String componentName {""};

    // Utility Function
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<SliderAttachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
