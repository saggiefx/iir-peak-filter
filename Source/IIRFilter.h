
#pragma once
#include <JuceHeader.h>

class IIRFilter
{
public:
    IIRFilter();
    ~IIRFilter();

    void setGain(float dbGain);
    void setCutoff(float fHz);
    void setBandWidth(float bHz);
    void setSampleRate(float sampleRate);
    void prepare(float sampleRate, float gain, float fc, float fb);
    void process(juce::AudioBuffer<float>& buffer);
    void updateCoefficients();
    float processSample(float input);

private:

    //filter coefficients
    float G, Wc,Wb;

    float sampleRate;
    float cutoffFrequency;

    std::vector<float> xh0;
    std::vector<float> xh1;

};




