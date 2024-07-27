
#include "DownSample.h"

DownSample::DownSample()
    : currentSampleRate(44100.0) 
{
    dryWet.setMixingRule(dsp::DryWetMixingRule::sin3dB);
}

void DownSample::prepareToPlay(double sampleRate, int samplesPerBlock, const dsp::ProcessSpec& spec) {
    currentSampleRate = sampleRate;
    aliasingBuffer.setSize(2, samplesPerBlock);
    aliasingBuffer.clear();
    ratio = currentSampleRate;
    dryWet.prepare(spec);
    for (int i = 0; i < spec.numChannels; i++) previousValue.push_back(0);
}

void DownSample::releaseResources() {
    aliasingBuffer.setSize(0, 0);
    
}

void DownSample::processBlock(AudioBuffer<float>& buffer, AudioBuffer<double>& modulation) {
    dsp::AudioBlock<float> audioBlock(buffer);
    dryWet.pushDrySamples(audioBlock);
    
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    auto bufferData = buffer.getArrayOfWritePointers();
    auto modData = modulation.getArrayOfWritePointers();
    auto numModCh = modulation.getNumChannels();
    
    int sampleCounter = 0;
    int ratio;
    double targetSampleRate;
    
    for (int smp = 0; smp < numSamples; ++smp) {
        for (int ch = 0; ch < numChannels; ++ch) {
            targetSampleRate = jmin(modData[jmin(ch, numModCh - 1)][smp], currentSampleRate);
            ratio = static_cast<int>(currentSampleRate / targetSampleRate);
            
            if ((sampleCounter % ratio) == 0)
                lastValue = bufferData[ch][smp];
            else
                bufferData[ch][smp] = lastValue;
        }
        
        sampleCounter++;
    }
    
    dryWet.mixWetSamples(audioBlock);
}

void DownSample::setDryWet(float newValue) {
    dryWet.setWetMixProportion(newValue);
}
