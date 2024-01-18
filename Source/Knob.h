/*
  ==============================================================================

    Knob.h
    Created: 19 Jan 1919 19:19:19am
    Author:  saggiefx

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AnalogLook : public juce::LookAndFeel_V4
{
private:
    juce::Image radioKnob;

public:
    AnalogLook()
    {
        radioKnob = juce::ImageCache::getFromMemory(BinaryData::E1_png, BinaryData::E1_pngSize);
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
        juce::Slider& slider) override
    {

        int frameCount = 127; 
        int frameIndex = static_cast<int>(sliderPos * frameCount);

        g.drawImage(radioKnob,
            x, y, width, height,
            0, frameIndex * 128, 128, 128);
    }
};

class Knob : public juce::Slider
{
public:
    Knob()
    {
        setSliderStyle(juce::Slider::RotaryVerticalDrag);
        setLookAndFeel(&analogLook);
        setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    }

    ~Knob() override {
        setLookAndFeel(nullptr);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Knob)
private:
    AnalogLook analogLook; 
};
