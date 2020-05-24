/*
  ==============================================================================

    ModularCircularBuffer.cpp
    Created: 19 May 2020 10:42:06am
    Author:  Stef

  ==============================================================================
*/

#include "ModularCircularBuffer.h"

//==This class contains the implementation of a circular buffer that can be modulated with an oscilator. It inherents from the normal CircularBuffer class.

ModularCircularBuffer::ModularCircularBuffer(int bufferSize) : CircularBuffer{bufferSize}
{
    
}

float ModularCircularBuffer::getInterpolatedSample(float x)
{
    float y;
    float y_1;
    float fracDelay;
    float interP;
    int readIndex_1;
    
    y = buffer[readIndex];
    
    if(readIndex == writeIndex && dynamicBufferSize < 1.0){
        y = x;
    }
    
    readIndex_1 = readIndex-1;
    if(readIndex_1<0){
        readIndex_1 = (int)buffer.size() - 1;
    }
    
    y_1 = buffer[readIndex_1];
    
    fracDelay = dynamicBufferSize - (int)dynamicBufferSize;
    interP = (y_1*(1-fracDelay)+y*(fracDelay));
        
    if(dynamicBufferSize == 0){
        y = x;
    }
    else{
        y = interP;
    }
    
    readIndex++;
    if(readIndex >= buffer.size()){
        readIndex = 0;
    }
    return y;
}

float ModularCircularBuffer::getModulatedSample(float x, waveType modType)
{
    float y = getInterpolatedSample(x);
    setDynamicBufferSize(buffer.size() - modAmplitude*(1 - modOscillator->getSample(modType)));
    return y;
}

void ModularCircularBuffer::setModulationSignal(int modAmplitude, int modFrequency, int sampleRate)
{
    modOscillator = new WTOscillator{2048};
    modOscillator->setFrequency(modFrequency, sampleRate);
    this->modAmplitude = modAmplitude;
}
