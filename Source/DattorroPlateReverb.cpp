/*
  ==============================================================================

    DattorroPlateReverb.cpp
    Created: 16 May 2020 9:25:36pm
    Author:  Stef

  ==============================================================================
*/

#include "DattorroPlateReverb.h"

DattorroPlateReverb::DattorroPlateReverb(int sampleRate, float dryGainL, float wetGainL, float dryGainR, float wetGainR) : tankEndL{0.0}, tankEndR{0.0}, bandwidth{0.9995}, decay{0.5}, damping{0.0005}, preDelayLength{0.02}, dryGainL{dryGainL}, wetGainL{wetGainL}, dryGainR{dryGainR}, wetGainR{wetGainR}, sampleRate{sampleRate}, preDelay{int(preDelayLength*sampleRate)}
{
    lowPassFilters.push_back(LowPassFilter1{bandwidth, 1-bandwidth});
    lowPassFilters.push_back(LowPassFilter1{1-damping, damping});
    lowPassFilters.push_back(LowPassFilter1{1-damping, damping});
    
    allPassFilters.push_back(AllPassFilter{-constValuesAPF[1][0], (int)(constValuesAPF[0][0]*sampleRate)});
    allPassFilters.push_back(AllPassFilter{-constValuesAPF[1][1], (int)(constValuesAPF[0][1]*sampleRate)});
    allPassFilters.push_back(AllPassFilter{-constValuesAPF[1][2], (int)(constValuesAPF[0][2]*sampleRate)});
    allPassFilters.push_back(AllPassFilter{-constValuesAPF[1][3], (int)(constValuesAPF[0][3]*sampleRate)});
    allPassFilters.push_back(AllPassFilter{-constValuesAPF[1][4], (int)(constValuesAPF[0][4]*sampleRate)});
    allPassFilters.push_back(AllPassFilter{-constValuesAPF[1][5], (int)(constValuesAPF[0][5]*sampleRate)});
    
    modulatedAllPassFilters.push_back(ModulatedAllPassFilter{constValuesMAPF[1][0], (int)(constValuesMAPF[0][0]*sampleRate), 0, 3, sampleRate});
    modulatedAllPassFilters.push_back(ModulatedAllPassFilter{constValuesMAPF[1][1], (int)(constValuesMAPF[0][1]*sampleRate), 0, 3, sampleRate});
    
    fixedDelays.push_back(DelayElement{(int)(constValuesFD[0]*sampleRate)});
    fixedDelays.push_back(DelayElement{(int)(constValuesFD[1]*sampleRate)});
    fixedDelays.push_back(DelayElement{(int)(constValuesFD[2]*sampleRate)});
    fixedDelays.push_back(DelayElement{(int)(constValuesFD[3]*sampleRate)});
}

float DattorroPlateReverb::processSample(float x)
{
    float y;
    float w;
    
    w = preDelay.processSample(x);
    
    w = lowPassFilters[0].processSample(w);
    
    w = allPassFilters[0].processSample(w);
    w = allPassFilters[1].processSample(w);
    w = allPassFilters[2].processSample(w);
    w = allPassFilters[3].processSample(w);
    
    float u1, u2;
    
    u1 = modulatedAllPassFilters[0].processSample(w+tankEndR);
    u2 = modulatedAllPassFilters[1].processSample(w+tankEndL);
    
    u1 = fixedDelays[0].processSample(u1);
    u2 = fixedDelays[1].processSample(u2);
    
    u1 = lowPassFilters[1].processSample(u1);
    u2 = lowPassFilters[2].processSample(u2);
    
    u1 = decay*u1;
    u2 = decay*u2;
    
    u1 = allPassFilters[4].processSample(u1);
    u2 = allPassFilters[5].processSample(u2);
    
    u1 = fixedDelays[2].processSample(u1);
    u2 = fixedDelays[3].processSample(u2);
    
    tankEndL = decay*u1;
    tankEndR = decay*u2;
    
    y = 0.0;
    y += fixedDelays[0].getFromDelayLine((int)(constOutputTapValues[0][0]*sampleRate));
    y += fixedDelays[0].getFromDelayLine((int)(constOutputTapValues[0][1]*sampleRate));
    y -= allPassFilters[4].getFromDelayLine((int)(constOutputTapValues[0][2]*sampleRate));
    y += fixedDelays[2].getFromDelayLine((int)(constOutputTapValues[0][3]*sampleRate));
    y -= fixedDelays[1].getFromDelayLine((int)(constOutputTapValues[0][4]*sampleRate));
    y -= allPassFilters[5].getFromDelayLine((int)(constOutputTapValues[0][5]*sampleRate));
    y -= fixedDelays[3].getFromDelayLine((int)(constOutputTapValues[0][6]*sampleRate));
    
    return dryGainL*x + wetGainL*y;;
}

void DattorroPlateReverb::processBlock(AudioBuffer<float>& buffer)
{
    float x,y;
    float w;
    
    for(auto i=0; i<buffer.getNumSamples(); i++){
    
        x = 0.0;
        
        for(auto n=0; n<buffer.getNumChannels(); n++){
            auto * readPointer = buffer.getReadPointer(n);
            x += readPointer[i];
        }
        
        w = preDelay.processSample(x);
        
        w = lowPassFilters[0].processSample(w);
        
        w = allPassFilters[0].processSample(w);
        w = allPassFilters[1].processSample(w);
        w = allPassFilters[2].processSample(w);
        w = allPassFilters[3].processSample(w);
        
        float u1, u2;
        
        u1 = modulatedAllPassFilters[0].processSample(w+tankEndR);
        u2 = modulatedAllPassFilters[1].processSample(w+tankEndL);
        
        u1 = fixedDelays[0].processSample(u1);
        u2 = fixedDelays[1].processSample(u2);
        
        u1 = lowPassFilters[1].processSample(u1);
        u2 = lowPassFilters[2].processSample(u2);
        
        u1 = decay*u1;
        u2 = decay*u2;
        
        u1 = allPassFilters[4].processSample(u1);
        u2 = allPassFilters[5].processSample(u2);
        
        u1 = fixedDelays[2].processSample(u1);
        u2 = fixedDelays[3].processSample(u2);
        
        tankEndL = decay*u1;
        tankEndR = decay*u2;
        
        for(auto n=0; n<buffer.getNumChannels(); n++){
            auto * writePointer = buffer.getWritePointer(n);
    
            y = 0.0;
            
            if(n == 0){
                y += fixedDelays[0].getFromDelayLine((int)(constOutputTapValues[0][0]*sampleRate));
                y += fixedDelays[0].getFromDelayLine((int)(constOutputTapValues[0][1]*sampleRate));
                y -= allPassFilters[4].getFromDelayLine((int)(constOutputTapValues[0][2]*sampleRate));
                y += fixedDelays[2].getFromDelayLine((int)(constOutputTapValues[0][3]*sampleRate));
                y -= fixedDelays[1].getFromDelayLine((int)(constOutputTapValues[0][4]*sampleRate));
                y -= allPassFilters[5].getFromDelayLine((int)(constOutputTapValues[0][5]*sampleRate));
                y -= fixedDelays[3].getFromDelayLine((int)(constOutputTapValues[0][6]*sampleRate));
            
                writePointer[i] = dryGainL*x + wetGainL*y;
            }
            else if(n == 1){
                y += fixedDelays[1].getFromDelayLine((int)(constOutputTapValues[1][0]*sampleRate));
                y += fixedDelays[1].getFromDelayLine((int)(constOutputTapValues[1][1]*sampleRate));
                y -= allPassFilters[5].getFromDelayLine((int)(constOutputTapValues[1][2]*sampleRate));
                y += fixedDelays[3].getFromDelayLine((int)(constOutputTapValues[1][3]*sampleRate));
                y -= fixedDelays[0].getFromDelayLine((int)(constOutputTapValues[1][4]*sampleRate));
                y -= allPassFilters[4].getFromDelayLine((int)(constOutputTapValues[1][5]*sampleRate));
                y -= fixedDelays[2].getFromDelayLine((int)(constOutputTapValues[1][6]*sampleRate));
                
                writePointer[i] = dryGainR*x + wetGainR*y;
            }
        }
    }
}

void DattorroPlateReverb::setDryGainLeft(float newDryGainLeft)
{
    dryGainL = newDryGainLeft/100.0;
}

void DattorroPlateReverb::setWetGainLeft(float newWetGainLeft)
{
    wetGainL = newWetGainLeft/100.0;
}

void DattorroPlateReverb::setDryGainRight(float newDryGainRight)
{
    dryGainR = newDryGainRight/100.0;
}

void DattorroPlateReverb::setWetGainRight(float newWetGainRight)
{
    wetGainR = newWetGainRight/100.0;
}

void DattorroPlateReverb::setPreDelay(float newPreDelay){
    fixedDelays[0].setDynamicOrder((newPreDelay/1000.0)*sampleRate);
}

void DattorroPlateReverb::setBandwidth(float newBandwidth){
    bandwidth = newBandwidth/20000.0;
    lowPassFilters[0].setCoefficient(bandwidth, 1-bandwidth);
}

void DattorroPlateReverb::setDecay(float newDecay){
    decay = newDecay/100.0;
}

void DattorroPlateReverb::setDamping(float newDamping){
    damping = newDamping/100.0;
    lowPassFilters[1].setCoefficient(1-damping, damping);
    lowPassFilters[2].setCoefficient(1-damping, damping);
}

void DattorroPlateReverb::setAllPassModulationState(bool newState){
    if(newState){
        modulatedAllPassFilters[0].setModulation(modAmplitude, modFrequency);
        modulatedAllPassFilters[1].setModulation(modAmplitude, modFrequency);
    }
    else{
        modulatedAllPassFilters[0].setModulation(0, 0);
        modulatedAllPassFilters[1].setModulation(0, 0);
    }
}
