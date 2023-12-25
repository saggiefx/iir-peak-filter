/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XFilterAudioProcessorEditor::XFilterAudioProcessorEditor (XFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //addAndMakeVisible(window);
    //window.setColour(juce::Component::, juce::Colours::black);

    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parametersTree, "gain", gainSlider));

    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    cutoffSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parametersTree, "cutoff", cutoffSlider));

    addAndMakeVisible(bandwidthSlider);
    bandwidthSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    bandwidthSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.parametersTree, "bandwidth", bandwidthSlider));

    setSize (400, 370);
}

XFilterAudioProcessorEditor::~XFilterAudioProcessorEditor()
{
}

//==============================================================================
void XFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::teal);

}

void XFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    gainSlider.setBounds(10, 0, 150, 150);
    cutoffSlider.setBounds(10, 100, 150, 150);
    bandwidthSlider.setBounds(10, 200, 150, 150);

}
