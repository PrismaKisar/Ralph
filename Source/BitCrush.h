#pragma once

#include <JuceHeader.h>

class BitCrush {
public:
    BitCrush() {}
    ~BitCrush() {}
    
    void processBlock (juce::AudioBuffer<float>& buffer, juce::AudioBuffer<double>& modulation);
    
private:
    float crush(float value, double bits);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BitCrush)
};
