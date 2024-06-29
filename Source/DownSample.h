#pragma once

#include <JuceHeader.h>
#include "Filters.h"

class DownSample {
public:
    DownSample();
    ~DownSample();
    
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock(AudioBuffer<float>& buffer, AudioBuffer<double>& modulation);
    void setTargetSampleRate(float newValue);
    
private:
    AudioBuffer<float> aliasingBuffer;
    StereoFilter filter;
    
    double currentSampleRate;
    double ratio;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DownSample)
};
