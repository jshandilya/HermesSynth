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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String osc1GainID, juce::String osc2GainID, juce::String waveSelectorID, juce::String voicesSelectorID, juce::String fmFreqID, juce::String fmDepthID, juce::String waveSelectorID2, juce::String fmFreqID2, juce::String fmDepthID2)
{
    // Voices Box
    juce::StringArray voicesChoices { "1", "2", "3", "4", "5", "6", "7", "8" };
    voicesSelector.addItemList(voicesChoices, 1);
//    addAndMakeVisible(voicesSelector);
    
    voicesSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, voicesSelectorID, voicesSelector);
    
    voicesSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    voicesSelectorLabel.setFont (15.0f);
    voicesSelectorLabel.setJustificationType (juce::Justification::left);
//    addAndMakeVisible (voicesSelectorLabel);
    
    // Osc 1
    juce::StringArray waveChoices { "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(waveChoices, 1);
    addAndMakeVisible(oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID, oscWaveSelector);
    
    waveSelectorLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel.setFont (15.0f);
    waveSelectorLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (waveSelectorLabel);
    
    // Osc 2
    oscWaveSelector2.addItemList(waveChoices, 1);
    addAndMakeVisible(oscWaveSelector2);
    
    oscWaveSelectorAttachment2 = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorID2, oscWaveSelector2);
    
    waveSelectorLabel2.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel2.setFont (15.0f);
    waveSelectorLabel2.setJustificationType (juce::Justification::left);
    addAndMakeVisible (waveSelectorLabel2);
    
    
    setSliderWithLabel(osc1GainSlider, osc1GainLabel, apvts, osc1GainID, osc1GainAttachment);
    setSliderWithLabel(osc2GainSlider, osc2GainLabel, apvts, osc2GainID, osc2GainAttachment);
    
    setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqID, fmFreqAttachment);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthID, fmDepthAttachment);
    
    setSliderWithLabel(fmFreqSlider2, fmFreqLabel2, apvts, fmFreqID2, fmFreqAttachment2);
    setSliderWithLabel(fmDepthSlider2, fmDepthLabel2, apvts, fmDepthID2, fmDepthAttachment2);
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
    g.drawText ("Oscillators", labelSpace.withX (5), juce::Justification::left);
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
    
    // Osc 1
    oscWaveSelector.setBounds (startX, startY + 5, boxWidth, boxHeight);
    waveSelectorLabel.setBounds (startX, startY - labelYOffset, oscWaveSelector.getWidth(), labelHeight);
    
    voicesSelector.setBounds (startX, oscWaveSelector.getY() + voicesOffset, boxWidth, boxHeight);
    voicesSelectorLabel.setBounds (startX, waveSelectorLabel.getY() + voicesOffset, voicesSelector.getWidth(), labelHeight);
    
    osc1GainSlider.setBounds (oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    osc1GainLabel.setBounds (osc1GainSlider.getX(), osc1GainSlider.getY() - labelYOffset, osc1GainSlider.getWidth(), labelHeight);
    
    fmFreqSlider.setBounds (osc1GainSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmFreqLabel.setBounds (fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);

    fmDepthSlider.setBounds (fmFreqSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds (fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
    
    // Osc 2
    oscWaveSelector2.setBounds (fmDepthSlider.getRight(), startY + 5, boxWidth, boxHeight);
    waveSelectorLabel2.setBounds (oscWaveSelector2.getX(), startY - labelYOffset, oscWaveSelector2.getWidth(), labelHeight);
    
    osc2GainSlider.setBounds (oscWaveSelector2.getRight(), startY, sliderWidth, sliderHeight);
    osc2GainLabel.setBounds (osc2GainSlider.getX(), osc2GainSlider.getY() - labelYOffset, osc2GainSlider.getWidth(), labelHeight);
    
    fmFreqSlider2.setBounds (osc2GainSlider.getRight(), startY, sliderWidth, sliderHeight);
    fmFreqLabel2.setBounds (fmFreqSlider2.getX(), fmFreqSlider2.getY() - labelYOffset, fmFreqSlider2.getWidth(), labelHeight);
    
    fmDepthSlider2.setBounds (fmFreqSlider2.getRight(), startY, sliderWidth, sliderHeight);
    fmDepthLabel2.setBounds (fmDepthSlider2.getX(), fmDepthSlider2.getY() - labelYOffset, fmDepthSlider2.getWidth(), labelHeight);
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
