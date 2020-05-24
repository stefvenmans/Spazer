/*
  ==============================================================================

    MoorerReverb.cpp
    Created: 16 May 2020 8:02:52pm
    Author:  Stef

  ==============================================================================
*/

#include "SchroederReverb.h"
#include <iostream>
#include <math.h>

SchroederReverb::SchroederReverb(int sampleRate, float dryGain, float wetGain) : sampleRate{sampleRate}, dryGain{dryGain}, wetGain{wetGain}
{
    for(int i=0; i<2; i++){
        allPassFilters.push_back(AllPassFilter{presetValues[1][3+i],(int)(presetValues[0][3+i]*sampleRate)});
    }
    
    for(int i=0; i<4; i++){
        combFilters.push_back(CombFilter{presetValues[1][i], (int)(presetValues[0][i]*sampleRate)});
    }
}

float SchroederReverb::processSample(float x)
{
    float y;
    float w = 0.0;
    for(auto it = combFilters.begin() ; it != combFilters.end(); it++){
        w += it->processSample(x);
    }
    w = allPassFilters[0].processSample(w);
    y = allPassFilters[1].processSample(w);
    return y;
}

void SchroederReverb::processBlock(AudioBuffer<float>& buffer){
    float x,y;
    float w;
    
    for(auto i=0; i<buffer.getNumSamples(); i++){
    
        x = 0.0;
        w = 0.0;
        
        for(auto n=0; n<buffer.getNumChannels(); n++){
            auto * readPointer = buffer.getReadPointer(n);
            x += 0.5*readPointer[i];
        }
        
        for(auto it = combFilters.begin() ; it != combFilters.end(); it++){
            w += it->processSample(x);
        }
        
        w = allPassFilters[0].processSample(w);
        y = allPassFilters[1].processSample(w);
        
        for(auto n=0; n<buffer.getNumChannels(); n++){
            auto * writePointer = buffer.getWritePointer(n);
            writePointer[i] = dryGain*x + wetGain*y;
        };
    }
}

void SchroederReverb::setDryGain(float newDryGain)
{
    this->dryGain = newDryGain/100.0;
}
void SchroederReverb::setWetGain(float newWetGain)
{
    this->wetGain = newWetGain/100.0;
}

void SchroederReverb::setReverbTime(float newReverbTime)
{
    for(int i=0; i<4; i++){
        presetValues[1][i] = pow(10,((-3.0*presetValues[0][i])/newReverbTime));
        combFilters[i].setCoefficient(presetValues[1][i]);
    }
}
