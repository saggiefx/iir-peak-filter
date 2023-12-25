#include "IIRFilter.h"

IIRFilter::IIRFilter()
{
}

IIRFilter::~IIRFilter()
{
}

void IIRFilter::prepare(double sampleRate, float gain, float fc, float fb)
{
    setSampleRate(sampleRate);
    setCutoff(fc);
    setGain(gain);
    setBandWidth(fb);
    updateCoefficients();
}

void IIRFilter::setGain(float dbGain)
{
    G = dbGain;
}


void IIRFilter::setCutoff(float fHz)
{
    Wc = 2 * fHz / sampleRate;
}

void IIRFilter::setBandWidth(float bHz)
{
    Wb = 2 * bHz / sampleRate;
}

void IIRFilter::setSampleRate(float newSampleRate)
{
    sampleRate = newSampleRate;
}

void IIRFilter::process(juce::AudioBuffer<float>& buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            channelData[i] = processSample(channelData[i]);
        }
    }
}

void IIRFilter::updateCoefficients()
{
    float V0 = std::pow(10, (G / 20.0f));
    H0 = V0 - 1.0f;
    const float pi = juce::MathConstants<float>::pi;

    if (G >= 0)
    {
        c = (std::tan(pi * Wb / 2.0f) - 1.0f) / (std::tan(pi * Wb / 2.0f) + 1.0f);
    }
    else
    {
        c = (std::tan(pi * Wb / 2.0f) - V0) / (std::tan(pi * Wb / 2.0f) + V0);
    }

    d = -std::cos(juce::MathConstants<float>::pi * Wc);
}

float IIRFilter::processSample(float input)
{
    float xh_new = input - d * (1 - c) * xh[0] + c * xh[1];
    float ap_y = -c * xh_new + d * (1 - c) * xh[0] + xh[1];

    xh[1] = xh[0];
    xh[0] = xh_new;

    float y = 0.5f * H0 * (input - ap_y) + input;
    return y;
}
