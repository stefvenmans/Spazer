/*
  ==============================================================================

    WTOscillator.h
    Created: 22 Apr 2020 9:41:45pm
    Author:  Stef

  ==============================================================================
*/

#pragma once

enum waveType{SINE,TRIANGLE,SQUARE,SAW};

class WTOscillator
{
public:
    WTOscillator(int size);
    ~WTOscillator();
    void resetReadIndex();
    float ** getProcessedBlock(int samplesPerBlock, waveType type);
    void setFrequency(float frequency, int sampleRate);
    
private:
    float readIndex;
    float quadPhaseReadIndex;
    bool invert;
    float ** outBuffer;
    float * sineTable;
    float * triangleTable;
    float * squareTable;
    float * sawTable;
    float frequencyIncVal;
    int tableSize;

};
