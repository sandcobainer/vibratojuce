/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
VibratopluginAudioProcessorEditor::VibratopluginAudioProcessorEditor (VibratopluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 350);
    
    kBypass.setBounds(250,10,200,50);
    addAndMakeVisible(kBypass);
    kBypass.setClickingTogglesState (true);
    kBypass.setButtonText ("BYPASS VIBRATO : OFF");
    kBypass.onClick = [this] { toggleButtonClicked() ; };
        
    
    
    kModulationWidthSlider.setBounds(150, 120, 150, 200);
    kModulationWidthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kModulationWidthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 150, 30);
    kModulationWidthSlider.setRange(0.0f, 0.2f); // Changed range from 0.4f -> 0.2
    kModulationWidthSlider.setTextValueSuffix (" s");
    
    kModWidthLabel.setText("Modulation Width", dontSendNotification);
    kModWidthLabel.attachToComponent(&kModulationWidthSlider, true);

    kModulationWidthSlider.setValue(0.1f);
    kModulationWidthSlider.addListener(this);
    addAndMakeVisible(kModulationWidthSlider);

    
    
    
    kRateSlider.setBounds(400,120, 150, 200);
    kRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kRateSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 150, 30);
    kRateSlider.setRange(0.0f, 14.0f);
    kRateSlider.setTextValueSuffix(" Hz");
    
    kRateLabel.setText("Rate", dontSendNotification);
    kRateLabel.attachToComponent(&kRateSlider, true);

    kRateSlider.setValue(2.0f);
    kRateSlider.addListener(this);
    addAndMakeVisible(kRateSlider);
    
}

VibratopluginAudioProcessorEditor::~VibratopluginAudioProcessorEditor()
{
}

//==============================================================================
void VibratopluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void VibratopluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void VibratopluginAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    
    if (slider == &kModulationWidthSlider)
    {
        processor.setModWidth(kModulationWidthSlider.getValue());
    }
    
    else if (slider == &kRateSlider)
    {
        processor.setRate(kRateSlider.getValue());
    }
    
}


void VibratopluginAudioProcessorEditor::toggleButtonClicked()
{
    auto state = kBypass.getToggleState();
    String stateString = state ? "ON" : "OFF";
    Logger::outputDebugString ( stateString);
    kBypass.setButtonText ("BYPASS VIBRATO : " + stateString);
    
    processor.toggleBypass(state);
    
}
