/*
  ==============================================================================

    Filters.h
    Created: 16 May 2020 6:31:22pm
    Author:  Stef

  ==============================================================================
*/

#pragma once

#include "CircularBuffer.h"
#include "ModularCircularBuffer.h"
#include "WTOscillator.h"

class DelayElement{
public:
    DelayElement(int order);
    float processSample(float x);
    void setDynamicOrder(int newOrder);
    float getFromDelayLine(int samplesBack);
private:
    CircularBuffer buffer;
};

class LowPassFilter1{
public:
    LowPassFilter1(float a0, float b0);
    float processSample(float x);
    void setCoefficient(float a0, float b0);
private:
    CircularBuffer buffer;
    float a0;
    float b0;
};

class AllPassFilter{
public:
    AllPassFilter(float g, int order);
    float processSample(float x);
    void setCoefficient(float g);
    float getFromDelayLine(int samplesBack);
private:
    CircularBuffer buffer;
    float g;
};

class ModulatedAllPassFilter{
public:
    ModulatedAllPassFilter(float g, int maxOrder, int modAmplitude, float modFrequency, int sampleRate);
    float processSample(float x);
    void setCoefficient(float g);
    void setModulation(int modAmplitude, float modFrequency);
private:
    ModularCircularBuffer buffer;
    float g;
    int sampleRate;
};

class CombFilter{
public:
    CombFilter(float g, int order);
    float processSample(float x);
    void setCoefficient(float g);
    float getFromDelayLine(int samplesBack);
private:
    CircularBuffer buffer;
    float g;
};

class LowPassCombFilter{
public:
    LowPassCombFilter(float g, float a0, float b0, int order);
    float processSample(float x);
    void setCoefficient(float g, float a0, float b0);
    float getFromDelayLine(int samplesBack);
private:
    CircularBuffer buffer;
    LowPassFilter1 lowPassFilter;
    float g;
};
