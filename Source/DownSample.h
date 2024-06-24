#pragma once

#include <JuceHeader.h>

class DownSample {
public:
    DownSample(double defaultMaxSR = 24, double defaultSR = 24);
    ~DownSample() {}
    
    void processBlock (juce::AudioBuffer<float>& buffer);
    void setSR(float newValue);
    
private:
    SmoothedValue<float, ValueSmoothingTypes::Linear> SR;
    double maxSR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DownSample)
};
