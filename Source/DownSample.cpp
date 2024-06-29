
#include "DownSample.h"

DownSample::DownSample()
    : currentSampleRate(44100.0) {}

DownSample::~DownSample() {}

void DownSample::prepareToPlay(double sampleRate, int samplesPerBlock) {
    currentSampleRate = sampleRate;
    aliasingBuffer.setSize(2, samplesPerBlock);
    aliasingBuffer.clear();
    ratio = currentSampleRate;
    filter.reset();
}

void DownSample::releaseResources() {
    aliasingBuffer.setSize(0, 0);
}

void DownSample::processBlock(AudioBuffer<float>& buffer, AudioBuffer<double>& modulation) {
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    auto bufferData = buffer.getArrayOfWritePointers();
    auto aliasingData = aliasingBuffer.getArrayOfWritePointers();
    auto modData = modulation.getArrayOfWritePointers();
    auto numModCh = modulation.getNumChannels();
    int t = 0;

    int samplesPerUpdate = static_cast<int>(numSamples * 0.03125);
    int samplesSinceUpdate = 0;

    for (int smp = 0; smp < numSamples; ++smp) {
        for (int ch = 0; ch < numChannels; ++ch) {
            if (samplesSinceUpdate >= samplesPerUpdate) {
                auto targetSampleRate = jmin(modData[jmin(ch, numModCh - 1)][smp], 44100.0);
                ratio = currentSampleRate / targetSampleRate;
                filter.setFrequency(targetSampleRate / 2 - 1);
                samplesSinceUpdate = 0;
            }

            t = (++t >= ratio) ? 0 : t;
            aliasingData[ch][smp] = (t == 0) ? bufferData[ch][smp] : aliasingData[ch][smp - (smp > 0)];
            bufferData[ch][smp] = aliasingData[ch][smp];
        }
        
        samplesSinceUpdate++;
    }
    filter.processBlock(buffer, numSamples);
}

