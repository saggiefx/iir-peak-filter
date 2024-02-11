/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "IIRFilter.h"

static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    auto dBFormat = [](float value, int /*maximumStringLength*/)
    {
        return juce::String(value, 2) + " dB";
    };

    auto hzFormat = [](float value, int /*maximumStringLength*/)
    {
        return juce::String(value, 0) + " Hz";
    };

    juce::NormalisableRange<float> gainRange(-60.0f, 10.0f, 0.1f, 1.0f);
    juce::NormalisableRange<float> cutoffRange(20.0f, 20000.0f, 1.0f, 1.0f);
    juce::NormalisableRange<float> bandwidthRange(0.1f, 100.0f, 0.01f, 1.0f); 

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "gain",
        "Gain",
        gainRange,
        -50.0f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        dBFormat,
        nullptr
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "cutoff",
        "Cutoff Frequency",
        cutoffRange,
        2000.0,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        hzFormat,
        nullptr
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "bandwidth",
        "Bandwidth",
        bandwidthRange,
        10.0f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        hzFormat,
        nullptr
    ));

    return layout;
}


//==============================================================================
/**
*/
class XFilterAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    XFilterAudioProcessor();
    ~XFilterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState parametersTree;

private:

    CutFilter peakFilter;

    std::atomic<float>* gainParam = nullptr;
    std::atomic<float>* cutoffParam = nullptr;
    std::atomic<float>* bandwidthParam = nullptr;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XFilterAudioProcessor)
};
