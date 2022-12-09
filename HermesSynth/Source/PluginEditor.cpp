/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HermesSynthAudioProcessorEditor::HermesSynthAudioProcessorEditor (HermesSynthAudioProcessor& p)
    :AudioProcessorEditor (&p)
, audioProcessor (p)
, osc ("OSC 1", audioProcessor.apvts, "OSC1GAIN", "OSC1PITCH", "OSC1WAVETYPE", "VOICES", "OSC1FMFREQ", "OSC1FMDEPTH")
, osc2("OSC 2", audioProcessor.apvts, "OSC2GAIN", "OSC2PITCH", "OSC2WAVETYPE", "VOICES", "OSC2FMFREQ", "OSC2FMDEPTH")
, osc3("OSC 3", audioProcessor.apvts, "OSC3GAIN", "OSC3PITCH", "OSC3WAVETYPE", "VOICES", "OSC3FMFREQ", "OSC3FMDEPTH")
, adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
, modAdsr("Filter Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
, distortion(audioProcessor.apvts, "DISTTYPE", "DISTGAIN", "DISTLEVEL")
{
    setSize (930, 650);
    addAndMakeVisible(osc);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(modAdsr);
    addAndMakeVisible(distortion);
}

HermesSynthAudioProcessorEditor::~HermesSynthAudioProcessorEditor()
{
}

//==============================================================================
void HermesSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void HermesSynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 25;
    const auto paddingY2 = 320;
    const auto paddingY3 = 520;
    
    const auto expandY = 1.5f;
    
    const auto width = 310 - paddingX;
    const auto width2 = 232.5f - paddingX;
    const auto height = 300;
    const auto height2 = 300;
    
    osc.setBounds(paddingX, paddingY, width, height);
    osc2.setBounds(osc.getRight(), paddingY, width, height);
    osc3.setBounds(osc2.getRight(), paddingY, width, height);

    adsr.setBounds(paddingX, paddingY2, width2, height2);
    filter.setBounds(adsr.getRight(), paddingY2, width2, height2);
    modAdsr.setBounds(filter.getRight(), paddingY2, width2, height2);
    distortion.setBounds(modAdsr.getRight(), paddingY2, width2, height2);}


