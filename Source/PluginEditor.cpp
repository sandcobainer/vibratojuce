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
    setSize (400, 300);
        
    kModulationWidthSlider.setBounds(0, 0, 150, 150);
    kModulationWidthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kModulationWidthSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 25);
    kModulationWidthSlider.setRange(0.0f, 2.0f);

    kModulationWidthSlider.setValue(0.5f);
    kModulationWidthSlider.addListener(this);
    addAndMakeVisible(kModulationWidthSlider);
    
    kRateSlider.setBounds(200,0, 150, 150);
    kRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    kRateSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 60, 25);
    kRateSlider.setRange(0.0f, 14.0f);

    kRateSlider.setValue(7.0f);
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
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
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
        float modwidth = (static_cast<float> (kModulationWidthSlider.getValue()) );
        processor.setModWidth(modwidth);
        DBG(modwidth);
        DBG(kModulationWidthSlider.getValue());
    }
    
    else if (slider == &kRateSlider)
    {
        float rate = (static_cast<float> (kRateSlider.getValue()) );
       processor.setRate(static_cast<float> (kRateSlider.getValue()) );
        DBG(rate);
       DBG(kRateSlider.getValue());
    }
    
}
