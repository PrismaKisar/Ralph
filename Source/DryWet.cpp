#include "DryWet.h"

void DryWet::prepareToPlay(double sr, int maxBlockSize) {
    drySignal.setSize(2, maxBlockSize);
    drySignal.clear();

    dryLevel.reset(sr, SMOOTHING_TIME);
    wetLevel.reset(sr, SMOOTHING_TIME);

    updateState();
}

void DryWet::releaseResources() {
    drySignal.setSize(0, 0);
}

void DryWet::copyDrySignal(AudioBuffer<float>& sourceBuffer) {
    const int numChannels = sourceBuffer.getNumChannels();
    const int numSamples = sourceBuffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch) {
        drySignal.copyFrom(ch, 0, sourceBuffer, ch, 0, numSamples);
    }
}

void DryWet::mixDrySignal(AudioBuffer<float>& destinationBuffer) {
    const int numChannels = destinationBuffer.getNumChannels();
    const int numSamples = destinationBuffer.getNumSamples();
    
    dryLevel.applyGain(drySignal, numSamples);
    wetLevel.applyGain(destinationBuffer, numSamples);

    for (int ch = 0; ch < numChannels; ++ch) {
        destinationBuffer.addFrom(ch, 0, drySignal, ch, 0, numSamples);
    }
}

void DryWet::setDWRatio(float newValue) {
    dwRatio = newValue;
    updateState();
}

void DryWet::updateState() {
    dryLevel.setTargetValue(sqrt(1.0f - dwRatio));
    wetLevel.setTargetValue(sqrt(dwRatio));
}
