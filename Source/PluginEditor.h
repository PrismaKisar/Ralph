/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class RalphAudioProcessorEditor  : public juce::AudioProcessorEditor {
public:
    RalphAudioProcessorEditor (RalphAudioProcessor&);
    ~RalphAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RalphAudioProcessor& audioProcessor;
    Image backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RalphAudioProcessorEditor)
};
