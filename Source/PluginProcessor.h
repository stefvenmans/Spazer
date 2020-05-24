/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DDLModule.h"
#include "WTOscillator.h"
#include "StereoDelay.h"
#include "DattorroPlateReverb.h"
#include "MoorerReverb.h"
#include "SchroederReverb.h"

//==============================================================================
/**
*/
class SpazerAudioProcessor  : public AudioProcessor,
                              public ValueTree::Listener,
                              public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    SpazerAudioProcessor();
    ~SpazerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void valueTreePropertyChanged(ValueTree & treeWhosePropertyHasChanged,const Identifier & property) override;
    void valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded) override{};
    void valueTreeChildRemoved (ValueTree &parentTree, ValueTree &childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override {};
    void valueTreeChildOrderChanged (ValueTree &parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override {};
    void valueTreeParentChanged (ValueTree &treeWhoseParentHasChanged) override{};
    
    //==============================================================================
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //==============================================================================
    void parameterChanged(const String &parameterID, float newValue) override;
    
    void updateNoteLengths();

    AudioProcessorValueTreeState & getAPVTS(){return mAPVTS;}
    

private:
    //==============================================================================
    AudioProcessorValueTreeState mAPVTS;
    StereoDelay * stereoDelay;
    DattorroPlateReverb * plateReverb;
    MoorerReverb * moorerReverb;
    SchroederReverb * schroederReverb;
    float bpmOfDAW;
    std::vector<float> noteLengths;
  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpazerAudioProcessor)
};
