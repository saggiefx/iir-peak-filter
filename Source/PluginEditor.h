/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class XFilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    XFilterAudioProcessorEditor (XFilterAudioProcessor&);
    ~XFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    XFilterAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    juce::Slider cutoffSlider;
    juce::Slider bandwidthSlider;

    juce::Component window;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bandwidthSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XFilterAudioProcessorEditor)
};
