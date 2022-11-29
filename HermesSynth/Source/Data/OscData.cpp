/*
  ==============================================================================

    OscData.cpp
    Created: 28 Nov 2022 9:25:47pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);

}


void OscData::setWaveType(const int choice)
{
    /*
     return std::sin (x);   // Sine
     return x / juce::MathConstants<float>::pi  // Saw
     return x < 0.0f ? - 1.0f : 1.0f    // Square
     */
    
    switch (choice)
    {
        // Sine
        case 0:
            initialise([](float x) { return std::sin (x); });
            break;
            
        // Saw
        case 1:
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;
        
        // Square
        case 2:
            initialise([](float x) { return x < 0.0f ? - 1.0f : 1.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float> (block));
}
