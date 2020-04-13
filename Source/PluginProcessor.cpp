/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Vibrato.h"

//==============================================================================
VibratopluginAudioProcessor::VibratopluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  ),
#endif
MaxModWidthInS(0.002), RampLengthInS(3e-4), bypass(false),
params(*this, nullptr, Identifier("VibratoParameters"),
       {
            std::make_unique<AudioParameterFloat> ( "modWidth",
                                                    "Modulation Width",
                                                    NormalisableRange <float> (0.0f, 0.002f,0.0001f),
                                                     0.001f),
            std::make_unique<AudioParameterFloat> ( "rate",
                                                    "LFO Rate",
                                                    0.0f,
                                                    14.0f,
                                                    8.0f)
        })

{
    CVibrato::createInstance(pVibrato);
    modWidthParameter = params.getRawParameterValue ("modWidth");
    rateParameter  = params
    .getRawParameterValue ("rate");
}

VibratopluginAudioProcessor::~VibratopluginAudioProcessor()
{
    pVibrato -> resetInstance();
    CVibrato::destroyInstance(pVibrato);
    
}

//==============================================================================
const String VibratopluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibratopluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VibratopluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VibratopluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VibratopluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibratopluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VibratopluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibratopluginAudioProcessor::setCurrentProgram (int index)
{
}

const String VibratopluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibratopluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VibratopluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    smoothModWidth.reset(sampleRate, RampLengthInS);
    smoothRate.reset(sampleRate, RampLengthInS);
    smoothBypass.reset(sampleRate, RampLengthInS);
    
    smoothModWidth.setCurrentAndTargetValue(*modWidthParameter);
    smoothRate.setCurrentAndTargetValue(*rateParameter);
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    pVibrato -> initInstance(MaxModWidthInS, (float)sampleRate, getTotalNumInputChannels());
    
}

void VibratopluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VibratopluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VibratopluginAudioProcessor:: processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    smoothModWidth.setTargetValue(*modWidthParameter);
    pVibrato -> setParam(CVibrato::kParamModWidthInS, static_cast<float> ( static_cast<int> (1 - bypass) * smoothModWidth.getNextValue()));
    
    smoothRate.setTargetValue(*rateParameter);
    pVibrato -> setParam(CVibrato::kParamModFreqInHz, static_cast<float> (smoothRate.getNextValue()));
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    pVibrato -> process(const_cast<float**>(buffer.getArrayOfReadPointers()), buffer.getArrayOfWritePointers() , this -> getBlockSize());
}

//==============================================================================
bool VibratopluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VibratopluginAudioProcessor::createEditor()
{
    return new VibratopluginAudioProcessorEditor (*this, params);
}

//==============================================================================
void VibratopluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = params.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VibratopluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
 
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (params.state.getType()))
            params.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibratopluginAudioProcessor();
}

void VibratopluginAudioProcessor::toggleBypass(bool state)
{
    bypass = state;
}
