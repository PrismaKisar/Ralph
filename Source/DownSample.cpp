#include "DownSample.h"

DownSample::DownSample()
    : currentSampleRate(44100.0), targetSampleRate(44100.0), downSamplingRatio(1), upSamplingRatio(1)
{
    // Default sample rates and ratios
}

DownSample::~DownSample()
{
}

void DownSample::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;

    // Allocazione dei buffer temporanei per downsampling e upsampling
    downsampledBuffer.setSize(1, samplesPerBlock / downSamplingRatio);
    upsampledBuffer.setSize(1, samplesPerBlock);
    downsampledBuffer.clear();
    upsampledBuffer.clear();
}

void DownSample::releaseResources()
{
    downsampledBuffer.setSize(1, 0);
    upsampledBuffer.setSize(1, 0);
}

void DownSample::processBlock(juce::AudioBuffer<float>& buffer, juce::AudioBuffer<double>& modulation)
{
    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();
    
    // Perform downsampling and upsampling for each channel
    for (int channel = 0; channel < numChannels; ++channel) {
        // Downsampling
        for (int i = 0; i < downsampledBuffer.getNumSamples(); ++i) {
            float index = i * downSamplingRatio;
            int indexFloor = static_cast<int>(index);
            
            // Verifica che indexFloor sia all'interno dei limiti validi
            if (indexFloor < 0 || indexFloor >= buffer.getNumSamples()) {
                // Gestisci l'errore: qui puoi decidere come gestire la situazione di out of bound

                if (indexFloor < 0)
                    indexFloor = 0;
                else if (indexFloor >= numSamples)
                    indexFloor = numSamples - 1;
                
            }
            
            int indexCeil = juce::jmin(indexFloor + 1, numSamples - 1);
            float fraction = index - indexFloor;
            
            float valueFloor = buffer.getSample(channel, indexFloor);
            float valueCeil = buffer.getSample(channel, indexCeil);
            
            downsampledBuffer.setSample(0, i, valueFloor + fraction * (valueCeil - valueFloor));
        }
        
        // Upsampling
        for (int i = 0; i < numSamples; ++i) {
            float index = i * upSamplingRatio;
            int indexFloor = static_cast<int>(index);
            
            // Verifica che indexFloor sia all'interno dei limiti validi
            if (indexFloor < 0 || indexFloor >= downsampledBuffer.getNumSamples()) {
                if (indexFloor < 0)
                    indexFloor = 0;
                else if (indexFloor >= downsampledBuffer.getNumSamples())
                    indexFloor = downsampledBuffer.getNumSamples() - 1;
                
            }
            
            int indexCeil = juce::jmin(indexFloor + 1, downsampledBuffer.getNumSamples() - 1);
            float fraction = index - indexFloor;
            
            float valueFloor = downsampledBuffer.getSample(0, indexFloor);
            float valueCeil = downsampledBuffer.getSample(0, indexCeil);
            
            upsampledBuffer.setSample(0, i, valueFloor + fraction * (valueCeil - valueFloor));
        }
        
        // Copy upsampled buffer back to original buffer channel
        for (int i = 0; i < numSamples; ++i)
            buffer.setSample(channel, i, upsampledBuffer.getSample(0, i));
    }
}


void DownSample::setTargetSampleRate(float newValue)
{
    targetSampleRate = newValue;
    downSamplingRatio = currentSampleRate / targetSampleRate;
    upSamplingRatio = targetSampleRate / currentSampleRate;
}
