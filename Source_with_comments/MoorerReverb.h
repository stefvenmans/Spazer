/*
  ==============================================================================

    MoorerReverb.h
    Created: 16 May 2020 8:02:52pm
    Author:  Stef

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Filters.h"

class MoorerReverb{
public:
    MoorerReverb(int sampleRate, float dryGain, float wetGain);
    float processSample(float x);
    void processBlock(AudioBuffer<float>& buffer);
    void setDryGain(float newDryGain);
    void setWetGain(float newWetGain);
    void setReverbTime(float newReverbTime);
private:
    std::vector<std::vector<float>> presetValues = {{0.050, 0.056, 0.061, 0.068, 0.072, 0.078, 0.006}, {0.46, 0.47, 0.475, 0.48, 0.49, 0.50, 0.7}, {0.4482, 0.4399, 0.4350, 0.4316, 0.4233, 0.3735}};
    std::vector<LowPassCombFilter> lowPassCombFilters;
    AllPassFilter allPassFilter;
    int sampleRate;
    float dryGain;
    float wetGain;
    const float totalGain = 0.8;
};
