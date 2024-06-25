#include "Oscillator.h"

/* NaiveOscillator */
Oscillator::Oscillator(double defaultFrequency, int defaultWaveform) :
waveform(defaultWaveform),
currentPhase(0),
phaseIncrement(0),
samplePeriod(0)
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

void Oscillator::getNextAudioBlock(AudioBuffer<double>& buffer, const int numsamples) {
    const int numCh = buffer.getNumChannels();
    auto data = buffer.getArrayOfWritePointers();

    for (int smp = 0; smp < numsamples; ++smp) {
        const double sampleValue = getNextAudioSample();
        for (int ch = 0; ch < numCh; ++ch)
            data[ch][smp] = sampleValue;
    }
}

float Oscillator::getNextAudioSample() {
    auto sampleValue = 0.0;

    switch (waveform) {
    case 0: // Sinusoidale
        sampleValue = sin(MathConstants<double>::twoPi * currentPhase);
        break;
    case 1: // Triangular
        sampleValue = 4.0 * abs(currentPhase - 0.5) - 1.0;
        break;
    case 2: // Saw UP
        sampleValue = 2.0 * currentPhase - 1.0;
        break;
    case 3: // Saw down
        sampleValue = -2.0 * currentPhase + 1.0;
        break;
    case 4: // Square
        sampleValue = (currentPhase > 0.5) - (currentPhase < 0.5);
        break;
    default:
        jassertfalse;
        break;
    }

    phaseIncrement = frequency.getNextValue() * samplePeriod;
    currentPhase += phaseIncrement;
    currentPhase -= static_cast<int>(currentPhase);

    return sampleValue;
}






