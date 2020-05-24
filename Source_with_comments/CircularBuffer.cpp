/*
  ==============================================================================

    CircularBuffer.cpp
    Created: 16 May 2020 5:48:35pm
    Author:  Stef
  ==============================================================================
*/

#include "CircularBuffer.h"

//Creates a circular buffer object with size: bufferSize.
CircularBuffer::CircularBuffer(int bufferSize)
{
    readIndex = 0;
    writeIndex = 0;
    dynamicBufferSize = 0.0;
    dynamicState = false;
    buffer = std::vector<float>(bufferSize,0);
    std::fill(buffer.begin(), buffer.end(), 0.0);
}

//Returns the size of the circular buffer.
size_t CircularBuffer::size()
{
    return buffer.size();
}

//Sets the size of the circular buffer.
void CircularBuffer::size(int newBufferSize)
{
    buffer = std::vector<float>(newBufferSize, 0);
}

//Returns the current readindex of the circular buffer.
int CircularBuffer::getIndex()
{
    return readIndex;
}

//Returns the sample at the current readindex and increments the readindex. It also wraps the readindex if it reaches the end of the buffer.
float CircularBuffer::getSample()
{
    float element =  buffer[readIndex];
    readIndex++;
    
    if(readIndex == size()){
        readIndex = 0;
    }
    
    return element;
}

//Returns a sample at a specific index of the buffer.
float CircularBuffer::getSampleAt(int sampleIndex)
{
    float element = buffer[sampleIndex];
    return element;
}

//Pushes a new sample on the circular buffer and increments the write infex. It also wraps the writeindex if it reaches the end of the buffer.
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

//Set a dynamic buffer size which implies different read and write indices.
void CircularBuffer::setDynamicBufferSize(float newSize)
{
    dynamicBufferSize = newSize;
    readIndex = writeIndex - dynamicBufferSize;
    if(readIndex<0){
        readIndex += buffer.size();
    }
}


