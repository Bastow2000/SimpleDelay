#pragma once
#include <JuceHeader.h>
#include "circularBuffer.h"

class Delay
{
public:
    // Constructor
    Delay(int maxDelaySamples, int numChannels);

    void reset(int sampleRate, int delayTimeInMilliSeconds);

    void setDelayTime(int milliseconds,int sampleRate);

    void setFeedback(float value);

    void setMixRate(float mixRate);

    void process(AudioBuffer<float>& buffer);

   
    
private:
    CircularBuffer circularBuffer_;
    float feedback_;
    float mix_;
    float sampleRate_;
    int delaySamples_;
};
