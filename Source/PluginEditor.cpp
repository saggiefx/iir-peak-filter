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

    radioBase = juce::ImageCache::getFromMemory(BinaryData::radio_front_png, BinaryData::radio_front_pngSize);

    setSize (900, 450);
}

XFilterAudioProcessorEditor::~XFilterAudioProcessorEditor()
{
}

//==============================================================================
void XFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::teal);

    // (Our component is opaque, so we must comp
    g.drawImage(radioBase, 0, 0, getWidth(), getHeight(), 0, 0, radioBase.getWidth(), radioBase.getHeight());

}

void XFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    int knobSize = 120;
    int y_init = 235;

    gainSlider.setBounds(390, y_init, knobSize, knobSize);
    bandwidthSlider.setBounds(520, y_init, knobSize, knobSize);
    cutoffSlider.setBounds(640, 195, 200, 200);

}
