/*
  ==============================================================================

    DistortionComponent.h
    Created: 5 Dec 2022 6:35:33am
    Author:  Jahan Shandilya

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distTypeID, juce::String gainID, juce::String levelID);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using BoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    juce::ComboBox distTypeSelector;
    std::unique_ptr<BoxAttachment> distTypeAttachment;
    juce::Label distTypeLabel { "Distortion Type", "Type" };
    
    juce::Slider gainSlider;
    juce::Slider levelSlider;
    
    std::unique_ptr<SliderAttachment> gainAttachment;
    std::unique_ptr<SliderAttachment> levelAttachment;
    
    juce::Label gainLabel { "Distortion Gain", "Gain" };
    juce::Label levelLabel { "Distortion Level", "Level" };

    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<SliderAttachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
