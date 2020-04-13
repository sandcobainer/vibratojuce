/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
VibratopluginAudioProcessorEditor::VibratopluginAudioProcessorEditor (VibratopluginAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p),
      valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 350);
    
    kBypass.setBounds(250,10,200,50);
    addAndMakeVisible(kBypass);
    kBypass.setClickingTogglesState (true);
    kBypass.setButtonText ("BYPASS VIBRATO : OFF");
    kBypass.onClick = [this] { toggleButtonClicked(); };

        
    kModulationWidthSlider.setBounds(150, 120, 150, 200);
    kModulationWidthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kModulationWidthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 300, 30);
    kModulationWidthSlider.setTextValueSuffix (" s");
    
    kModWidthLabel.setText("Modulation Width", dontSendNotification);
    kModWidthLabel.attachToComponent(&kModulationWidthSlider, true);

    kModulationWidthSlider.setValue(0.1f);
    kModWidthAttachment.reset (new SliderAttachment (valueTreeState, "modWidth", kModulationWidthSlider));
    addAndMakeVisible(kModulationWidthSlider);

    
    kRateSlider.setBounds(400, 120, 150, 200);
    kRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kRateSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 300, 30);
    kRateSlider.setTextValueSuffix(" Hz");
    
    kRateLabel.setText("Rate", dontSendNotification);
    kRateLabel.attachToComponent(&kRateSlider, true);
    kRateSlider.setValue(2.0f);
    kRateAttachment.reset (new SliderAttachment (valueTreeState, "rate", kRateSlider));
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

void VibratopluginAudioProcessorEditor::toggleButtonClicked()
{
    auto state = kBypass.getToggleState();
    String stateString = state ? "ON" : "OFF";
    kBypass.setButtonText ("BYPASS VIBRATO : " + stateString);
    processor.toggleBypass(state);
}
