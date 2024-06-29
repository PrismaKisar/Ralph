#pragma once

#include <JuceHeader.h>

#define MAX_NUM_CH 2

class StereoFilter {
public:
    StereoFilter(double defaultFrequency = 1000.0);
    ~StereoFilter() {}

    void prepareToPlay(double sampleRate);
    void processBlock(AudioBuffer<float>& buffer, const int numSamples);
    void setFrequency(const double newValue);
    void reset();
    
private:
    double frequency;
    double sampleRate = 48000.0;

    OwnedArray<dsp::FirstOrderTPTFilter<float>> tptFilters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StereoFilter)
};
