
#pragma once
#include <JuceHeader.h>

class CutFilter
{
public:
    CutFilter();
    ~CutFilter();

    void setGain(float dbGain);
    void setCutoff(float fHz);
    void setBandWidth(float bHz);
    void setSampleRate(float sampleRate);
    void updateCoefficients();
    void processBlock(juce::AudioBuffer<float>& buffer);
    float processSample(float input, int channel);

private:

    //filter coefficients & parameters
    float G, Wc,Wb,H0,c,d;

    float sampleRate;
    float cutoffFrequency;

    std::vector<float> xh0;
    std::vector<float> xh1;

};




