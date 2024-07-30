#include "Oscillator.h"

Oscillator::Oscillator(double defaultFrequency, int defaultWaveform) :
    waveform(defaultWaveform),
    currentPhase(0),
    samplePeriod(0),
    phaseIncrement(0),
    prevValue(0.0f),
    newCycle(true)
{
    frequency.setTargetValue(defaultFrequency);
}

void Oscillator::prepareToPlay(double sampleRate) {
    frequency.reset(sampleRate, 0.02);
    samplePeriod = 1.0 / sampleRate;
}

void Oscillator::setFrequency(double newValue) {
    jassert(newValue > 0);
    frequency.setTargetValue(newValue);
}

void Oscillator::setWaveform(int newValue) {
    waveform = newValue;
}

void Oscillator::getNextAudioBlock(AudioBuffer<double>& buffer, int numSamples) {
    const int numChannels = buffer.getNumChannels();
    auto data = buffer.getArrayOfWritePointers();

    for (int smp = 0; smp < numSamples; ++smp) {
        const double sampleValue = getNextAudioSample();
        for (int ch = 0; ch < numChannels; ++ch)
            data[ch][smp] = sampleValue;
    }
}

float Oscillator::getNextAudioSample() {
    double sampleValue = 0.0;

    switch (waveform) {
        case SINUSOID:
            sampleValue = sin(MathConstants<double>::twoPi * currentPhase);
            break;
        case TRIANGULAR:
            sampleValue = 4.0 * fabs(currentPhase - 0.5) - 1.0;
            break;
        case SAW_UP:
            sampleValue = 2.0 * currentPhase - 1.0;
            break;
        case SAW_DOWN:
            sampleValue = -2.0 * currentPhase + 1.0;
            break;
        case SQUARE:
            sampleValue = (currentPhase > 0.5) ? 1.0 : -1.0;
            break;
        case SAMPLE_AND_HOLD:
            if (newCycle) {
                sampleValue = 2.0 * (randomGenerator.nextDouble()) - 1.0;
                prevValue = sampleValue;
                newCycle = false;
            } else {
                sampleValue = prevValue;
            }
            break;
        default:
            jassertfalse;
            break;
    }

    phaseIncrement = frequency.getNextValue() * samplePeriod;
    currentPhase += phaseIncrement;
    newCycle = currentPhase >= 1.0;
    currentPhase -= static_cast<int>(currentPhase);
    
    return static_cast<float>(sampleValue);
}
