/*
  ==============================================================================

    DattorroPlateReverb.h
    Created: 16 May 2020 9:25:36pm
    Author:  Stef

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Filters.h"

class DattorroPlateReverb{
public:
    DattorroPlateReverb(int sampleRate, float dryGainL, float wetGainL, float dryGainR, float wetGainR);
    float processSample(float x);
    void processBlock(AudioBuffer<float>& buffer);
    void setDryGainLeft(float newDryGainLeft);
    void setWetGainLeft(float newWetGainLeft);
    void setDryGainRight(float newDryGainRight);
    void setWetGainRight(float newWetGainRight);
    void setPreDelay(float newPreDelay);
    void setBandwidth(float newBandwidth);
    void setDecay(float newDecay);
    void setDamping(float newDamping);
    void setAllPassModulationState(bool newState);
private:
    const std::vector<const std::vector<float>> constOutputTapValues = {{0.00893, 0.09980, 0.06420, 0.06698, 0.06678, 0.00628, 0.03578},{0.01180, 0.12170, 0.04120, 0.08970, 0.07080, 0.01120, 0.00410}};
    const std::vector<const std::vector<float>> constValuesAPF = {{0.00476, 0.00358, 0.01272, 0.00929, 0.08914, 0.06041},{0.75, 0.75, 0.625, 0.625, 0.5, 0.5}};
    std::vector<AllPassFilter> allPassFilters;
    const std::vector<float> constValuesFD = {0.14152,0.14943, 0.10524, 0.12483};
    std::vector<DelayElement> fixedDelays;
    const std::vector<const std::vector<float>> constValuesMAPF = {{0.03045, 0.02256}, {0.00028, 0.00028}, {0.7, 0.7}};
    std::vector<ModulatedAllPassFilter> modulatedAllPassFilters;
    std::vector<LowPassFilter1> lowPassFilters;
    float tankEndL;
    float tankEndR;
    float bandwidth;
    float decay;
    float damping;
    float preDelayLength;
    float dryGainL;
    float wetGainL;
    float dryGainR;
    float wetGainR;
    int sampleRate;
    DelayElement preDelay;
    const int modAmplitude = 12;
    const float modFrequency = 1.5;
    
};
