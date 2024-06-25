#include "ModulationControl.h"

ModulationControl::ModulationControl(double defaultParameter, double defaultModAmount) {
    parameter.setCurrentAndTargetValue(defaultParameter);
    modAmount.setCurrentAndTargetValue(defaultModAmount);
}

void ModulationControl::prepareToPlay(double sampleRate) {
    parameter.reset(sampleRate, 0.02);
    modAmount.reset(sampleRate, 0.02);
}

void ModulationControl::setModAmount(const double newValue) {
    modAmount.setTargetValue(newValue);
}

void ModulationControl::setParameter(const double newValue) {
    parameter.setTargetValue(newValue);
}

void ModulationControl::processBlock(AudioBuffer<double>& buffer, const int numSamples) {
    auto data = buffer.getArrayOfWritePointers();
    const auto numCh = buffer.getNumChannels();

    // Scalo la modulazione tra 0 e 1
    for (int ch = 0; ch < numCh; ++ch) {
        FloatVectorOperations::add(data[ch], 1.0, numSamples);
        FloatVectorOperations::multiply(data[ch], 0.5, numSamples);
    }

    // Scalo la modulazione in accordo con mod amount
    modAmount.applyGain(buffer, numSamples);

    // Sommo modulazione e parametro
    if (parameter.isSmoothing()) {
        for (int smp = 0; smp < numSamples; ++smp)
            for (int ch = 0; ch < numCh; ++ch)
                data[ch][smp] += ch ? parameter.getCurrentValue() : parameter.getNextValue();
    } else {
        for (int ch = 0; ch < numCh; ++ch)
            FloatVectorOperations::add(data[ch], parameter.getCurrentValue(), numSamples);
    }
}
