/*
  ==============================================================================

    DistortionData.cpp
    Created: 5 Dec 2022 6:35:11am
    Author:  Jahan Shandilya

  ==============================================================================
*/

#include "DistortionData.h"

void DistortionData::process(juce::AudioBuffer<float>& buffer, float gain, float level)
{
    float* channelLeft = buffer.getWritePointer(0);
    float* channelRight = buffer.getWritePointer(1);
    
    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
//        gain = gain - 0.004;
        
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
}
