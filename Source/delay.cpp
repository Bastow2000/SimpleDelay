#include "delay.h"


Delay::Delay(int maxDelaySamples, int numChannels)
: circularBuffer_(maxDelaySamples, numChannels), feedback_(0.5f),mix_(1.0f), delaySamples_(0)
{
    
}


void Delay::reset(int sampleRate, int delayTimeInMilliSeconds)
{
    delaySamples_ = (sampleRate * delayTimeInMilliSeconds) / 1000;
    circularBuffer_.resize(delaySamples_);
    circularBuffer_.reset();
}

void Delay::setDelayTime(int milliseconds,int sampleRate)
{
    delaySamples_ = (sampleRate * milliseconds) / 1000;

    // Ensure delaySamples doesn't exceed buffer size.
    delaySamples_ = juce::jmin(delaySamples_, circularBuffer_.getBufferSize() - 1); 
    circularBuffer_.setReadPosition(0, delaySamples_);
    circularBuffer_.setReadPosition(1, delaySamples_);

}

void Delay::setFeedback(float value)
{
    // Defensive programming, if the value is out side of this range it will flag up
    jassert(value >= 0.0f && value <= 1.0f && "feedback value is out of range!");

    feedback_ = juce::jlimit(0.0f, 1.0f, value);
}

void Delay::setMixRate(float mixRate)
{
    // Defensive programming, if the value is out side of this range it will flag up
    jassert(mixRate >= 0.0f && mixRate <= 1.0f && "mixRate value is out of range!");

    mix_ = juce::jlimit(0.0f, 1.0f, mixRate);
    //mix_ = mixRate;
}

void Delay::process(AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            float inputSample = buffer.getSample(channel, sample);
            
            float delayedSample = circularBuffer_.process(channel, inputSample, feedback_);
            
            // Mix the processed signal with the original
            buffer.setSample(channel, sample, mix_ * delayedSample + (1.0f - mix_) * inputSample);
        }
    }
}
