/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class BoxLookAndFeel : public LookAndFeel_V4
{
public:
    Font getComboBoxFont(ComboBox&) override
    {
        return getCommonMenuFont();
    }
    Font getPopupMenuFont() override
    {
        return getCommonMenuFont();
    }
private:
    Font getCommonMenuFont(){
        return Font("Avenir Next", "Regular", 12.0f);
    }
};


//==============================================================================
/**
*/
class SpazerAudioProcessorEditor  : public AudioProcessorEditor,
                                    private Slider::Listener,
                                    public Value::Listener
{
public:
    SpazerAudioProcessorEditor (SpazerAudioProcessor&);
    ~SpazerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void valueChanged(Value & value) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpazerAudioProcessor& processor;
    void sliderValueChanged (Slider* slider) override;
    
    
    Slider delayLeftMs;
    Slider delayLeftFb;
    Slider delayLeftWet;
    Slider delayLeftFilter;
    Slider delayRightMs;
    Slider delayRightFb;
    Slider delayRightWet;
    Slider delayRightFilter;
    
    Label delayLeftMsLabel;
    Label delayLeftFbLabel;
    Label delayLeftWetLabel;
    Label delayLeftFilterLabel;
    Label delayRightMsLabel;
    Label delayRightFbLabel;
    Label delayRightWetLabel;
    Label delayRightFilterLabel;
    
    ComboBox delayLeftNoteLength;
    ComboBox delayRightNoteLength;
    BoxLookAndFeel newLandf;
    
    Array<float> noteLengths;
    bool userSetNoteLength;
    
    Label bpmTestLabel;

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpazerAudioProcessorEditor)
};
