/*
  ==============================================================================

    DDLModule.cpp
    Created: 19 Apr 2020 6:06:37pm
    Author:  Stef

  ==============================================================================
*/

#include "DDLModule.h"
#include <iostream>

DDLModule::DDLModule(){
    buffer = NULL;
    outBuffer = NULL;
    feedBackFilterSet = false;
    
    delayInSamples = 0.0;
    feedback = 0.0;
    wetLevel = 0.0;
    
    readIndex = 0;
    writeIndex = 0;
    bufferSize = 0;
    sampleRate = -1;
}

DDLModule::~DDLModule(){
    delete [] buffer;
}

float * DDLModule::processAudioBlock(AudioBuffer<float> & b, int channel){
    if(channel<!b.getNumChannels()){
        return NULL;
    }

    outBuffer = new float[b.getNumSamples()];
    auto * inBuffer = b.getReadPointer(channel);
    auto * bOut = b.getWritePointer(channel);
    
    float yn;
    float yn_1;
    float fracDelay;
    float interP;
    int readIndex_1;
    
    for(auto i=0; i<b.getNumSamples(); i++){
        yn = buffer[readIndex];
        
        if(readIndex == writeIndex && delayInSamples < 1.0){
            yn = inBuffer[i];
        }
        
        readIndex_1 = readIndex-1;
        if(readIndex_1<0){
            readIndex_1 = bufferSize - 1;
        }
        
        yn_1 = buffer[readIndex_1];
        
        // yn_1 ??
        fracDelay = delayInSamples - (int)delayInSamples;
        interP = (yn*(1-fracDelay)+yn*(fracDelay));
        
        if(delayInSamples == 0){
            yn = inBuffer[i];
        }
        else{
            yn = interP;
        }
        
        if(feedBackFilterSet){
            buffer[writeIndex] = feedBackFilter.processSingleSampleRaw(inBuffer[i] + feedback*yn);
        }
        else{
            buffer[writeIndex] = inBuffer[i] + feedback*yn;
        }
        
        writeIndex++;
        if(writeIndex >= bufferSize){
            writeIndex = 0;
        }
    
        readIndex++;
        if(readIndex >= bufferSize){
            readIndex = 0;
        }
        outBuffer[i] = wetLevel*yn + (1.0 - wetLevel)*inBuffer[i];
        bOut[i] = wetLevel*yn + (1.0 - wetLevel)*inBuffer[i];
    }
    return outBuffer;
}

void DDLModule::setParameters(float feedBackPct, float wetLevelPct, float delayMs, int totalDelayTime, int newSampleRate){
    if(sampleRate != newSampleRate){
        bufferSize = totalDelayTime*newSampleRate;
        flushDelayLine();
        std::cout << "dbg" <<std::endl;
    }
    feedback = feedBackPct/100.0;
    wetLevel = wetLevelPct/100.0;
    delayInSamples = delayMs * (float)(sampleRate/1000.0);
    
    readIndex = writeIndex - (int)delayInSamples;
    if(readIndex < 0){
        readIndex += bufferSize;
    }
    sampleRate = newSampleRate;
}

void DDLModule::flushDelayLine(){
    if(buffer){
        delete [] buffer;
    }
    buffer = new float [bufferSize];
    memset(buffer, 0, bufferSize*sizeof(float));
    writeIndex = 0;
    readIndex = 0;
    
}

float * DDLModule::processAudioBlock(AudioBuffer<float> & b, float * mod){
    outBuffer = new float[b.getNumSamples()];
    auto * inBuffer = b.getReadPointer(0);
    
    float yn;
    float yn_1;
    float fracDelay;
    float interP;
    int readIndex_1;
    
    for(auto i=0; i<b.getNumSamples(); i++){
        yn = buffer[readIndex];
        
        if(readIndex == writeIndex && delayInSamples < 1.0){
            yn = inBuffer[i];
        }
        
        readIndex_1 = readIndex-1;
        if(readIndex_1<0){
            readIndex_1 = bufferSize - 1;
        }
        
        yn_1 = buffer[readIndex_1];
        
        // yn_1 ??
        fracDelay = delayInSamples - (int)delayInSamples;
        interP = (yn*(1-fracDelay)+yn_1*(fracDelay));
        
        if(delayInSamples == 0){
            yn = inBuffer[i];
        }
        else{
            yn = interP;
        }
        
        if(feedBackFilterSet){
            buffer[writeIndex] = feedBackFilter.processSingleSampleRaw(inBuffer[i] + feedback*yn);
        }
        else{
            buffer[writeIndex] = inBuffer[i] + feedback*yn;
        }
        setParameters(feedback*100.0, wetLevel*100.0, abs(mod[i])*6.0, 2, 44100);
        
        writeIndex++;
        if(writeIndex >= bufferSize){
            writeIndex = 0;
        }
    
        readIndex++;
        if(readIndex >= bufferSize){
            readIndex = 0;
        }
        outBuffer[i] = wetLevel*yn + (1.0 - wetLevel)*inBuffer[i];
        
    }
    return outBuffer;
}

void DDLModule::setFeedbackFilter(IIRCoefficients coeff){
    if(!feedBackFilterSet){
        feedBackFilterSet = true;
    }
    feedBackFilter.setCoefficients(coeff);
}
