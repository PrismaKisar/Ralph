#include "ModulationControl.h"

ModulationControl::ModulationControl(double defaultParameter, double defaultModAmount)
    : parameter(defaultParameter), modAmount(defaultModAmount)
{
}

void ModulationControl::prepareToPlay(double sampleRate) {
    parameter.reset(sampleRate, 0.02);
    modAmount.reset(sampleRate, 0.02);
}

void ModulationControl::setModAmount(double newValue) {
    modAmount.setTargetValue(newValue);
}

void ModulationControl::setParameter(double newValue) {
    parameter.setTargetValue(newValue);
}

void ModulationControl::processBlock(AudioBuffer<double>& buffer, int numSamples) {
    auto data = buffer.getArrayOfWritePointers();
    const int numChannels = buffer.getNumChannels();

    // Scale modulation between 0 and 1
    for (int ch = 0; ch < numChannels; ++ch) {
        FloatVectorOperations::add(data[ch], 1.0, numSamples);
        FloatVectorOperations::multiply(data[ch], 0.5, numSamples);
    }

    // Scale modulation according to mod amount
    modAmount.applyGain(buffer, numSamples);

    // Add modulation and parameter
    if (parameter.isSmoothing()) {
        for (int smp = 0; smp < numSamples; ++smp) {
            double currentParameter = parameter.getNextValue();
            for (int ch = 0; ch < numChannels; ++ch)
                data[ch][smp] += currentParameter;
        }
    } else {
        double currentParameter = parameter.getCurrentValue();
        for (int ch = 0; ch < numChannels; ++ch)
            FloatVectorOperations::add(data[ch], currentParameter, numSamples);
    }
}
