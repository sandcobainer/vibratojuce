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
class VibratopluginAudioProcessorEditor  :  public AudioProcessorEditor,
                                            public Slider::Listener
{
public:
    VibratopluginAudioProcessorEditor (VibratopluginAudioProcessor&);
    ~VibratopluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider* slider) override;
    void toggleButtonClicked();

private:
    
    Slider kModulationWidthSlider;
    Slider kRateSlider;
    ToggleButton kBypass;
    Label kModWidthLabel;
    Label kRateLabel;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VibratopluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratopluginAudioProcessorEditor)
};
