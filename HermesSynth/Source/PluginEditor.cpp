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
, osc ("OSC 1", audioProcessor.apvts, "OSC1GAIN", "OSC1WAVETYPE", "VOICES", "OSC1FMFREQ", "OSC1FMDEPTH")
, osc2("OSC 2", audioProcessor.apvts, "OSC2GAIN", "OSC2WAVETYPE", "VOICES", "OSC2FMFREQ", "OSC2FMDEPTH")
, adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
, filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
, modAdsr("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
, distortion(audioProcessor.apvts, "DISTTYPE", "DISTGAIN", "DISTLEVEL")
{
    setSize (930, 450);
    addAndMakeVisible(osc);
    addAndMakeVisible(osc2);
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
    const auto paddingY2 = 220;
    const auto paddingY3 = 520;
    
    const auto width = 310 - paddingX;
    const auto height = 200;
    
    osc.setBounds(paddingX, paddingY, width, height);
    osc2.setBounds(osc.getRight(), paddingY, width, height);
    adsr.setBounds(osc2.getRight(), paddingY, width, height);
    filter.setBounds(paddingX, paddingY2, width, height);
//    filter.setBounds(adsr.getRight(), paddingY2, width, height);
    modAdsr.setBounds(filter.getRight(), paddingY2, width, height);
    distortion.setBounds(adsr.getX(), paddingY2, width, height);}


