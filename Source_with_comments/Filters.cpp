/*
  ==============================================================================

    Filters.cpp
    Created: 16 May 2020 6:31:22pm
    Author:  Stef

  ==============================================================================
*/

#include "Filters.h"

// ==== DelayElement

//Creates a DelayElement object with order: order.
DelayElement::DelayElement(int order) : buffer(order)
{
    
}

//Returns a processed sample by the DelayElement.
float DelayElement::processSample(float x)
{
    float y = buffer.getSample();
    buffer.pushSample(x);
    return y;
}

//Sets the dynamic order of the CircularBuffer.
void DelayElement::setDynamicOrder(int newOrder)
{
    buffer.setDynamicBufferSize(newOrder);
}

//Return a sample from the circular buffer of "samplesBack" number of samples back in time.
float DelayElement::getFromDelayLine(int samplesBack)
{
    int index = buffer.getIndex() - samplesBack - 1;
    if (index < 0){
        index += buffer.size();
    }
    
    return buffer.getSampleAt(index);
}

// ==== LowPassFilter1

//Creates a first order low-pass filter object.
LowPassFilter1::LowPassFilter1(float a0, float b0) : buffer{1}, a0{a0}, b0{b0}
{

}

//Returns a processed sample from the low-pass filter.
float LowPassFilter1::processSample(float x)
{
    float y = a0*x + b0*buffer.getSample();
    buffer.pushSample(y);
    return y;
}

//Sets the coefficients of the low pass filter.
void LowPassFilter1::setCoefficient(float a0, float b0)
{
    this->a0 = a0;
    this->b0 = b0;
}

// ==== AllPassFilter

//Creates a all-pass filter object.
AllPassFilter::AllPassFilter(float g, int order) : buffer{order}, g{g}
{
    
}

//Returns a processesed sample by the all-pass filter.
float AllPassFilter::processSample(float x)
{
    float y = -g*x + buffer.getSample();
    buffer.pushSample(x + g*y);
    return y;
}

//Sets the coefficients of the all-pass filter.
void AllPassFilter::setCoefficient(float g)
{
    this->g = g;
}

//Return a sample from the circular buffer of "samplesBack" number of samples back in time.
float AllPassFilter::getFromDelayLine(int samplesBack)
{
    int index = buffer.getIndex() - samplesBack - 1;
    if (index < 0){
        index += buffer.size();
    }
    
    return buffer.getSampleAt(index);
}

// ==== ModulatedAllPassFilter

//Creates a modulated all-pass filter object.
ModulatedAllPassFilter::ModulatedAllPassFilter(float g, int maxOrder, int modAmplitude, float modFrequency, int sampleRate) : buffer{maxOrder}, g{g}, sampleRate{sampleRate}
{
    buffer.setModulationSignal(modAmplitude, modFrequency, sampleRate);
}

//Returns a processesed sample by the modulated all-pass filter.
float ModulatedAllPassFilter::processSample(float x)
{
    float y = -g*x + buffer.getModulatedSample(x, SINE);
    buffer.pushSample(x + g*y);
    return y;
}

//Sets the coefficient of the all-pass filter.
void ModulatedAllPassFilter::setCoefficient(float g)
{
    this->g = g;
}

//Sets the modulation signal of the all-pass filter.
void ModulatedAllPassFilter::setModulation(int modAmplitude, float modFrequency)
{
    buffer.setModulationSignal(modAmplitude, modFrequency, sampleRate);
}

// ==== CombFilter

//Creates a comb filter object.
CombFilter::CombFilter(float g, int order) : buffer{order}, g{g}
{
   
}

//Returns a processesed sample from the comb filter.
float CombFilter::processSample(float x)
{
    float y = buffer.getSample();
    buffer.pushSample(x + g*y);
    return y;
}

//Sets the coefficient from the comb filter.
void CombFilter::setCoefficient(float g)
{
    this->g = g;
}

//Return a sample from the circular buffer of "samplesBack" number of samples back in time.
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

