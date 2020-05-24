/*
  ==============================================================================

    WTOscillator.cpp
    Created: 22 Apr 2020 9:41:45pm
    Author:  Stef

  ==============================================================================
*/

//==This class contains the implementation of a wave table oscilattor.

#include "WTOscillator.h"
#include <iostream>
#include <math.h>

WTOscillator::WTOscillator(int size){
    sineTable = new float[size];
    triangleTable = new float[size];
    squareTable = new float[size];
    sawTable = new float[size];
    outBuffer = NULL;
    frequencyIncVal = 1.0;
    readIndex = 0.0;
    tableSize = size;
    
    // Sine table
    for(int i=0; i<size; i++){
        sineTable[i] = sin(((float)i/(float)size)*(2*M_PI));
    }
    
    // Triangle table
    float tSlope = 1.0/((float)size/4.0);
    for(int i=0; i<size; i++){
        if(i<=size/4){
            triangleTable[i] = i*tSlope;
        }
        else if(i<=3*size/4){
            triangleTable[i] = 2.0 - i*tSlope;
        }
        else {
            triangleTable[i] = (4.0 - i*tSlope)*(-1.0);
        }
    }
    
    // Square table
    for(int i=0; i<size; i++){
        if(i<=size/2){
            squareTable[i] = 1.0;
        }
        else{
            squareTable[i] = -1.0;
        }
    }
    
    // Saw table;
    float sSlope = 2.0/(float)size;
    for (int i=0; i<size; i++){
        sawTable[i] = -1.0 + sSlope*i;
    }
}

WTOscillator::~WTOscillator(){
    delete [] sineTable;
    delete [] triangleTable;
    delete [] squareTable;
    delete [] sawTable;
}

float ** WTOscillator::getBlock(int samplesPerBlock, waveType type){
    outBuffer = new float*[2];
    outBuffer[0] = new float[samplesPerBlock];
    outBuffer[1] = new float[samplesPerBlock];
    
    int discreteReadIndex;
    float fraction;
    int readIndexNext;
    
    for (int i=0; i<samplesPerBlock; i++){
        switch(type){
            case SINE:
                discreteReadIndex = (int)readIndex;
                fraction = readIndex - discreteReadIndex;
                readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
                
                // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
                outBuffer[0][i] = (sineTable[discreteReadIndex]*(1-fraction)+sineTable[readIndexNext]*(fraction));
                
                readIndex += frequencyIncVal;
                if(readIndex > tableSize){
                    readIndex = readIndex - tableSize;
                }
                
                break;
                
            case TRIANGLE:
                discreteReadIndex = (int)readIndex;
                fraction = readIndex - discreteReadIndex;
                readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
                
                // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
                outBuffer[0][i] = (triangleTable[discreteReadIndex]*(1-fraction)+triangleTable[readIndexNext]*(fraction));
                
                readIndex += frequencyIncVal;
                if(readIndex > tableSize){
                    readIndex = readIndex - tableSize;
                }
                
                break;
                
            case SQUARE:
                discreteReadIndex = (int)readIndex;
                fraction = readIndex - discreteReadIndex;
                readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
                
                // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
                outBuffer[0][i] = (squareTable[discreteReadIndex]*(1-fraction)+squareTable[readIndexNext]*(fraction));
                
                readIndex += frequencyIncVal;
                if(readIndex > tableSize){
                    readIndex = readIndex - tableSize;
                }
                
                break;
                
            case SAW:
                discreteReadIndex = (int)readIndex;
                fraction = readIndex - discreteReadIndex;
                readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
                
                // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
                outBuffer[0][i] = (sawTable[discreteReadIndex]*(1-fraction)+sawTable[readIndexNext]*(fraction));
                
                readIndex += frequencyIncVal;
                if(readIndex > tableSize){
                    readIndex = readIndex - tableSize;
                }
                
                break;
        }
    }
    return outBuffer;
}

float WTOscillator::getSample(waveType type)
{
    float y;
    
    int discreteReadIndex;
    float fraction;
    int readIndexNext;
    
    switch(type){
        case SINE:
            discreteReadIndex = (int)readIndex;
            fraction = readIndex - discreteReadIndex;
            readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
            
            // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
            y = (sineTable[discreteReadIndex]*(1-fraction)+sineTable[readIndexNext]*(fraction));
            
            readIndex += frequencyIncVal;
            if(readIndex > tableSize){
                readIndex = readIndex - tableSize;
            }
            
            break;
            
        case TRIANGLE:
            discreteReadIndex = (int)readIndex;
            fraction = readIndex - discreteReadIndex;
            readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
            
            // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
            y = (triangleTable[discreteReadIndex]*(1-fraction)+triangleTable[readIndexNext]*(fraction));
            
            readIndex += frequencyIncVal;
            if(readIndex > tableSize){
                readIndex = readIndex - tableSize;
            }
            
            break;
            
        case SQUARE:
            discreteReadIndex = (int)readIndex;
            fraction = readIndex - discreteReadIndex;
            readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
            
            // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
            y = (squareTable[discreteReadIndex]*(1-fraction)+squareTable[readIndexNext]*(fraction));
            
            readIndex += frequencyIncVal;
            if(readIndex > tableSize){
                readIndex = readIndex - tableSize;
            }
            
            break;
            
        case SAW:
            discreteReadIndex = (int)readIndex;
            fraction = readIndex - discreteReadIndex;
            readIndexNext = discreteReadIndex > tableSize ? 0 : discreteReadIndex + 1;
            
            // Linear interpolation y = (y0(x1-x)+y(x-x0))/x1-x0
            y = (sawTable[discreteReadIndex]*(1-fraction)+sawTable[readIndexNext]*(fraction));
            
            readIndex += frequencyIncVal;
            if(readIndex > tableSize){
                readIndex = readIndex - tableSize;
            }
            
            break;
        default:
            y = 0.0;
    }
    return y;
}

void WTOscillator::setFrequency(float frequency, int sampleRate)
{
    frequencyIncVal = ((float)tableSize*frequency)/((float)sampleRate);
}
