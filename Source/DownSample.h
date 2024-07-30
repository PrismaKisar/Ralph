#pragma once

#include <JuceHeader.h>

class DownSample {
public:
    DownSample();
    ~DownSample() {}
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, const dsp::ProcessSpec& spec);
    void releaseResources();
    void processBlock(AudioBuffer<float>& buffer, AudioBuffer<double>& modulation);
    void setDryWet(float newValue);
    
private:
    AudioBuffer<float> aliasingBuffer;
    dsp::DryWetMixer<float> dryWet;
    std::vector<float> previousValue;

    float lastValue[2] = {0.0f, 0.0f};
    double currentSampleRate;
    int ratio;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DownSample)
};
