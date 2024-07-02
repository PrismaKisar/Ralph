#pragma once

#include <JuceHeader.h>

class BitCrush {
public:
    BitCrush();
    ~BitCrush() {}
    
    void setDryWet(float newValue);
    void prepare(const dsp::ProcessSpec& spec);
    void processBlock (juce::AudioBuffer<float>& buffer, juce::AudioBuffer<double>& modulation);
    
private:
    dsp::DryWetMixer<float> dryWet;
    
    float crush(float value, double bits);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BitCrush)
};
