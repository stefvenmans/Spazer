/*
  ==============================================================================

    CircularBuffer.h
    Created: 16 May 2020 5:48:35pm
    Author:  Stef

  ==============================================================================
*/

#pragma once

#include <vector>
#include <iostream>

class CircularBuffer{
public:
    CircularBuffer(int bufferSize);
    size_t size();
    void size(int newBufferSize);
    int getIndex();
    float getSample();
    float getSampleAt(int sampleIndex);
    void pushSample(float sample);
    void setDynamicState(bool newState);
    void setDynamicBufferSize(float newSize);
    
protected:
    std::vector<float> buffer;
    int readIndex;
    int writeIndex;
    bool dynamicState;
    float dynamicBufferSize;
    
};
