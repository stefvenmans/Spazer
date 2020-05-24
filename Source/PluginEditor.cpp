/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpazerAudioProcessorEditor::SpazerAudioProcessorEditor (SpazerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
    
    delayLeftMs.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftMs.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    delayLeftMs.setPopupDisplayEnabled (true, false, this);
    delayLeftMs.setTextValueSuffix ("ms");
    
    mDelayLeftMsAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(),"delayLeftMs",delayLeftMs);
    
    delayLeftFb.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftFb.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayLeftFb.setPopupDisplayEnabled (true, false, this);
    delayLeftFb.setTextValueSuffix ("%");
    
    mDelayLeftFbAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(),"delayLeftFb",delayLeftFb);
    
    delayLeftWet.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftWet.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayLeftWet.setPopupDisplayEnabled (true, false, this);
    delayLeftWet.setTextValueSuffix ("%");
    
    mDelayLeftWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "delayLeftWet", delayLeftWet);
    
    delayLeftFilter.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftFilter.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayLeftFilter.setPopupDisplayEnabled (true, false, this);
    delayLeftFilter.setTextValueSuffix ("Hz");
    
    mDelayLeftFilterAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "delayLeftFilter", delayLeftFilter);
    
    delayLeftNoteLength.setLookAndFeel(&newLandf);
    delayLeftNoteLength.addItemList(StringArray("1/2d","1/2","1/4d","1/4","1/8d","1/8","1/16d","1/16","1/32d","1/32"), 1);
    mDelayLeftNoteLengthAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(),"delayLeftNoteLength",delayLeftNoteLength);
    
    delayLeftMsLabel.setText("Time (ms)", NotificationType::dontSendNotification);
    delayLeftMsLabel.setFont(Font(12));
    delayLeftMsLabel.setJustificationType(Justification::centred);
    delayLeftMsLabel.attachToComponent(&delayLeftMs, false);
    
    delayLeftFbLabel.setText("Feedback (%)", NotificationType::dontSendNotification);
    delayLeftFbLabel.setFont(Font(12));
    delayLeftFbLabel.setJustificationType(Justification::centred);
    delayLeftFbLabel.attachToComponent(&delayLeftFb, false);
    
    delayLeftWetLabel.setText("Dry/Wet (%)", NotificationType::dontSendNotification);
    delayLeftWetLabel.setFont(Font(12));
    delayLeftWetLabel.setJustificationType(Justification::centred);
    delayLeftWetLabel.attachToComponent(&delayLeftWet, false);
    
    delayLeftFilterLabel.setText("Low Pass (Hz)", NotificationType::dontSendNotification);
    delayLeftFilterLabel.setFont(Font(12));
    delayLeftFilterLabel.setJustificationType(Justification::centred);
    delayLeftFilterLabel.attachToComponent(&delayLeftFilter, false);
    
    addAndMakeVisible (&delayLeftMs);
    addAndMakeVisible(&delayLeftFb);
    addAndMakeVisible(&delayLeftWet);
    addAndMakeVisible(&delayLeftFilter);
    addAndMakeVisible(&delayLeftNoteLength);
    
    delayRightMs.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightMs.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    delayRightMs.setPopupDisplayEnabled (true, false, this);
    delayRightMs.setTextValueSuffix ("ms");

    mDelayRightMsAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "delayRightMs", delayRightMs);
    
    delayRightFb.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightFb.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayRightFb.setPopupDisplayEnabled (true, false, this);
    delayRightFb.setTextValueSuffix ("%");
    
    mDelayRightFbAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "delayRightFb", delayRightFb);

    delayRightWet.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightWet.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayRightWet.setPopupDisplayEnabled (true, false, this);
    delayRightWet.setTextValueSuffix ("%");
    
    mDelayRightWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "delayRightWet", delayRightWet);

    delayRightFilter.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightFilter.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayRightFilter.setPopupDisplayEnabled (true, false, this);
    delayRightFilter.setTextValueSuffix ("Hz");
    
    mDelayRightFilterAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "delayRightFilter", delayRightFilter);
    
    delayRightNoteLength.setLookAndFeel(&newLandf);
    delayRightNoteLength.addItemList(StringArray("1/2d","1/2","1/4d","1/4","1/8d","1/8","1/16d","1/16","1/32d","1/32"), 1);
    mDelayRightNoteLengthAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(),"delayRightNoteLength",delayRightNoteLength);
//    resp = processor.getAPVTS().getParameter("delayRightNoteLength");
//    testBox.setSelectedId(((AudioParameterChoice*)resp)->getIndex()+1);

    delayRightMsLabel.setText("Time (ms)", NotificationType::dontSendNotification);
    delayRightMsLabel.setFont(Font(12));
    delayRightMsLabel.setJustificationType(Justification::centred);
    delayRightMsLabel.attachToComponent(&delayRightMs, false);

    delayRightFbLabel.setText("Feedback (%)", NotificationType::dontSendNotification);
    delayRightFbLabel.setFont(Font(12));
    delayRightFbLabel.setJustificationType(Justification::centred);
    delayRightFbLabel.attachToComponent(&delayRightFb, false);

    delayRightWetLabel.setText("Dry/Wet (%)", NotificationType::dontSendNotification);
    delayRightWetLabel.setFont(Font(12));
    delayRightWetLabel.setJustificationType(Justification::centred);
    delayRightWetLabel.attachToComponent(&delayRightWet, false);

    delayRightFilterLabel.setText("Low Pass (Hz)", NotificationType::dontSendNotification);
    delayRightFilterLabel.setFont(Font(12));
    delayRightFilterLabel.setJustificationType(Justification::centred);
    delayRightFilterLabel.attachToComponent(&delayRightFilter, false);
    
    addAndMakeVisible (&delayRightMs);
    addAndMakeVisible(&delayRightFb);
    addAndMakeVisible(&delayRightWet);
    addAndMakeVisible(&delayRightFilter);
    addAndMakeVisible(&delayRightNoteLength);
    
    reverbLeftDrySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbLeftDrySlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbLeftDrySlider.setPopupDisplayEnabled (true, false, this);
    reverbLeftDrySlider.setTextValueSuffix ("%");

    reverbLeftDryAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbLeftDry", reverbLeftDrySlider);
    
    reverbLeftWetSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbLeftWetSlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbLeftWetSlider.setPopupDisplayEnabled (true, false, this);
    reverbLeftWetSlider.setTextValueSuffix ("%");

    reverbLeftWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbLeftWet", reverbLeftWetSlider);
    
    reverbRightDrySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbRightDrySlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbRightDrySlider.setPopupDisplayEnabled (true, false, this);
    reverbRightDrySlider.setTextValueSuffix ("%");

    reverbRightDryAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbRightDry", reverbRightDrySlider);
    
    reverbRightWetSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbRightWetSlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbRightWetSlider.setPopupDisplayEnabled (true, false, this);
    reverbRightWetSlider.setTextValueSuffix ("%");

    reverbRightWetAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbRightWet", reverbRightWetSlider);
    
    reverbLeftDryLabel.setText("Dry (%)", NotificationType::dontSendNotification);
    reverbLeftDryLabel.setFont(Font(12));
    reverbLeftDryLabel.setJustificationType(Justification::centred);
    reverbLeftDryLabel.attachToComponent(&reverbLeftDrySlider, false);
    
    reverbLeftWetLabel.setText("Wet (%)", NotificationType::dontSendNotification);
    reverbLeftWetLabel.setFont(Font(12));
    reverbLeftWetLabel.setJustificationType(Justification::centred);
    reverbLeftWetLabel.attachToComponent(&reverbLeftWetSlider, false);
    
    reverbRightDryLabel.setText("Dry (%)", NotificationType::dontSendNotification);
    reverbRightDryLabel.setFont(Font(12));
    reverbRightDryLabel.setJustificationType(Justification::centred);
    reverbRightDryLabel.attachToComponent(&reverbRightDrySlider, false);
    
    reverbRightWetLabel.setText("Wet (%)", NotificationType::dontSendNotification);
    reverbRightWetLabel.setFont(Font(12));
    reverbRightWetLabel.setJustificationType(Justification::centred);
    reverbRightWetLabel.attachToComponent(&reverbRightWetSlider, false);
    
    addAndMakeVisible(&reverbLeftDrySlider);
    addAndMakeVisible(&reverbLeftWetSlider);
    addAndMakeVisible(&reverbRightDrySlider);
    addAndMakeVisible(&reverbRightWetSlider);
    
    reverbPreDelaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbPreDelaySlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbPreDelaySlider.setPopupDisplayEnabled (true, false, this);
    reverbPreDelaySlider.setTextValueSuffix ("ms");

    reverbPreDelayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbPreDelay", reverbPreDelaySlider);
    
    reverbBandwidthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbBandwidthSlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbBandwidthSlider.setPopupDisplayEnabled (true, false, this);
    reverbBandwidthSlider.setTextValueSuffix ("Hz");

    reverbBandwidthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbBandwidth", reverbBandwidthSlider);
    
    reverbDecaySlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbDecaySlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbDecaySlider.setPopupDisplayEnabled (true, false, this);
    reverbDecaySlider.setTextValueSuffix ("");

    reverbDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbDecay", reverbDecaySlider);
    
    reverbDampingSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbDampingSlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbDampingSlider.setPopupDisplayEnabled (true, false, this);
    reverbDampingSlider.setTextValueSuffix ("");
    reverbDampingSlider.setColour(1, Colour::fromRGB(200, 200, 200));

    reverbDampingAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbDamping", reverbDampingSlider);
    
    reverbReverbTimeSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    reverbReverbTimeSlider.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    reverbReverbTimeSlider.setPopupDisplayEnabled (true, false, this);
    reverbReverbTimeSlider.setTextValueSuffix ("s");
    
    reverbReverbTimeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getAPVTS(), "reverbReverbTime", reverbReverbTimeSlider);
    
    reverbAPFModulationButton.setClickingTogglesState(true);
    reverbAPFModulationButton.setButtonText("OFF");
    reverbAPFModulationButton.onClick = [this]{
        if(reverbAPFModulationButton.getToggleStateValue() == true){
            reverbAPFModulationButton.setButtonText("ON");
        }
        else{
            reverbAPFModulationButton.setButtonText("OFF");
        }
    };
    
    reverbAPFModulationAttachment = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.getAPVTS(),"reverbAPFModulation",reverbAPFModulationButton);
    
    reverbPreDelayLabel.setText("Pre-Delay (ms)", NotificationType::dontSendNotification);
    reverbPreDelayLabel.setFont(Font(12));
    reverbPreDelayLabel.setJustificationType(Justification::centred);
    reverbPreDelayLabel.attachToComponent(&reverbPreDelaySlider, false);
    
    reverbBandwidthLabel.setText("Bandwidth (Hz)", NotificationType::dontSendNotification);
    reverbBandwidthLabel.setFont(Font(12));
    reverbBandwidthLabel.setJustificationType(Justification::centred);
    reverbBandwidthLabel.attachToComponent(&reverbBandwidthSlider, false);
    
    reverbDecayLabel.setText("Decay", NotificationType::dontSendNotification);
    reverbDecayLabel.setFont(Font(12));
    reverbDecayLabel.setJustificationType(Justification::centred);
    reverbDecayLabel.attachToComponent(&reverbDecaySlider, false);
    
    reverbDampingLabel.setText("Damping", NotificationType::dontSendNotification);
    reverbDampingLabel.setFont(Font(12));
    reverbDampingLabel.setJustificationType(Justification::centred);
    reverbDampingLabel.attachToComponent(&reverbDampingSlider, false);
    
    reverbReverbTimeLabel.setText("Reverb Time (s)", NotificationType::dontSendNotification);
    reverbReverbTimeLabel.setFont(Font(12));
    reverbReverbTimeLabel.setJustificationType(Justification::centred);
    reverbReverbTimeLabel.attachToComponent(&reverbReverbTimeSlider, false);
    
    reverbAPFModulationLabel.setText("APF Modulation", NotificationType::dontSendNotification);
    reverbAPFModulationLabel.setFont(Font(12));
    reverbAPFModulationLabel.setJustificationType(Justification::centred);
    reverbAPFModulationLabel.attachToComponent(&reverbAPFModulationButton, false);
    
    addAndMakeVisible(&reverbPreDelaySlider);
    addAndMakeVisible(&reverbBandwidthSlider);
    addAndMakeVisible(&reverbDecaySlider);
    addAndMakeVisible(&reverbDampingSlider);
    addAndMakeVisible(&reverbReverbTimeSlider);
    addAndMakeVisible(&reverbAPFModulationButton);
    
    reverbTypeComboBox.addItemList(StringArray("Schroeder Reverb", "Moorer Reverb", "Dattorro Plate Reverb"), 1);
    reverbTypeComboBox.setLookAndFeel(&newLandf);
    reverbTypeComboBox.onChange = [this] {
        if(reverbTypeComboBox.getSelectedItemIndex() < 2){
            reverbRightDrySlider.setVisible(false);
            reverbRightWetSlider.setVisible(false);
            reverbPreDelaySlider.setVisible(false);
            reverbBandwidthSlider.setVisible(false);
            reverbDecaySlider.setVisible(false);
            reverbDampingSlider.setVisible(false);
            reverbAPFModulationButton.setVisible(false);
            reverbReverbTimeSlider.setVisible(true);
            
        }
        
        if(reverbTypeComboBox.getSelectedItemIndex() == 2){
            reverbRightDrySlider.setVisible(true);
            reverbRightWetSlider.setVisible(true);
            reverbPreDelaySlider.setVisible(true);
            reverbBandwidthSlider.setVisible(true);
            reverbDecaySlider.setVisible(true);
            reverbDampingSlider.setVisible(true);
            reverbAPFModulationButton.setVisible(true);
            reverbReverbTimeSlider.setVisible(false);
            
        }
        repaint();
    };
    
    reverbTypeAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getAPVTS(),"reverbType",reverbTypeComboBox);
    
    addAndMakeVisible(&reverbTypeComboBox);
}

SpazerAudioProcessorEditor::~SpazerAudioProcessorEditor()
{
    delayLeftNoteLength.setLookAndFeel(nullptr);
    delayRightNoteLength.setLookAndFeel(nullptr);
    reverbTypeComboBox.setLookAndFeel(nullptr);
}

//==============================================================================
void SpazerAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll (Colours::darkgrey );
    
    g.setColour(Colours::black);
    g.fillRect(0, 15, 300, 365+20);
    
    g.setColour(Colour(120, 0, 10));
    g.fillRect(300, 15, 300, 365+20);
    
 
    // set the current drawing colour to black
    g.setColour (Colours::white);
 
    // set the font size and draw text to the screen
    g.setFont (15.0f);
    
    Line<float> lineDelay;
    lineDelay.setStart(150, 50+20);
    lineDelay.setEnd(150, 380 - 20+20);
    g.drawLine(lineDelay);
    
    if(reverbTypeComboBox.getSelectedItemIndex() == 2){
        Line<float> lineReverb;
        lineReverb.setStart(150+300, 50+20+20);
        lineReverb.setEnd(150+300, 170);
        g.drawLine(lineReverb);
        g.setFont(14.0f);
        g.drawText("LEFT", 300, 20+20, 130, 20, Justification::centred);
        g.drawText("RIGHT", 300 + 150 + 20, 20+20, 130, 20, Justification::centred);
        g.setFont(12.0f);
        g.drawText("CHANNEL", 300, 20 + 20 + 22, 300, 20, Justification::centred);
    }
 
    g.setFont(10.0f);
    g.drawFittedText ("SPAZER v1.0.1.2", 0, 2, getWidth(), 10, Justification::centred, 1);
    g.setFont(14.0f);
    g.drawText("LEFT", 0, 20+20, 150, 20, Justification::centred);
    g.drawText("RIGHT", 0 + 150, 20 + 20, 150, 20, Justification::centred);
    g.setFont(12.0f);
    g.drawText("CHANNEL", 0, 20 + 20, 300, 20, Justification::centred);
    g.setFont(18.0f);
    g.drawText("DELAY", 0, 15, 300, 25, Justification::centred);
    g.drawText("REVERB", 300, 15, 300, 25, Justification::centred);
    
}

void SpazerAudioProcessorEditor::resized()
{
    // sets the position and size of the slider with arguments (x, y, width, height)
    delayLeftMs.setBounds (25, 60+20, 65, 55);
    delayLeftFb.setBounds (45, 60 + 65 + 15 + 20, 65,65);
    delayLeftWet.setBounds(45, 60 + 2*65 + 30 + 20, 65, 65);
    delayLeftFilter.setBounds(45, 60 + 3*65 + 45 + 20, 65, 65);
    
    delayRightMs.setBounds (25 + 150, 60 + 20, 65, 55);
    delayRightFb.setBounds (45 + 150, 60 + 65 + 15 + 20, 65,65);
    delayRightWet.setBounds(45 + 150, 60 + 2*65 + 30 + 20, 65, 65);
    delayRightFilter.setBounds(45 + 150, 60 + 3*65 + 45 + 20, 65, 65);
    
    delayLeftNoteLength.setBounds(85, 80 + 20, 55, 20);
    delayRightNoteLength.setBounds(85+150, 80 + 20, 55, 20);
    
    reverbLeftDrySlider.setBounds(332.5, 60 + 20, 65, 65);
    reverbLeftWetSlider.setBounds(332.5, 60 + 80 + 20, 65, 65);
    reverbRightDrySlider.setBounds(332.5 + 170, 60 + 20, 65, 65);
    reverbRightWetSlider.setBounds(332.5 + 170, 60 + 80 + 20, 65, 65);
    
    reverbPreDelaySlider.setBounds(360, 60 + 2*80 + 20, 65, 65);
    reverbBandwidthSlider.setBounds(325 + 150, 60 + 2*80 + 20, 65, 65);
    reverbDecaySlider.setBounds(360 , 60 + 3*80 + 20, 65, 65);
    reverbDampingSlider.setBounds(325 + 150, 60 + 3*80 + 20, 65, 65);
    reverbReverbTimeSlider.setBounds(332.5 + 170, 60 + 20, 65, 65);
    reverbTypeComboBox.setBounds(Rectangle<int>(395, 20 + 20, 110, 20));
    
    reverbAPFModulationButton.setBounds(415, 35 + 2*80, 70, 20);
}
