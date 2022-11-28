/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HermesSynthAudioProcessor::HermesSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
//    synth.addSound(new SynthSound());
    
    for (int i = 0; i < numVoices; i++)
    {
        synth.addVoice(new SynthVoice());
        synth.addSound(new SynthSound());
    }
}

HermesSynthAudioProcessor::~HermesSynthAudioProcessor()
{
}

//==============================================================================
const juce::String HermesSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HermesSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HermesSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HermesSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HermesSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HermesSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HermesSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HermesSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HermesSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void HermesSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HermesSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void HermesSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HermesSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HermesSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<juce::SynthesiserVoice*>(synth.getVoice(i)))
        {
            // Osc controls
            // ADSR
            // LFO
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool HermesSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HermesSynthAudioProcessor::createEditor()
{
    return new HermesSynthAudioProcessorEditor (*this);
}

//==============================================================================
void HermesSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HermesSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HermesSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout HermesSynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // OSC Waveform
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    
    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "ATTACK", 1}, "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "DECAY", 1}, "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "SUSTAIN", 1}, "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "RELEASE", 1}, "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, }, 0.4f));
   
    return { params.begin(), params.end() };
}
