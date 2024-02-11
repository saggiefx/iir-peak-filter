#include "IIRFilter.h"

CutFilter::CutFilter()
{
}

CutFilter::~CutFilter()
{
}

void CutFilter::setGain(float dbGain)
{
    G = dbGain;
}


void CutFilter::setCutoff(float fHz)
{
    Wc = 2 * fHz / sampleRate;
}

void CutFilter::setBandWidth(float bHz)
{
    Wb = 2 * bHz / sampleRate;
}

void CutFilter::setSampleRate(float newSampleRate)
{
    sampleRate = newSampleRate;
}

void CutFilter::processBlock(juce::AudioBuffer<float>& buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    xh0.resize(buffer.getNumChannels(), 0.f);
    xh1.resize(buffer.getNumChannels(), 0.f);

    for (auto channel = 0; channel < numChannels; ++channel) {
        float* samplePointer = buffer.getWritePointer(channel);
        for (auto i = 0; i < numSamples; ++i) {
            const float inputSample = samplePointer[i];
            samplePointer[i] = processSample(inputSample,channel);
        }
    }
}

void CutFilter::updateCoefficients()
{
    float V0 = powf(10, G / 20);
    H0 = V0 - 1.0f;
    const float pi = juce::MathConstants<float>::pi;
    c = (std::tan(pi * Wb / 2.0f) - (G >= 0 ? 1 : V0)) / (std::tan(pi * Wb / 2.0f) + (G >= 0 ? 1 : V0));
    d = -std::cos(juce::MathConstants<float>::pi * Wc);
}

float CutFilter::processSample(float input, int channel)
{
    const auto xh_new = input - d * (1 - c) * xh0[channel] + c * xh1[channel];
    const auto ap_y = -c * xh_new + d * (1 - c) * xh0[channel] + xh1[channel];

    //update state variables, use seperate state variables for seperate channels
    xh1[channel] = xh0[channel];
    xh0[channel] = xh_new;

    const float filterOutput = 0.5f * H0 * (input - ap_y) + input;
    //assertion will fail incase the output exceeds our desired range
    //jassert(filterOutput >= -1.0f && filterOutput <= 1.0f);
    return filterOutput;
}
