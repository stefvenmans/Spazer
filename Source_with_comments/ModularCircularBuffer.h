/*
  ==============================================================================

    ModularCircularBuffer.h
    Created: 19 May 2020 10:42:06am
    Author:  Stef

  ==============================================================================
*/

#pragma once

#include "CircularBuffer.h"
#include "WTOscillator.h"

class ModularCircularBuffer : public CircularBuffer{
public:
    ModularCircularBuffer(int bufferSize);
    float getInterpolatedSample(float x);
    float getModulatedSample(float x, waveType modType);
    void setModulationSignal(int modAmplitude,  int modFrequency, int sampleRate);
    
private:
    WTOscillator * modOscillator;
    int modAmplitude;
};
