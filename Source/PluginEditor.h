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
class SpazerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SpazerAudioProcessorEditor (SpazerAudioProcessor&);
    ~SpazerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpazerAudioProcessor& processor;
    
    Slider delayLeftMs;
    Slider delayLeftFb;
    Slider delayLeftWet;
    Slider delayLeftFilter;
    Slider delayRightMs;
    Slider delayRightFb;
    Slider delayRightWet;
    Slider delayRightFilter;
    
    Slider reverbLeftDrySlider;
    Slider reverbLeftWetSlider;
    Slider reverbRightDrySlider;
    Slider reverbRightWetSlider;
    Slider reverbPreDelaySlider;
    Slider reverbBandwidthSlider;
    Slider reverbDecaySlider;
    Slider reverbDampingSlider;
    Slider reverbReverbTimeSlider;
    TextButton reverbAPFModulationButton;
    
    Label delayLeftMsLabel;
    Label delayLeftFbLabel;
    Label delayLeftWetLabel;
    Label delayLeftFilterLabel;
    Label delayRightMsLabel;
    Label delayRightFbLabel;
    Label delayRightWetLabel;
    Label delayRightFilterLabel;
    
    Label reverbLeftDryLabel;
    Label reverbLeftWetLabel;
    Label reverbRightDryLabel;
    Label reverbRightWetLabel;
    Label reverbPreDelayLabel;
    Label reverbBandwidthLabel;
    Label reverbDecayLabel;
    Label reverbDampingLabel;
    Label reverbReverbTimeLabel;
    Label reverbAPFModulationLabel;
    
    ComboBox delayLeftNoteLength;
    ComboBox delayRightNoteLength;
    ComboBox reverbTypeComboBox;
    BoxLookAndFeel newLandf;
    
    Array<float> noteLengths;
    bool userSetNoteLength;
    
    Label bpmTestLabel;
    ComboBox testBox;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayLeftMsAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayLeftFbAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayLeftWetAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayLeftFilterAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mDelayLeftNoteLengthAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayRightMsAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayRightFbAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayRightWetAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDelayRightFilterAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mDelayRightNoteLengthAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbLeftDryAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbLeftWetAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbRightDryAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbRightWetAttachment;
    
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> reverbTypeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbPreDelayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbBandwidthAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbDecayAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbDampingAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> reverbReverbTimeAttachment;
    
    
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> reverbAPFModulationAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpazerAudioProcessorEditor)
};
