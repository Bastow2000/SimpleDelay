/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDelayAudioProcessorEditor::SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    mixSlider.addListener(this);
    feedbackSlider.addListener(this);
    delayTimeSlider.addListener(this);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(feedbackSlider);
    addAndMakeVisible(delayTimeSlider);

    mixVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, mixId, mixSlider);
    feedVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, feedbackId, feedbackSlider);
    delayVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, delayTimeId, feedbackSlider);

    setSize (400, 300);
}

SimpleDelayAudioProcessorEditor::~SimpleDelayAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mixSlider.setBounds(10, 10, getWidth() , 260);
    feedbackSlider.setBounds(10, 10, getWidth() , 150);
    delayTimeSlider.setBounds(10, 10, getWidth() , 40);
}

void SimpleDelayAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{

}