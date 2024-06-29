#pragma once

#include <JuceHeader.h>

constexpr double DEFAULT_DRY_WET = 0.5;
constexpr double SMOOTHING_TIME = 0.01;

class DryWet {
public:
    explicit DryWet(double defaultDW = DEFAULT_DRY_WET) : dwRatio(defaultDW) {}
    ~DryWet() = default;

    void prepareToPlay(double sr, int maxBlockSize);
    void releaseResources();

    void copyDrySignal(AudioBuffer<float>& sourceBuffer);
    void mixDrySignal(AudioBuffer<float>& destinationBuffer);
    void setDWRatio(float newValue);

private:
    AudioBuffer<float> drySignal;
    float dwRatio;
    SmoothedValue<float, ValueSmoothingTypes::Linear> dryLevel;
    SmoothedValue<float, ValueSmoothingTypes::Linear> wetLevel;
    
    void updateState();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};
