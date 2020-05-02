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
    setSize (300, 380);
    
    userSetNoteLength = false;
    
    //120 bpm = 2 seconds per full note
    // TODO: sync with DAW tempo
    auto fullNote = 2.0;
    noteLengths.add((fullNote/2.0)+(fullNote/4.0));
    noteLengths.add((fullNote/2.0));
    noteLengths.add((fullNote/4.0)+(fullNote/8.0));
    noteLengths.add((fullNote/4.0));
    noteLengths.add((fullNote/8.0)+(fullNote/16.0));
    noteLengths.add((fullNote/8.0));
    noteLengths.add((fullNote/16.0)+(fullNote/32.0));
    noteLengths.add((fullNote/16.0));
    noteLengths.add((fullNote/32.0)+(fullNote/64.0));
    noteLengths.add((fullNote/32.0));
    
    delayLeftMs.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftMs.setRange(0.0, 2000, 0.1);
    delayLeftMs.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    delayLeftMs.setPopupDisplayEnabled (true, false, this);
    delayLeftMs.setTextValueSuffix ("ms");
    delayLeftMs.setValue(1.0);
    delayLeftMs.addListener(this);
    
    delayLeftFb.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftFb.setRange(0.0, 100, 0.1);
    delayLeftFb.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayLeftFb.setPopupDisplayEnabled (true, false, this);
    delayLeftFb.setTextValueSuffix ("%");
    delayLeftFb.setValue(1.0);
    delayLeftFb.addListener(this);
    
    delayLeftWet.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftWet.setRange(0.0, 100, 0.1);
    delayLeftWet.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayLeftWet.setPopupDisplayEnabled (true, false, this);
    delayLeftWet.setTextValueSuffix ("%");
    delayLeftWet.setValue(1.0);
    delayLeftWet.addListener(this);
    
    delayLeftFilter.setSliderStyle (Slider::RotaryVerticalDrag);
    delayLeftFilter.setRange(10.0, 20000.0, 0.1);
    delayLeftFilter.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayLeftFilter.setPopupDisplayEnabled (true, false, this);
    delayLeftFilter.setTextValueSuffix ("Hz");
    delayLeftFilter.setValue(1.0);
    delayLeftFilter.addListener(this);
    
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
    
    delayRightMs.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightMs.setRange(0.0, 2000, 0.1);
    delayRightMs.setTextBoxStyle (Slider::NoTextBox, false, 90,0);
    delayRightMs.setPopupDisplayEnabled (true, false, this);
    delayRightMs.setTextValueSuffix ("ms");
    delayRightMs.setValue(1.0);
    delayRightMs.addListener(this);

    delayRightFb.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightFb.setRange(0.0, 100, 0.1);
    delayRightFb.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayRightFb.setPopupDisplayEnabled (true, false, this);
    delayRightFb.setTextValueSuffix ("%");
    delayRightFb.setValue(1.0);
    delayRightFb.addListener(this);

    delayRightWet.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightWet.setRange(0.0, 100, 0.1);
    delayRightWet.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayRightWet.setPopupDisplayEnabled (true, false, this);
    delayRightWet.setTextValueSuffix ("%");
    delayRightWet.setValue(1.0);
    delayRightWet.addListener(this);

    delayRightFilter.setSliderStyle (Slider::RotaryVerticalDrag);
    delayRightFilter.setRange(10.0, 20000.0, 0.1);
    delayRightFilter.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    delayRightFilter.setPopupDisplayEnabled (true, false, this);
    delayRightFilter.setTextValueSuffix ("Hz");
    delayRightFilter.setValue(1.0);
    delayRightFilter.addListener(this);

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
    
    delayLeftNoteLength.addItem("1/2d", 1);
    delayLeftNoteLength.addItem("1/2", 2);
    delayLeftNoteLength.addItem("1/4d", 3);
    delayLeftNoteLength.addItem("1/4", 4);
    delayLeftNoteLength.addItem("1/8d", 5);
    delayLeftNoteLength.addItem("1/8", 6);
    delayLeftNoteLength.addItem("1/16d", 7);
    delayLeftNoteLength.addItem("1/16", 8);
    delayLeftNoteLength.addItem("1/32d", 9);
    delayLeftNoteLength.addItem("1/32", 10);
    delayLeftNoteLength.setLookAndFeel(&newLandf);
    addAndMakeVisible(&delayLeftNoteLength);
    delayLeftNoteLength.onChange = [this] {
        std::cout << "note length: " << noteLengths[delayLeftNoteLength.getSelectedId()] << std::endl;
        delayLeftMs.setValue((noteLengths[delayLeftNoteLength.getSelectedId() - 1])*1000.0);
    };
    
    delayRightNoteLength.addItem("1/2d", 1);
    delayRightNoteLength.addItem("1/2", 2);
    delayRightNoteLength.addItem("1/4d", 3);
    delayRightNoteLength.addItem("1/4", 4);
    delayRightNoteLength.addItem("1/8d", 5);
    delayRightNoteLength.addItem("1/8", 6);
    delayRightNoteLength.addItem("1/16d", 7);
    delayRightNoteLength.addItem("1/16", 8);
    delayRightNoteLength.addItem("1/32d", 9);
    delayRightNoteLength.addItem("1/32", 10);
    delayRightNoteLength.setLookAndFeel(&newLandf);
    addAndMakeVisible(&delayRightNoteLength);
    delayRightNoteLength.onChange = [this] {
        delayRightMs.setValue((noteLengths[delayRightNoteLength.getSelectedId() - 1])*1000.0);
    };
    
    addAndMakeVisible(bpmTestLabel);
    bpmTestLabel.setText("-1", NotificationType::dontSendNotification);
    processor.tempoOfDaw.addListener(this);
    
}

SpazerAudioProcessorEditor::~SpazerAudioProcessorEditor()
{
    delayLeftNoteLength.setLookAndFeel(nullptr);
    delayRightNoteLength.setLookAndFeel(nullptr);
    processor.tempoOfDaw.removeListener(this);
}

//==============================================================================
void SpazerAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll (Colours::darkgrey );
 
    // set the current drawing colour to black
    g.setColour (Colours::white);
 
    // set the font size and draw text to the screen
    g.setFont (15.0f);
    
    Line<float> line;
    line.setStart(150, 50);
    line.setEnd(150, 380 - 20);
    g.drawLine(line);
 
    //g.drawFittedText ("Left", Rectangle<float>().setBounds(0, 0, 0, 0),Justification(),1);
    g.setFont(10.0f);
    g.drawFittedText ("SPAZER v1.0.1.2", 0, 2, getWidth(), 10, Justification::centred, 1);
    g.setFont(16.0f);
    g.drawText("LEFT", 0, 15, 150, 20, Justification::centred);
    g.drawText("RIGHT", 0 + 150, 15, 150, 20, Justification::centred);
    
}

void SpazerAudioProcessorEditor::resized()
{
    // sets the position and size of the slider with arguments (x, y, width, height)
    delayLeftMs.setBounds (25, 60, 65, 55);
    delayLeftFb.setBounds (45, 60 + 65 + 15, 65,65);
    delayLeftWet.setBounds(45, 60 + 2*65 + 30, 65, 65);
    delayLeftFilter.setBounds(45, 60 + 3*65 + 45, 65, 65);
    
    delayRightMs.setBounds (25 + 150, 60, 65, 55);
    delayRightFb.setBounds (45 + 150, 60 + 65 + 15, 65,65);
    delayRightWet.setBounds(45 + 150, 60 + 2*65 + 30, 65, 65);
    delayRightFilter.setBounds(45 + 150, 60 + 3*65 + 45, 65, 65);
    
    delayLeftNoteLength.setBounds(85, 80, 55, 20);
    delayRightNoteLength.setBounds(85+150, 80, 55, 20);
    
    bpmTestLabel.setBounds(0, 0, 30, 20);
    
}

void SpazerAudioProcessorEditor::sliderValueChanged (Slider* slider){
    processor.delayLeft.setParameters(delayLeftFb.getValue(), delayLeftWet.getValue(), delayLeftMs.getValue(), 2, processor.getSampleRate());
    processor.delayRight.setParameters(delayRightFb.getValue(), delayRightWet.getValue(), delayRightMs.getValue(), 2, processor.getSampleRate());
    
    if(slider == &delayLeftFilter){
        processor.delayLeft.setFeedbackFilter(IIRCoefficients::makeLowPass(processor.getSampleRate(), delayLeftFilter.getValue()));
    }
    if(slider == &delayRightFilter){
        processor.delayRight.setFeedbackFilter(IIRCoefficients::makeLowPass(processor.getSampleRate(), delayRightFilter.getValue()));
    }
    
    
}

void SpazerAudioProcessorEditor::valueChanged(Value &value){
    
    auto fullNote = (60.0/((double)processor.tempoOfDaw.getValue()))*4.0;
    noteLengths.clear();
    noteLengths.add((fullNote/2.0)+(fullNote/4.0));
    noteLengths.add((fullNote/2.0));
    noteLengths.add((fullNote/4.0)+(fullNote/8.0));
    noteLengths.add((fullNote/4.0));
    noteLengths.add((fullNote/8.0)+(fullNote/16.0));
    noteLengths.add((fullNote/8.0));
    noteLengths.add((fullNote/16.0)+(fullNote/32.0));
    noteLengths.add((fullNote/16.0));
    noteLengths.add((fullNote/32.0) +(fullNote/64.0));
    noteLengths.add((fullNote/32.0));
    if(delayLeftNoteLength.getSelectedId() != 0){
        delayLeftMs.setValue((noteLengths[delayLeftNoteLength.getSelectedId() - 1])*1000.0);
        bpmTestLabel.setText(String((double)processor.tempoOfDaw.getValue()), NotificationType::dontSendNotification);
    }
    if(delayRightNoteLength.getSelectedId() != 0){
        delayRightMs.setValue((noteLengths[delayRightNoteLength.getSelectedId() - 1])*1000.0);
        
    }
}

