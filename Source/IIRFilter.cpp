#include "IIRFilter.h"

IIRFilter::IIRFilter()
{
}

IIRFilter::~IIRFilter()
{
}

void IIRFilter::prepare(float sampleRate, float gain, float fc, float fb)
{
    setSampleRate(sampleRate);
    setCutoff(fc);
    setGain(gain);
    setBandWidth(fb);
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
    this->sampleRate = newSampleRate;
}

void IIRFilter::process(juce::AudioBuffer<float>& buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    constexpr auto PI = 3.14159265359f;
    xh0.resize(buffer.getNumChannels(), 0.f);
    xh1.resize(buffer.getNumChannels(), 0.f);

    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto channelSamples = buffer.getWritePointer(channel);
        for (auto i = 0; i < buffer.getNumSamples(); ++i) {

            const float inputSample = channelSamples[i];
            const auto V0 = pow(10, (G/20));
            const auto H0 = V0 - 1;
            const auto d = -cos(PI * Wc);

            const auto xt = G >= 0 ? 1 : V0;
            const auto c = (tan(PI * Wb/2) - xt) / (tan(PI * Wb/2) + xt);

            const auto xh_new = inputSample - d * (1 - c) * xh0[channel] + c * xh1[channel];

            const auto ap_y = -c * xh_new + d * (1 - c) * xh0[channel] + xh1[channel];

            xh1[channel] = xh0[channel];
            xh0[channel] = xh_new;

            const float filterOutput = 0.5f * H0 * (inputSample - ap_y) + inputSample;

            channelSamples[i] = filterOutput;
        }
    }
}

void IIRFilter::updateCoefficients()
{
    //float V0 = pow(10, G / 20);
    //H0 = V0 - 1.0f;
    //const float pi = juce::MathConstants<float>::pi;

    //if (G >= 0)
    //{
    //    c = (std::tan(pi * Wb / 2.0f) - 1.0f) / (std::tan(pi * Wb / 2.0f) + 1.0f);
    //}
    //else
    //{
    //    c = (std::tan(pi * Wb / 2.0f) - V0) / (std::tan(pi * Wb / 2.0f) + V0);
    //}

    //d = -std::cos(juce::MathConstants<float>::pi * Wc);
}

float IIRFilter::processSample(float input)
{
    //float xh_new = input - (d * (1 - c) * xh[0]) + c*xh[1];
    ////jassert(xh_new > -3.9 && xh_new<3.9);
    ////jassert(xh[1] > -10 && xh[1] < 10);
    //float ap_y = -c * xh_new + d * (1 - c) * xh[0] + xh[1];

    //xh[1] = xh[0];
    //xh[0] = xh_new;

    //float y = 0.5f * H0 * (input - ap_y) + input;
    //jassert(y >= -1.0f && y <= 1.0f);

    //return y;
    return 0;
}
