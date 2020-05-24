/*
  ==============================================================================

    MoorerReverb.cpp
    Created: 16 May 2020 8:02:52pm
    Author:  Stef

  ==============================================================================
*/

#include "MoorerReverb.h"
#include <iostream>

MoorerReverb::MoorerReverb(int sampleRate, float dryGain, float wetGain) : allPassFilter{presetValues[1][6],(int)(presetValues[0][6]*sampleRate)}, sampleRate{sampleRate}, dryGain{dryGain}, wetGain{wetGain}
{
    for(int i=0; i<6; i++){
        lowPassCombFilters.push_back(LowPassCombFilter{presetValues[1][i], 1.0, presetValues[2][i], (int)(presetValues[0][i]*sampleRate)});
    }
}

float MoorerReverb::processSample(float x)
{
    float y;
    float w = 0.0;
    for(auto it = lowPassCombFilters.begin() ; it != lowPassCombFilters.end(); it++){
        w += it->processSample(x);
    }
    y = allPassFilter.processSample(w);
    return y;
}

void MoorerReverb::processBlock(AudioBuffer<float>& buffer){
    float x,y;
    float w;
    
    for(auto i=0; i<buffer.getNumSamples(); i++){
    
        x = 0.0;
        w = 0.0;
        
        for(auto n=0; n<buffer.getNumChannels(); n++){
            auto * readPointer = buffer.getReadPointer(n);
            x += 0.5*readPointer[i];
        }
        
        for(auto it = lowPassCombFilters.begin() ; it != lowPassCombFilters.end(); it++){
            w += it->processSample(x);
        }
        
        y = allPassFilter.processSample(w);
        
        for(auto n=0; n<buffer.getNumChannels(); n++){
            auto * writePointer = buffer.getWritePointer(n);
            writePointer[i] = dryGain*x + wetGain*y;
        };
    }
}

void MoorerReverb::setDryGain(float newDryGain)
{
    this->dryGain = newDryGain/100.0;
}

void MoorerReverb::setWetGain(float newWetGain)
{
    this->wetGain = newWetGain/100.0;
}

void MoorerReverb::setReverbTime(float newReverbTime){
    for(int i=0; i<6; i++){
        presetValues[1][i] = pow(10,((-3.0*presetValues[0][i])/newReverbTime));
        presetValues[2][i] = totalGain*(1-presetValues[1][i]);
        lowPassCombFilters[i].setCoefficient(presetValues[1][i], 1, presetValues[2][i]);
    }
}
