#pragma once

#include <JuceHeader.h>

class ModulationControl {
public:
    ModulationControl(double defaultParameter = 0.0, double defaultModAmount = 0.0);
    ~ModulationControl() = default;

    void prepareToPlay(double sampleRate);
    void setModAmount(double newValue);
    void setParameter(double newValue);
    void processBlock(AudioBuffer<double>& buffer, int numSamples);

private:
    SmoothedValue<double, ValueSmoothingTypes::Linear> parameter;
    SmoothedValue<double, ValueSmoothingTypes::Linear> modAmount;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModulationControl)
};
