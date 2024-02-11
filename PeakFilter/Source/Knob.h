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
    }

    void drawRotarySlider(Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          Slider& slider) override
    {
        int frameIndex = static_cast<int>(sliderPosProportional * 70) % 71;

        int frameWidth = 400;
        int frameHeight = 400;

        const char* data = nullptr;
        int size = 0;

        juce::String imageName = juce::String::formatted("volume_%05d_png", frameIndex);


        data = BinaryData::getNamedResource((const char*) imageName.toUTF8(), size);
        radioKnob = ImageCache::getFromMemory(data, size);
        g.drawImage(radioKnob,
                    0,
                    0,
                    slider.getWidth(),
                    slider.getHeight(),
                    0,
                    0,
                    frameWidth,
                    frameHeight);
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
