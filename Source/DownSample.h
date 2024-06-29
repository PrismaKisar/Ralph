#pragma once

#include <JuceHeader.h>

class DownSample {
public:
    DownSample();
    ~DownSample();
    
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<double>& modulation);
    void setTargetSampleRate(float newValue);
    
private:
    juce::AudioBuffer<float> aliasingBuffer;
    
    double currentSampleRate;
    double targetSampleRate;
    double ratio;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DownSample)
};
