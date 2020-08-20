/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTutorial1AudioProcessorEditor::GainTutorial1AudioProcessorEditor (GainTutorial1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);
    
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(0.0, 1.0);
    gainSlider.setValue(0.6);
    gainSlider.addListener(this);
    

    addAndMakeVisible(gainSlider);
}

GainTutorial1AudioProcessorEditor::~GainTutorial1AudioProcessorEditor()
{
}

//==============================================================================
void GainTutorial1AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void GainTutorial1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gainSlider.setBounds(getLocalBounds());
}


void GainTutorial1AudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &gainSlider)
    {
        float sliderValue = (float) gainSlider.getValue();
        
        processor.reverbWetLevel = sliderValue;
        processor.mReverbParameters.wetLevel = sliderValue;
    }
}
