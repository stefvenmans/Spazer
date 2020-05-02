/*
  ==============================================================================

    DDLModule.h
    Created: 19 Apr 2020 6:06:37pm
    Author:  Stef

  ==============================================================================
*/
#include <JuceHeader.h>

#pragma once

class DDLModule
{
public:
    DDLModule();
    ~DDLModule();
    void flushDelayLine();
    float * processAudioBlock(AudioBuffer<float> &, int channel);
    float * processAudioBlock(AudioBuffer<float> &, float*);
    void setParameters(float feedBackPct, float wetLevelPct, float delayMs, int totalDelayTime, int sampleRate);
    void setSampleRate(int rate);
    void setFeedbackFilter(IIRCoefficients coeff);
private:
    float delayInSamples;
    float feedback;
    float wetLevel;
    
    float * buffer;
    float * outBuffer;
    int readIndex;
    int writeIndex;
    int bufferSize;
    int sampleRate;
    
    IIRFilter feedBackFilter;
    bool feedBackFilterSet;
};
