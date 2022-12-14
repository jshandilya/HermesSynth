/*
  ==============================================================================

    OscData.cpp
    Created: 28 Nov 2022 9:25:47pm
    Author:  Jahan Shandilya

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    prepare(spec);
    fmOsc.prepare(spec);
    gain.prepare(spec);

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
            
        // Triangle
        case 1:
            initialise([](float x) { return abs(x / juce::MathConstants<float>::pi); });
            break;
        
        // Square
        case 2:
            initialise([](float x) { return x < 0.0f ? - 1.0f : 1.0f; });
            break;
            
        // Saw
        case 3:
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;
        
        // Noise
        case 4:
            initialise([this](float x) { return random.nextFloat() * 0.25f - 0.125f; });
            break;
            
        // Off
        case 5:
            initialise([](float x) { return x * 0.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setGain (const float levelInDecibels)
{
    gain.setGainDecibels(levelInDecibels);
}

void OscData::setPitch (const int pitch)
{
    lastPitch = pitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz((lastMidiNote + lastPitch) + fmMod));
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz((midiNoteNumber + lastPitch) + fmMod));
    lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int ch = 0; ch < block.getNumChannels(); ++ch)
    {
        for (int s = 0; s < block.getNumSamples(); ++s)
        {
            fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
        }
    }
    
    process(juce::dsp::ProcessContextReplacing<float> (block));
    gain.process(juce::dsp::ProcessContextReplacing<float> (block));
}

void OscData::setFMParams(const float depth, const float freq)
{
    fmDepth = depth;
    fmOsc.setFrequency(freq);
//    auto currentFreq = (juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod);
//    setFrequency (currentFreq >=0 ? currentFreq : currentFreq * -1.0f);
    
    setFrequency (juce::MidiMessage::getMidiNoteInHertz ((lastMidiNote + lastPitch) + fmMod));
}
