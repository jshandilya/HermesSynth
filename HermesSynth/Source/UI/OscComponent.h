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
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String osc1GainID, juce::String osc2GainID, juce::String waveSelectorID, juce::String voicesSelectorID, juce::String fmFreqID, juce::String fmDepthID, juce::String waveSelectorID2, juce::String fmFreqID2, juce::String fmDepthID2);
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
    
    juce::ComboBox oscWaveSelector2;
    std::unique_ptr<BoxAttachment> oscWaveSelectorAttachment2;
    
    // Sliders
    juce::Slider osc1GainSlider;
    juce::Slider osc2GainSlider;

    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    juce::Slider fmFreqSlider2;
    juce::Slider fmDepthSlider2;
    
    std::unique_ptr<SliderAttachment> osc1GainAttachment;
    std::unique_ptr<SliderAttachment> osc2GainAttachment;
    
    std::unique_ptr<SliderAttachment> fmFreqAttachment;
    std::unique_ptr<SliderAttachment> fmDepthAttachment;
    
    std::unique_ptr<SliderAttachment> fmFreqAttachment2;
    std::unique_ptr<SliderAttachment> fmDepthAttachment2;

    // Labels
    juce::Label voicesSelectorLabel { "Voices", "Voices" };
    
    juce::Label waveSelectorLabel { "Osc 1 Wave Type", "OSC 1" };
    juce::Label waveSelectorLabel2 { "Osc 2 Wave Type", "OSC 2" };

    juce::Label osc1GainLabel { "Osc 1 Gain", "Gain" };
    juce::Label osc2GainLabel { "Osc 2 Gain", "Gain" };
    
    juce::Label fmFreqLabel { "Osc 1 FM Freq", "FM Freq" };
    juce::Label fmDepthLabel { "Osc 1 FM Depth", "FM Depth" };
    
    juce::Label fmFreqLabel2 { "Osc 2 FM Freq", "FM Freq" };
    juce::Label fmDepthLabel2 { "Osc 2 FM Depth", "FM Depth" };

    // Utility Function
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<SliderAttachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
