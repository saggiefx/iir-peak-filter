
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
    void prepare(double sampleRate, float gain, float fc, float fb);
    void process(juce::AudioBuffer<float>& buffer);
    void updateCoefficients();
    float processSample(float input);

private:

    //filter coefficients
    float c, H0, G, Wc,Wb, d;

    // state variables
    float xh[2] = { 0.0f, 0.0f }, yA;

    double sampleRate;

};




