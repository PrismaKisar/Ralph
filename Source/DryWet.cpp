#include "DryWet.h"

void DryWet::prepareToPlay(double sr, int maxBlockSize) {
    drySignal.setSize(2, maxBlockSize);
    drySignal.clear();

    dryLevel.reset(sr, 0.01);
    wetLevel.reset(sr, 0.01);

    updateState();
}

void DryWet::releaseResources() {
    drySignal.setSize(0, 0);
}

void DryWet::copyDrySignal(AudioBuffer<float>& sourceBuffer) {
    auto numCh = sourceBuffer.getNumChannels();
    auto numSamples = sourceBuffer.getNumSamples();

    for (int ch = 0; ch < numCh; ++ch)
        drySignal.copyFrom(ch, 0, sourceBuffer, ch, 0, numSamples);
}

void DryWet::mixDrySignal(AudioBuffer<float>& destinationBuffer) {
    auto numCh = destinationBuffer.getNumChannels();
    auto numSamples = destinationBuffer.getNumSamples();
    
    dryLevel.applyGain(drySignal, numSamples);
    wetLevel.applyGain(destinationBuffer, numSamples);

    for (int ch = 0; ch < numCh; ++ch)
        destinationBuffer.addFrom(ch, 0, drySignal, ch, 0, numSamples);
}

void DryWet::setDWRatio(float newValue) {
    dwRatio = newValue;
    updateState();
}

void DryWet::updateState() {
    dryLevel.setTargetValue(sqrt(1.0 - dwRatio));
    wetLevel.setTargetValue(sqrt(dwRatio));
}

