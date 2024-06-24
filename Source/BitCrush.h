#pragma once

#include <JuceHeader.h>

class BitCrush {
public:
    BitCrush(double defaultMaxBits = 24, double defaultBits = 24);
    ~BitCrush() {}
    
    void prepareToPlay(double sampleRate);
    void processBlock (juce::AudioBuffer<float>& buffer, juce::AudioBuffer<double>& modulation);
    //void setBits(float newValue);
    
private:
    //SmoothedValue<float, ValueSmoothingTypes::Multiplicative> bits;
    double maxBits;
    
    float crush(float value, double bits);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BitCrush)
};
