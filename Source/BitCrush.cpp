#include "BitCrush.h"

BitCrush::BitCrush() : dryWet() {
    dryWet.setMixingRule(dsp::DryWetMixingRule::sin3dB);
}

void BitCrush::prepare(const dsp::ProcessSpec& spec) {
    dryWet.prepare(spec);
}

void BitCrush::processBlock(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<double>& modulation) {
    dsp::AudioBlock<float> audioBlock(buffer);
    dryWet.pushDrySamples(audioBlock);
    
    const auto numSamples = buffer.getNumSamples();
    const auto numCh = buffer.getNumChannels();

    auto bufferData = buffer.getArrayOfWritePointers();
    auto modData = modulation.getArrayOfWritePointers();
    const auto numModCh = modulation.getNumChannels();

    for (int smp = 0; smp < numSamples; ++smp)
        for (int ch = 0; ch < numCh; ++ch)
            bufferData[ch][smp] = crush(bufferData[ch][smp], jmin(modData[jmin(ch, numModCh - 1)][smp], 24.0));
    
    dryWet.mixWetSamples(audioBlock);
}

float BitCrush::crush(float value, double bits) {
    const double QL = (pow(2, bits) - 1) * 0.5;
    return static_cast<int>(value * QL) / QL;
}

void BitCrush::setDryWet(float newValue) {
    dryWet.setWetMixProportion(newValue);
}
