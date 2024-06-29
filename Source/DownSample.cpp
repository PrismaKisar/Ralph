
#include "DownSample.h"

DownSample::DownSample()
    : currentSampleRate(44100.0), targetSampleRate(44100.0) {}

DownSample::~DownSample() {}

void DownSample::prepareToPlay(double sampleRate, int samplesPerBlock) {
    currentSampleRate = sampleRate;
    aliasingBuffer.setSize(2, samplesPerBlock);
    aliasingBuffer.clear();
    ratio = currentSampleRate / targetSampleRate;
}

void DownSample::releaseResources() {
    aliasingBuffer.setSize(0, 0);
}

void DownSample::processBlock(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<double>& modulation) {
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    auto bufferData = buffer.getArrayOfWritePointers();
    auto aliasingData = aliasingBuffer.getArrayOfWritePointers();
    auto modData = modulation.getArrayOfWritePointers();
    auto numModCh = modulation.getNumChannels();
    int t = 0;
    
    for (int smp = 0; smp < numSamples; ++smp) {
        for (int ch = 0; ch < numChannels; ++ch) {
            ratio = currentSampleRate / jmin(modData[jmin(ch, numModCh - 1)][smp], 44100.0);
            t = (++t >= ratio) ? 0 : t;
            aliasingData[ch][smp] = (t == 0) ? bufferData[ch][smp] : aliasingData[ch][smp - (smp > 0)];
            bufferData[ch][smp] = aliasingData[ch][smp];
        }
    }
}

void DownSample::setTargetSampleRate(float newValue) {
    targetSampleRate = newValue;
    ratio = currentSampleRate / targetSampleRate;
}
