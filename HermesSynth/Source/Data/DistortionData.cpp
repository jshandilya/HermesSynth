/*
  ==============================================================================

    DistortionData.cpp
    Created: 5 Dec 2022 6:35:11am
    Author:  Jahan Shandilya

  ==============================================================================
*/

#include "DistortionData.h"

void DistortionData::process(const int choice, juce::AudioBuffer<float>& buffer, float gain, float level, int numChannels)
{
    // Hard clip
    float* channelLeft = buffer.getWritePointer(0);
    float* channelRight = buffer.getWritePointer(1);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        channelLeft[sample] *= gain;
        channelRight[sample] *= gain;

        if (channelLeft[sample] > 1.0f)
        {
            channelLeft[sample] = 1.0f;
        } else if (channelLeft[sample] < -1.0f)
        {
            channelLeft[sample] =  -1.0f;
        }

        if (channelRight[sample] > 1.0f)
        {
            channelRight[sample] = 1.0f;
        } else if (channelRight[sample] < -1.0f)
        {
            channelRight[sample] =  -1.0f;
        }

        channelLeft[sample] *= level;
        channelRight[sample] *= level;
    }

    // Soft clip
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] *= juce::Decibels::decibelsToGain(gain);
            channelData[sample] = (2 / M_PI) * atan(channelData[sample]);

            channelData[sample] *= level;
        }
    }
}
