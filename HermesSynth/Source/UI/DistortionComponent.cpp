/*
  ==============================================================================

    DistortionComponent.cpp
    Created: 5 Dec 2022 6:35:33am
    Author:  Jahan Shandilya

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DistortionComponent.h"

//==============================================================================
DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distTypeID, juce::String gainID, juce::String levelID)
{
    juce::StringArray distChoicess { "Off", "Hard Clip", "Soft Clip" };
    distTypeSelector.addItemList(distChoicess, 1);
    addAndMakeVisible(distTypeSelector);
    
    distTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, distTypeID, distTypeSelector);
    
    distTypeLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    distTypeLabel.setFont (15.0f);
    distTypeLabel.setJustificationType (juce::Justification::left);
    addAndMakeVisible (distTypeLabel);
    
    setSliderWithLabel(gainSlider, gainLabel, apvts, gainID, gainAttachment);
    setSliderWithLabel(levelSlider, levelLabel, apvts, levelID, levelAttachment);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced (5);
    auto labelSpace = bounds.removeFromTop (25.0f);
    
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawText ("Distortion", labelSpace.withX (5), juce::Justification::left);
    g.drawRoundedRectangle (bounds.toFloat(), 5.0f, 2.0f);
}

void DistortionComponent::resized()
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
    
    distTypeSelector.setBounds (startX, startY + 5, boxWidth, boxHeight);
    distTypeLabel.setBounds (startX, startY - labelYOffset, distTypeSelector.getWidth(), labelHeight);
    
    gainSlider.setBounds (distTypeSelector.getRight(), startY + 5, sliderWidth, sliderHeight);
    gainLabel.setBounds (gainSlider.getX(), startY - labelYOffset, gainSlider.getWidth(), labelHeight);
    
    levelSlider.setBounds (gainSlider.getRight(), startY + 5, sliderWidth, sliderHeight);
    levelLabel.setBounds (levelSlider.getX(), startY - labelYOffset, levelSlider.getWidth(), labelHeight);
}

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void DistortionComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
