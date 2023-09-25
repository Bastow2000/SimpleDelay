/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "paramId.h"

//==============================================================================
/**
*/
class SimpleDelayAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor&);
    ~SimpleDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDelayAudioProcessor& audioProcessor;

    juce::Slider mixSlider, feedbackSlider, delayTimeSlider;
 
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> mixVal;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> feedVal;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> delayVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayAudioProcessorEditor)
};
