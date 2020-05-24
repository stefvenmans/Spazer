/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//Initializes a AudioProcessor object. The AudioProcessorValueTreeState is initialized with parameters that are created with the following function: createParameterLayout. Parameter listeners are added to the AudioProcessorValueTreeState (mAPVTS) to listen for changes on these parameters. If a change ocours, the function: parameterChanged will be called.
SpazerAudioProcessor::SpazerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mAPVTS(*this, nullptr, Identifier("SpazerParameters"),createParameterLayout())
#endif
{
    mAPVTS.state.addListener(this);
    mAPVTS.addParameterListener("delayLeftMs", this);
    mAPVTS.addParameterListener("delayLeftFb", this);
    mAPVTS.addParameterListener("delayLeftWet", this);
    mAPVTS.addParameterListener("delayLeftFilter", this);
    mAPVTS.addParameterListener("delayRightMs", this);
    mAPVTS.addParameterListener("delayRightFb", this);
    mAPVTS.addParameterListener("delayRightWet", this);
    mAPVTS.addParameterListener("delayLeftNoteLength", this);
    mAPVTS.addParameterListener("delayRightNoteLength", this);
    mAPVTS.addParameterListener("delayRightFilter", this);
    mAPVTS.addParameterListener("reverbLeftDry", this);
    mAPVTS.addParameterListener("reverbLeftWet", this);
    mAPVTS.addParameterListener("reverbRightDry", this);
    mAPVTS.addParameterListener("reverbRightWet", this);
    mAPVTS.addParameterListener("reverbPreDelay", this);
    mAPVTS.addParameterListener("reverbBandwidth", this);
    mAPVTS.addParameterListener("reverbDecay", this);
    mAPVTS.addParameterListener("reverbDamping", this);
    mAPVTS.addParameterListener("reverbReverbTime", this);
    mAPVTS.addParameterListener("reverbAPFModulation", this);
    
    bpmOfDAW = 120.0f;
    
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
//This function will be called before the first audio buffer arrives. It informs the PluginProcessor at which samplerate and buffersize the samples will arrive later. The audio effects are intialized here because they need to know what the samplerate is.
void SpazerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    schroederReverb = new SchroederReverb{(int)sampleRate, mAPVTS.getParameter("reverbLeftDry")->getValue(), mAPVTS.getParameter("reverbLeftWet")->getValue()};
    moorerReverb = new MoorerReverb{(int)sampleRate, mAPVTS.getParameter("reverbLeftDry")->getValue(), mAPVTS.getParameter("reverbLeftWet")->getValue()};
    plateReverb = new DattorroPlateReverb{(int)sampleRate, mAPVTS.getParameter("reverbLeftDry")->getValue(), mAPVTS.getParameter("reverbLeftWet")->getValue(), mAPVTS.getParameter("reverbRightDry")->getValue(), mAPVTS.getParameter("reverbRightWet")->getValue()};
    stereoDelay = new StereoDelay{(int)sampleRate, 2.0f, mAPVTS.getParameter("delayLeftMs")->getValue()*2.0f, mAPVTS.getParameter("delayLeftFb")->getValue(), mAPVTS.getParameter("delayLeftFilter")->getValue(), mAPVTS.getParameter("delayLeftWet")->getValue()};
    updateNoteLengths();
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

//This is the most important function of the plug-in. This function will be called at a frequency of sampleRate/bufferSize. It takes a reference to a AudioBuffer which contains the new inputsamples. These input samples will be processed in this function with right audio effect and will then be writen back into the output buffer which is also part of: buffer. If the BPM of the DAW changes, the vector with note lengths will be updated acording to the new BPM.
void SpazerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    AudioBuffer<float> processIn;
    processIn.makeCopyOf(buffer);
    stereoDelay->processBuffer(buffer);
    if(mAPVTS.getParameter("reverbType")->getValue() == 0){
        schroederReverb->processBlock(buffer);
    }
    else if(mAPVTS.getParameter("reverbType")->getValue() == 0.5){
        moorerReverb->processBlock(buffer);
    }
    else if(mAPVTS.getParameter("reverbType")->getValue() == 1){
        plateReverb->processBlock(buffer);
    }
    
    AudioPlayHead::CurrentPositionInfo result;
    getPlayHead()->getCurrentPosition(result);
    if(result.bpm != bpmOfDAW){
        bpmOfDAW = result.bpm;
        updateNoteLengths();
        if(mAPVTS.getParameter("delayLeftNoteLength")->getValue() != 0){
            mAPVTS.getParameter("delayLeftMs")->setValueNotifyingHost((noteLengths[mAPVTS.getParameter("delayLeftNoteLength")->getValue()*9])/2.0f);
        }
        if(mAPVTS.getParameter("delayRightNoteLength")->getValue() != 0){
            mAPVTS.getParameter("delayRightMs")->setValueNotifyingHost((noteLengths[mAPVTS.getParameter("delayRightNoteLength")->getValue()*9])/2.0f);
        }
    }
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

}

void SpazerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

//Callback from value tree
void SpazerAudioProcessor::valueTreePropertyChanged(ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
    
}

//Parameter callback from valuetree
void SpazerAudioProcessor::parameterChanged(const String &parameterID, float newValue){
    if(!parameterID.compare("delayLeftMs")){
        stereoDelay->setDelay(0, newValue/1000.0f);
    }
    else if(!parameterID.compare("delayRightMs")){
        stereoDelay->setDelay(1, newValue/1000.0f);
    }
    else if(!parameterID.compare("delayLeftFb")){
        stereoDelay->setFeedback(0, newValue/100.0f);
    }
    else if(!parameterID.compare("delayRightFb")){
        stereoDelay->setFeedback(1, newValue/100.0f);
    }
    else if(!parameterID.compare("delayLeftWet")){
        stereoDelay->setWetGain(0, newValue/100.0f);
    }
    else if(!parameterID.compare("delayRightWet")){
        stereoDelay->setWetGain(1, newValue/100.0f);
    }
    else if(!parameterID.compare("delayLeftFilter")){
        stereoDelay->setBandwidth(0, newValue);
    }
    else if(!parameterID.compare("delayRightFilter")){
        stereoDelay->setBandwidth(1, newValue);
    }
    else if(!parameterID.compare("delayLeftNoteLength")){
        mAPVTS.getParameter("delayLeftMs")->setValueNotifyingHost((noteLengths[(int)newValue]/2.0f));
    }
    else if(!parameterID.compare("delayRightNoteLength")){
        mAPVTS.getParameter("delayRightMs")->setValueNotifyingHost((noteLengths[newValue])/2.0f);
    }
    else if(!parameterID.compare("reverbLeftDry")){
        schroederReverb->setDryGain(newValue);
        moorerReverb->setDryGain(newValue);
        plateReverb->setDryGainLeft(newValue);
    }
    else if(!parameterID.compare("reverbLeftWet")){
        schroederReverb->setWetGain(newValue);
        moorerReverb->setWetGain(newValue);
        plateReverb->setWetGainLeft(newValue);
    }
    else if(!parameterID.compare("reverbRightDry")){
        plateReverb->setDryGainRight(newValue);
    }
    else if(!parameterID.compare("reverbRightWet")){
        plateReverb->setWetGainRight(newValue);
    }
    else if(!parameterID.compare("reverbPreDelay")){
        plateReverb->setPreDelay(newValue);
    }
    else if(!parameterID.compare("reverbBandwidth")){
        plateReverb->setBandwidth(newValue);
    }
    else if(!parameterID.compare("reverbDecay")){
        plateReverb->setDecay(newValue);
    }
    else if(!parameterID.compare("reverbDamping")){
        plateReverb->setDamping(newValue);
     }
    else if(!parameterID.compare("reverbReverbTime")){
        schroederReverb->setReverbTime(newValue);
        moorerReverb->setReverbTime(newValue);
    }
    else if(!parameterID.compare("reverbAPFModulation")){
        plateReverb->setAllPassModulationState((bool)newValue);
    }
}

AudioProcessorValueTreeState::ParameterLayout SpazerAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;
    
    params.push_back (std::make_unique<AudioParameterFloat> ("delayLeftMs","Delay Left", 0.0f, 2000.0f, 1000.0f));
    params.push_back (std::make_unique<AudioParameterFloat> ("delayLeftFb", "Feedback Left", 0.0f, 100.0f, 25.0f));
    params.push_back (std::make_unique<AudioParameterFloat> ("delayLeftWet", "Dry/Wet Left", 0.0f, 100.0f, 25.0f));
    params.push_back (std::make_unique<AudioParameterFloat> ("delayLeftFilter", "Filter Left", 0.0f, 20000.0f, 20000.0f));
    params.push_back (std::make_unique<AudioParameterFloat> ("delayRightMs", "Delay Right", 0.0f, 2000.0f, 500.0f));
    params.push_back (std::make_unique<AudioParameterFloat> ("delayRightFb", "Feedback Right", 0.0f, 100.0f, 15.0f));
    params.push_back (std::make_unique<AudioParameterFloat> ("delayRightWet", "Dry/Wet Right", 0.0f, 100.0f, 15.0f));
    params.push_back (std::make_unique<AudioParameterFloat> ("delayRightFilter", "Filter Right", 0.0f, 20000.0f, 20000.0f));
    params.push_back (std::make_unique<AudioParameterChoice>("delayLeftNoteLength","Note Length Left",StringArray("1/2d","1/2","1/4d","1/4","1/8d","1/8","1/16d","1/16","1/32d","1/32"),1));
    params.push_back (std::make_unique<AudioParameterChoice>("delayRightNoteLength","Note Length Right",StringArray("1/2d","1/2","1/4d","1/4","1/8d","1/8","1/16d","1/16","1/32d","1/32"),1));
    params.push_back(std::make_unique<AudioParameterChoice>("reverbType", "Reverb Type", StringArray("Schroeder Reverb","Moorer Reverb", "Dattorro Plate Reverb"), 2));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbLeftDry", "Reverb Left Dry", 0.0f, 100.0f, 90.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbLeftWet", "Reverb Left Wet", 0.0f, 100.0f, 10.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbRightDry", "Reverb Right Dry", 0.0f, 100.0f, 90.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbRightWet", "Reverb Right Wet", 0.0f, 100.0f, 10.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbPreDelay", "Reverb Pre-Delay", 0.0f, 100.0f, 20.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbBandwidth", "Reverb Bandwidth", 0.0f, 20000.0f, 19990.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbDecay", "Reverb Decay", 0.0f, 100.0f, 50.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbDamping", "Reverb Damping", 0.0f, 100.0f, 0.05f));
    params.push_back(std::make_unique<AudioParameterFloat>("reverbReverbTime", "Reverb Time", 0.0f, 10.0f, 1.0f));
    params.push_back(std::make_unique<AudioParameterBool>("reverbAPFModulation", "Reverb APF Modulation", false));
    
    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpazerAudioProcessor();
}

void SpazerAudioProcessor::updateNoteLengths()
{
    auto fullNote = (60.0/((double)bpmOfDAW))*4.0;
    noteLengths.clear();
    noteLengths.push_back((fullNote/2.0)+(fullNote/4.0));
    noteLengths.push_back((fullNote/2.0));
    noteLengths.push_back((fullNote/4.0)+(fullNote/8.0));
    noteLengths.push_back((fullNote/4.0));
    noteLengths.push_back((fullNote/8.0)+(fullNote/16.0));
    noteLengths.push_back((fullNote/8.0));
    noteLengths.push_back((fullNote/16.0)+(fullNote/32.0));
    noteLengths.push_back((fullNote/16.0));
    noteLengths.push_back((fullNote/32.0) +(fullNote/64.0));
    noteLengths.push_back((fullNote/32.0));
}
