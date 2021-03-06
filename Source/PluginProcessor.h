/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Vibrato.h"

//==============================================================================
/**
*/
class VibratopluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VibratopluginAudioProcessor();
    ~VibratopluginAudioProcessor();

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
    
    void processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer& midiMessages, bool state);
    void toggleBypass(bool state);
private:
    AudioProcessorValueTreeState params;
    std::atomic<float>* modWidthParameter = nullptr;
    std::atomic<float>* rateParameter  = nullptr;
    
    CVibrato *pVibrato = nullptr;
    
    const float MaxModWidthInS;
    const float RampLengthInS;
    
    SmoothedValue<float, ValueSmoothingTypes::Linear>           smoothModWidth;
    SmoothedValue<float, ValueSmoothingTypes::Linear>           smoothRate;
    SmoothedValue<float, ValueSmoothingTypes::Linear>           smoothBypass;
    
    bool bypass = false;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratopluginAudioProcessor)
};
