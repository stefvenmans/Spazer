/*
  ==============================================================================

    CircularBuffer.cpp
    Created: 16 May 2020 5:48:35pm
    Author:  Stef

  ==============================================================================
*/

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int bufferSize)
{
    readIndex = 0;
    writeIndex = 0;
    dynamicBufferSize = 0.0;
    dynamicState = false;
    buffer = std::vector<float>(bufferSize,0);
    std::fill(buffer.begin(), buffer.end(), 0.0);
}

size_t CircularBuffer::size()
{
    return buffer.size();
}

void CircularBuffer::size(int newBufferSize)
{
    buffer = std::vector<float>(newBufferSize, 0);
}

int CircularBuffer::getIndex()
{
    return readIndex;
}

float CircularBuffer::getSample()
{
    float element =  buffer[readIndex];
    readIndex++;
    
    if(readIndex == size()){
        readIndex = 0;
    }
    
    return element;
}

float CircularBuffer::getSampleAt(int sampleIndex)
{
    float element = buffer[sampleIndex];
    return element;
}

void CircularBuffer::pushSample(float sample)
{
    buffer[writeIndex] = sample;
    writeIndex ++;
    if(writeIndex == size()){
        writeIndex = 0;
    }
}

void CircularBuffer::setDynamicState(bool newState)
{
    dynamicState = newState;
}

void CircularBuffer::setDynamicBufferSize(float newSize)
{
    dynamicBufferSize = newSize;
    readIndex = writeIndex - dynamicBufferSize;
    if(readIndex<0){
        readIndex += buffer.size();
    }
}


