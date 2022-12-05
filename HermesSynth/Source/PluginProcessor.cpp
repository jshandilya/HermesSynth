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
    synth.addSound(new SynthSound());
    
    setNumVoices();
    
//    for (int i = 0; i < numVoices; i++)
//    {
//        synth.addVoice(new SynthVoice());
////        synth.addSound(new SynthSound());
//    }
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
    
    setNumVoices();
    
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
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // Osc 1
            auto& osc1WaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& osc1Gain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& fmDepth1 = *apvts.getRawParameterValue("OSC1FMDEPTH");
            auto& fmFreq1 = *apvts.getRawParameterValue("OSC1FMFREQ");
            
            // Osc 2
            auto& osc2WaveChoice = *apvts.getRawParameterValue("OSC2WAVETYPE");
            auto& osc2Gain = *apvts.getRawParameterValue("OSC2GAIN");
            auto& fmDepth2 = *apvts.getRawParameterValue("OSC2FMDEPTH");
            auto& fmFreq2 = *apvts.getRawParameterValue("OSC2FMFREQ");
            
            // Amp ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");
            
            // Filter
            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& cutoff = *apvts.getRawParameterValue("FILTERFREQ");
            auto& res = *apvts.getRawParameterValue("FILTERRES");
            
            // Mod ADSR
            auto& modAttack = *apvts.getRawParameterValue("MODATTACK");
            auto& modDecay = *apvts.getRawParameterValue("MODDECAY");
            auto& modSustain = *apvts.getRawParameterValue("MODSUSTAIN");
            auto& modRelease = *apvts.getRawParameterValue("MODRELEASE");
            
            // Connections
            voice->getOscillator1().setWaveType(osc1WaveChoice);
            voice->getOscillator1().setGain(osc1Gain);
            voice->getOscillator1().setFMParams(fmDepth1, fmFreq1);
            
            voice->getOscillator2().setWaveType(osc2WaveChoice);
            voice->getOscillator2().setGain(osc2Gain);
            voice->getOscillator2().setFMParams(fmDepth2, fmFreq2);
            
            voice->updateAdsr (attack.load(), decay.load(), sustain.load(), release.load());
            voice->updateFilter(filterType.load(), cutoff.load(), res.load());
            voice->updateModAdsr(modAttack, modDecay, modSustain, modRelease);
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

void HermesSynthAudioProcessor::setNumVoices()
{
    auto& voiceSelect = *apvts.getRawParameterValue("VOICES");
    numVoices = voiceSelect.load();
        
    for (int i = 0; i < numVoices; i++)
    {
        synth.addVoice(new SynthVoice());
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout HermesSynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // OSC Voices
    params.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID { "VOICES", 1 }, "Voices", 1, 8, 8));
    
    // OSC Waveform
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID { "OSC1WAVETYPE", 1 }, "Osc 1 Wave Type", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID { "OSC2WAVETYPE", 1 }, "Osc 2 Wave Type", juce::StringArray { "Sine", "Saw", "Square" }, 2));
    
    // OSC Gain
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "OSC1GAIN", 1 }, "Oscillator 1 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "OSC2GAIN", 1 }, "Oscillator 2 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));

    // FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "OSC1FMFREQ", 1}, "Osc 1 FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "OSC1FMDEPTH", 1}, "Osc 1 FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 0.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "OSC2FMFREQ", 1}, "Osc 2 FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "OSC2FMDEPTH", 1}, "Osc 2 FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 0.0f));
    
    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "ATTACK", 1}, "Attack", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "DECAY", 1}, "Decay", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "SUSTAIN", 1}, "Sustain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "RELEASE", 1}, "Release", juce::NormalisableRange<float> { 0.0f, 3.0f, 0.01f }, 0.4f));
    
    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID { "FILTERTYPE", 1 }, "Filter Type", juce::StringArray { "Lowpass", "Bandpass", "Highpass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "FILTERFREQ", 1}, "Filter Freq", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "FILTERRES", 1}, "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.01f}, 1.0f));

    // Filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "MODATTACK", 1}, "Mod Attack", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "MODDECAY", 1}, "Mod Decay", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "MODSUSTAIN", 1}, "Mod Sustain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { "MODRELEASE", 1}, "Mod Release", juce::NormalisableRange<float> { 0.0f, 3.0f, 0.01f }, 0.4f));

    return { params.begin(), params.end() };
}
