/*
  ==============================================================================

    StereoDelay.cpp
    Created: 18 May 2020 12:32:37pm
    Author:  Stef

  ==============================================================================
*/

//==This class contains the implementation of the StereoDelay scheme. It has the same style of implementation as the DattorroPlateReverb.

#include "StereoDelay.h"
#include <math.h>

StereoDelay::StereoDelay(int sampleRate, float totalDelay, float initDelay, float initFeedback, float initBandwidth, float initWetGain) : sampleRate{sampleRate}, totalDelay{totalDelay}
{
    for(auto n=0; n<2; n++){
        buffers.push_back(ModularCircularBuffer{int(totalDelay*sampleRate)});
        delay.push_back(initDelay);
        feedback.push_back(initFeedback);
        bandwidth.push_back(initBandwidth);
        wetGain.push_back(initWetGain);
    
        buffers[n].setDynamicState(true);
        buffers[n].setDynamicBufferSize(delay[n]*sampleRate);
        
        
        float thetaC = (2.0*M_PI*initBandwidth)/((float)sampleRate);
        float gamma = 2 - cos(thetaC);
        float b1 = sqrt(pow(gamma, 2)-1) - gamma;
        float a0 = 1 + b1;
        lowPassFilters.push_back(LowPassFilter1{a0,b1});
    }
}

float StereoDelay::processSample(float x)
{
    float y;
    
    y = buffers[0].getSample();
    buffers[0].pushSample(x + feedback[0]*y);
    y = wetGain[0]*y + (1-wetGain[0])*x;
    
    return y;
}

void StereoDelay::processBuffer(AudioBuffer<float> &buffer)
{
    float y;
    for(auto n=0; n<buffer.getNumChannels(); n++){
        auto * inBuffer = buffer.getReadPointer(n);
        auto * outBuffer = buffer.getWritePointer(n);
        
        for(auto i=0; i<buffer.getNumSamples(); i++){
            y = buffers[n].getInterpolatedSample(inBuffer[i]);
            buffers[n].pushSample(inBuffer[i] + feedback[n]*(lowPassFilters[n].processSample(y)));
            outBuffer[i] = wetGain[n]*y + (1-wetGain[n])*inBuffer[i];
            
        }
    }
}

void StereoDelay::setDelay(int channel, float newDelay)
{
    delay[channel] = newDelay;
    buffers[channel].setDynamicBufferSize(delay[channel]*sampleRate);
}

void StereoDelay::setFeedback(int channel, float newFeedback)
{
    feedback[channel] = newFeedback;
}

void StereoDelay::setBandwidth(int channel, float newBandwidth)
{
    bandwidth[channel] = newBandwidth;
    float thetaC = (2.0*M_PI*newBandwidth)/((float)sampleRate);
    float gamma = 2 - cos(thetaC);
    float b1 = sqrt(pow(gamma, 2)-1) - gamma;
    float a0 = 1 + b1;
    lowPassFilters[channel].setCoefficient(a0, b1);
}

void StereoDelay::setWetGain(int channel, float newWetGain)
{
    wetGain[channel] = newWetGain;
}

