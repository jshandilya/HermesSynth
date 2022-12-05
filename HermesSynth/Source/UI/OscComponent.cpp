/*
  ==============================================================================

    OscComponent.cpp
    Created: 28 Nov 2022 9:52:39pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::String name, juce::AudioProcessorValueTreeState& apvts, juce::String osc1GainID, juce::String osc1PitchID, juce::String waveSelectorID, juce::String voicesSelectorID, juce::String fmFreqID, juce::String fmDepthID)
{
    componentName = name;
    
    // Voices Box
    juce::StringArray voicesChoices { "1", "2", "3", "4", "5", "6", "7", "8" };
    voicesSelector.addItemList(voicesChoices, 1);
    addAndMakeVisible(voicesSelector);
    
    voicesSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, voicesSelectorID, voicesSelector);
    
    voicesSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    voicesSelectorLabel.setFont (15.0f);
    voicesSelectorLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (voicesSelectorLabel);
    
    // Osc
    juce::StringArray waveChoices { "Sine", "Triangle", "Square", "Saw" };
    oscWaveSelector.addItemList(waveChoices, 1);
    addAndMakeVisible(oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    
    waveSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel.setFont (15.0f);
    waveSelectorLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (waveSelectorLabel);
    
    setSliderWithLabel(osc1GainSlider, osc1GainLabel, apvts, osc1GainID, osc1GainAttachment);
    setSliderWithLabel(osc1PitchSlider, osc1PitchLabel, apvts, osc1PitchID, osc1PitchAttachment);
    
    setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqID, fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthID, fmDepthAttachment);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText (componentName, labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    // Variables
    const auto startX = 10;
    const auto startY = 55;
    
    const auto boxWidth = 90;
    const auto boxHeight = 30;
    
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    const auto voicesOffset = 70;
    
    // Osc
    oscWaveSelector.setBounds (startX, startY + 5, boxWidth, boxHeight);
    waveSelectorLabel.setBounds (startX, startY - labelYOffset, oscWaveSelector.getWidth(), labelHeight);
    
    voicesSelector.setBounds (startX, oscWaveSelector.getY() + voicesOffset, boxWidth, boxHeight);
    voicesSelectorLabel.setBounds (startX, waveSelectorLabel.getY() + voicesOffset, voicesSelector.getWidth(), labelHeight);
    
    osc1GainSlider.setBounds (oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    osc1GainLabel.setBounds (osc1GainSlider.getX(), osc1GainSlider.getY() - labelYOffset, osc1GainSlider.getWidth(), labelHeight);
    
    osc1PitchSlider.setBounds (osc1GainSlider.getRight(), startY, sliderWidth, sliderHeight);
    osc1PitchLabel.setBounds (osc1PitchSlider.getX(), osc1PitchSlider.getY() - labelYOffset, osc1PitchSlider.getWidth(), labelHeight);
    
    fmFreqSlider.setBounds (osc1GainSlider.getX(), osc1GainSlider.getBottom() + 30, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds (fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);

    fmDepthSlider.setBounds (fmFreqSlider.getRight(), osc1PitchSlider.getBottom() + 30, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds (fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
}

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
