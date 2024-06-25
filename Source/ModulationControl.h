#pragma once

#include <JuceHeader.h>

class ModulationControl {
public:
    ModulationControl(const double defaultParameter = 0.0, const double defaultModAmount = 0.0);
    ~ModulationControl() {}

    void prepareToPlay(double sampleRate);
    void setModAmount(const double newValue);
    void setParameter(const double newValue);
    void processBlock(AudioBuffer<double>& buffer, const int numSamples);

private:
    SmoothedValue<double, ValueSmoothingTypes::Linear> parameter;
    SmoothedValue<double, ValueSmoothingTypes::Linear> modAmount;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModulationControl)
};
