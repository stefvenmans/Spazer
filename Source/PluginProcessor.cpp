/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpazerAudioProcessor::SpazerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
}

SpazerAudioProcessor::~SpazerAudioProcessor()
{
}

//==============================================================================
const String SpazerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpazerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SpazerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SpazerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SpazerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpazerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SpazerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpazerAudioProcessor::setCurrentProgram (int index)
{
}

const String SpazerAudioProcessor::getProgramName (int index)
{
    return {};
}

void SpazerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SpazerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    delayLeft.setParameters(70, 50, 600, 2, sampleRate);
    delayLeft.setFeedbackFilter(IIRCoefficients::makeLowPass(sampleRate, 100));
    delayRight.setParameters(50, 50, 200, 2, sampleRate);
    delayRight.setFeedbackFilter(IIRCoefficients::makeLowPass(sampleRate, 1500));
    //filter.setCoefficients(IIRCoefficients::makeLowPass(44100,6000,1));
    
    LFO1.setFrequency(0.2, sampleRate);
    
    AudioPlayHead::CurrentPositionInfo result;
    getPlayHead()->getCurrentPosition(result);
    std::cout << result.bpm << std::endl;
  
}

void SpazerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpazerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SpazerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    //auto delayBuffer = delayLeft.processAudioBlock(buffer, oscBuff[0]);
    //buffer.clear();
    //auto writePointer = buffer.getWritePointer(0);
//    for(int i=0; i<buffer.getNumSamples();i++){
//        writePointer[i] = delayBuffer[i];
//    }
    //buffer.clear();
    
    
    delayLeft.processAudioBlock(buffer, 0);
    delayRight.processAudioBlock(buffer, 1);
    
    
    MidiBuffer processedMidi;
    int time;
    MidiMessage m;
 
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        std::cout << m.getTempoSecondsPerQuarterNote() << std::endl;
        
        std::cout << m.getTempoSecondsPerQuarterNote() << "tempo" << std::endl;
    }
    
    AudioPlayHead::CurrentPositionInfo result;
    getPlayHead()->getCurrentPosition(result);
    if(result.bpm != (double)tempoOfDaw.getValue()){
        tempoOfDaw.setValue(result.bpm);
    }
    
    //filter.processSamples(writePointer, buffer.getNumSamples());
//    auto oscBuff = LFO1.getProcessedBlock(buffer.getNumSamples(), TRIANGLE);
//    for(int i=0; i<buffer.getNumSamples();i++){
//        writePointer[i] = oscBuff[0][i];
//    }
}

//==============================================================================
bool SpazerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SpazerAudioProcessor::createEditor()
{
    return new SpazerAudioProcessorEditor (*this);
}

//==============================================================================
void SpazerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SpazerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpazerAudioProcessor();
}
