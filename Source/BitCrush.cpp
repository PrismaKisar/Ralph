#include "BitCrush.h"

BitCrush::BitCrush(double defaultMaxBits, double defaultBits) {
    bits.setTargetValue(defaultBits);
    maxBits = defaultMaxBits;
}

void BitCrush::processBlock(juce::AudioBuffer<float>& buffer) {
    const auto numSamples = buffer.getNumSamples();
    const auto numCh = buffer.getNumChannels();
    auto bufferData = buffer.getArrayOfWritePointers();

    for (int smp = 0; smp < numSamples; ++smp)
        for (int ch = 0; ch < numCh; ++ch)
            bufferData[ch][smp] = crush(static_cast<float>(bufferData[ch][smp]));
}

void BitCrush::setBits(float newValue) { 
    bits.setTargetValue(newValue);
}

float BitCrush::crush(float value) { 
    double QL = 2.0 / (pow(2, bits.getTargetValue()) - 1);
    return QL * static_cast<int>(value / QL);
}





