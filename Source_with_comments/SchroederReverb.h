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

class SchroederReverb{
public:
    SchroederReverb(int sampleRate, float dryGain, float wetGain);
    float processSample(float x);
    void processBlock(AudioBuffer<float>& buffer);
    void setDryGain(float newDryGain);
    void setWetGain(float newWetGain);
    void setReverbTime(float newReverbTime);
private:
    std::vector<std::vector<float>> presetValues = {{0.0497, 0.0674, 0.0738, 0.0750, 0.002, 0.003}, {0.8423, 0.7923, 0.7750, 0.7718, 0.55, 0.67}};
    std::vector<CombFilter> combFilters;
    std::vector<AllPassFilter> allPassFilters;
    int sampleRate;
    float dryGain;
    float wetGain;
};
