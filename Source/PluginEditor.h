/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VibratopluginAudioProcessorEditor  :  public AudioProcessorEditor
{
public:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
    VibratopluginAudioProcessorEditor (VibratopluginAudioProcessor&, AudioProcessorValueTreeState&);
    ~VibratopluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void toggleButtonClicked();

private:
    
    Slider kModulationWidthSlider;
    Slider kRateSlider;
    ToggleButton kBypass;
    Label kModWidthLabel;
    Label kRateLabel;
    
    AudioProcessorValueTreeState& valueTreeState;
    std::unique_ptr <SliderAttachment> kModWidthAttachment;
    std::unique_ptr <SliderAttachment> kRateAttachment;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VibratopluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratopluginAudioProcessorEditor)
};
