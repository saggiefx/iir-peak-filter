/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Knob.h"


class Needle : public juce::Component
{
public:
    Needle() {}

    ~Needle() override {}

    void setPosition(float newPosition)
    {
        position = newPosition;
        repaint(); // Trigger a repaint to update the needle position
    }


    void paint(juce::Graphics& g) override
    {
        //g.setColour(Colours::red);
        //g.drawRect(getLocalBounds().toFloat());

        float minPos = log10(20.0f);
        float maxPos = log10(20000.0f);

        float pos = log10(position);


        float mappedPosition = jmap(pos, minPos, maxPos, 16.0f, 316.f);

        // Draw the needle shadow first
        g.setColour(juce::Colours::black.withAlpha(0.3f));
        g.drawLine(mappedPosition - 1,
                   getHeight(),
                   mappedPosition - 1,
                   0,
                   6); // Shadow thickness doubled

        // Draw the needle as a vertical line at the mapped position
        g.setColour(juce::Colours::lightgrey);
        g.drawLine(mappedPosition,
                   getHeight(),
                   mappedPosition,
                   0,
                   4); // Needle thickness doubled
    }

private:
    float position = 2000.f;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Needle)
};




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

    Knob gainSlider;
    Knob cutoffSlider;
    Knob bandwidthSlider;

    Needle freqNeedle;

    juce::Component window;

    juce::Image radioBase;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bandwidthSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XFilterAudioProcessorEditor)
};
