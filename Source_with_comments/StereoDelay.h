/*
  ==============================================================================

    StereoDelay.h
    Created: 18 May 2020 12:32:37pm
    Author:  Stef

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Filters.h"
#include "ModularCircularBuffer.h"

class StereoDelay{
public:
    StereoDelay(int sampleRate, float totalDelay, float initDelay, float initFeedback, float initBandwidth, float initWetGain);
    float processSample(float x);
    void processBuffer(AudioBuffer<float>& buffer);
    void setDelay(int channel, float newDelay);
    void setFeedback(int channel, float newFeedback);
    void setBandwidth(int channel, float newBandwidth);
    void setWetGain(int channel, float newWetGain);
    
private:
    int sampleRate;
    float totalDelay;
    std::vector<float> delay;
    std::vector<float> feedback;
    std::vector<float> bandwidth;
    std::vector<float> wetGain;
    std::vector<ModularCircularBuffer> buffers;
    std::vector<LowPassFilter1> lowPassFilters;
};
