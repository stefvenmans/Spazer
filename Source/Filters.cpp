/*
  ==============================================================================

    Filters.cpp
    Created: 16 May 2020 6:31:22pm
    Author:  Stef

  ==============================================================================
*/

#include "Filters.h"

// ==== DelayElement

DelayElement::DelayElement(int order) : buffer(order)
{
    
}

float DelayElement::processSample(float x)
{
    float y = buffer.getSample();
    buffer.pushSample(x);
    return y;
}

void DelayElement::setDynamicOrder(int newOrder)
{
    buffer.setDynamicBufferSize(newOrder);
}

float DelayElement::getFromDelayLine(int samplesBack)
{
    int index = buffer.getIndex() - samplesBack - 1;
    if (index < 0){
        index += buffer.size();
    }
    
    return buffer.getSampleAt(index);
}

// ==== LowPassFilter1

LowPassFilter1::LowPassFilter1(float a0, float b0) : buffer{1}, a0{a0}, b0{b0}
{

}

float LowPassFilter1::processSample(float x)
{
    float y = a0*x + b0*buffer.getSample();
    buffer.pushSample(y);
    return y;
}

void LowPassFilter1::setCoefficient(float a0, float b0)
{
    this->a0 = a0;
    this->b0 = b0;
}

// ==== AllPassFilter

AllPassFilter::AllPassFilter(float g, int order) : buffer{order}, g{g}
{
    
}

float AllPassFilter::processSample(float x)
{
    float y = -g*x + buffer.getSample();
    buffer.pushSample(x + g*y);
    return y;
}

void AllPassFilter::setCoefficient(float g)
{
    this->g = g;
}

float AllPassFilter::getFromDelayLine(int samplesBack)
{
    int index = buffer.getIndex() - samplesBack - 1;
    if (index < 0){
        index += buffer.size();
    }
    
    return buffer.getSampleAt(index);
}

// ==== ModulatedAllPassFilter

ModulatedAllPassFilter::ModulatedAllPassFilter(float g, int maxOrder, int modAmplitude, float modFrequency, int sampleRate) : buffer{maxOrder}, g{g}, sampleRate{sampleRate}
{
    buffer.setModulationSignal(modAmplitude, modFrequency, sampleRate);
}

float ModulatedAllPassFilter::processSample(float x)
{
    float y = -g*x + buffer.getModulatedSample(x, SINE);
    buffer.pushSample(x + g*y);
    return y;
}

void ModulatedAllPassFilter::setCoefficient(float g)
{
    this->g = g;
}

void ModulatedAllPassFilter::setModulation(int modAmplitude, float modFrequency)
{
    buffer.setModulationSignal(modAmplitude, modFrequency, sampleRate);
}

// ==== CombFilter

CombFilter::CombFilter(float g, int order) : buffer{order}, g{g}
{
   
}

float CombFilter::processSample(float x)
{
    float y = buffer.getSample();
    buffer.pushSample(x + g*y);
    return y;
}

void CombFilter::setCoefficient(float g)
{
    this->g = g;
}

float CombFilter::getFromDelayLine(int samplesBack)
{
    int index = buffer.getIndex() - samplesBack - 1;
    if (index < 0){
        index += buffer.size();
    }
    
    return buffer.getSampleAt(index);
}

// ==== LowPassCombFilter

LowPassCombFilter::LowPassCombFilter(float g, float a0, float b0, int order) : buffer{order}, lowPassFilter{a0, b0}, g{g}
{
    
}

float LowPassCombFilter::processSample(float x)
{
    float y = buffer.getSample();
    buffer.pushSample(x + g*(lowPassFilter.processSample(y)));
    return y;
}

void LowPassCombFilter::setCoefficient(float g, float a0, float b0)
{
    this->g = g;
    this->lowPassFilter.setCoefficient(a0, b0);
}

float LowPassCombFilter::getFromDelayLine(int samplesBack)
{
    int index = buffer.getIndex() - samplesBack - 1;
    if (index < 0){
        index += buffer.size();
    }
    
    return buffer.getSampleAt(index);
}

