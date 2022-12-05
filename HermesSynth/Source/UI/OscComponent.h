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
    OscComponent(juce::AudioProcessorValueTreeState& apvts
 , juce::String waveSelectorID, juce::String voicesSelectorID, juce::String fmFreqID, juce::String fmDepthID
 , juce::String waveSelectorID2, juce::String fmFreqID2, juce::String fmDepthID2);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using BoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    juce::ComboBox voicesSelector;
    std::unique_ptr<BoxAttachment> voicesSelectorAttachment;
    
    juce::ComboBox oscWaveSelector;
    std::unique_ptr<BoxAttachment> oscWaveSelectorAttachment;
    
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    juce::ComboBox oscWaveSelector2;
    std::unique_ptr<BoxAttachment> oscWaveSelectorAttachment2;
    
    juce::Slider fmFreqSlider2;
    juce::Slider fmDepthSlider2;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> fmFreqAttachment;
    std::unique_ptr<SliderAttachment> fmDepthAttachment;
    
    std::unique_ptr<SliderAttachment> fmFreqAttachment2;
    std::unique_ptr<SliderAttachment> fmDepthAttachment2;

    juce::Label voicesSelectorLabel { "Voices", "Voices" };
    
    juce::Label waveSelectorLabel { "Wave Type", "Wave Type" };
    juce::Label fmFreqLabel { "FM Freq", "FM Freq" };
    juce::Label fmDepthLabel { "FM Depth", "FM Depth" };
    
    juce::Label waveSelectorLabel2 { "Wave Type", "Wave Type" };
    juce::Label fmFreqLabel2 { "FM Freq", "FM Freq" };
    juce::Label fmDepthLabel2 { "FM Depth", "FM Depth" };

    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<SliderAttachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
