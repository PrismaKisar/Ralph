#pragma once

#include <JuceHeader.h>

class BitCrush {
public:
    BitCrush(double defaultMaxBits = 24, double defaultBits = 24);
    ~BitCrush() {}
    
    void processBlock (juce::AudioBuffer<float>& buffer);
    void setBits(float newValue);
    
private:
    SmoothedValue<float, ValueSmoothingTypes::Linear> bits;
    double maxBits;
    
    float crush(float value);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BitCrush)
};
