#include "circularBuffer.h"
#include <iostream>

// Initalise the buffer to the given size
CircularBuffer::CircularBuffer(int size, int numChannels)
: bufferSize_(size), numChannels_(numChannels), writePosition_(static_cast<index_>(numChannels), 0), 
readPosition_(static_cast<index_>(numChannels), 0)

{
    // Defensive programming
    jassert(numChannels > 0 && "Number of channels must be greater than 0!");

    // Sets the 2d array to the number of channels for and the size of the buffer
    buffer_.setSize(numChannels_, bufferSize_);
    
}

// Write the sample to the buffer at the current write position
void CircularBuffer::writeSample(int channel, float sample)
{
    if(channel < numChannels_)
    {
        buffer_.setSample(channel, writePosition_[static_cast<index_>(channel)], sample);
        
        // This code increments the writing position by one, then wraps it around
        // At the end of the buffer size
        writePosition_[static_cast<index_>(channel)] = (writePosition_[static_cast<index_>(channel)] + 1) % bufferSize_;
    }
}

// Read the sample from the buffer at the current read position
float CircularBuffer::readSample(int channel)
{
    if (channel < numChannels_)
    {
        float sample = buffer_.getSample(channel, readPosition_[static_cast<index_>(channel)]);

        // This code increments the read position by one, then wraps it around
        // At the end of the buffer size
        readPosition_[static_cast<index_>(channel)] = (readPosition_[static_cast<index_>(channel)] + 1) % bufferSize_;
        return sample;
    }
    return 0.0f; 
}

// Set the readPosition based on the desired delay in samples.
void CircularBuffer::setReadPosition(int channel, float delaySamples)
{
    if (channel < numChannels_)
    {
        delaySamples = std::max(0.0f, delaySamples); // Ensure delaySamples is non-negative

        // Calculates the read pointers position based on the write pointer
        readPosition_[static_cast<index_>(channel)] = (writePosition_[static_cast<index_>(channel)] - (int)delaySamples + bufferSize_) % bufferSize_;
    }
}

// Reset the buffer by setting all its values to 0.
void CircularBuffer::reset()
{
    buffer_.clear();
    for (int channel = 0; channel < numChannels_; ++channel)
    {
        writePosition_[static_cast<index_>(channel)] = 0;
        readPosition_[static_cast<index_>(channel)] = 0;
    }
}

// Adjust the size of the buffer.
void CircularBuffer::resize(int newSize)
{
    // Resize the original buffer while retaining the current data
    // Third argument keeps old data
    buffer_.setSize(numChannels_, newSize, true); 
    bufferSize_ = newSize;
    reset();
}

// process the whole file
float CircularBuffer::process(int channel, float inputSample, float feedback)
{
    if (channel < numChannels_)
    {
        // Obtains the sample currently at the read position
        float delayedSample = readSample(channel);

        // Calculates the output by adding the input to a feedback delayed sample
        float outputSample = inputSample + feedback * delayedSample;

        // Writes the calculated output sample back into the buffer
        writeSample(channel, outputSample);

        return outputSample;
    }
    return 0.0f; // Return 0 if channel index is out of bounds
}
