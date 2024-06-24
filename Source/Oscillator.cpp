#include "Oscillator.h"

/* NaiveOscillator */
NaiveOscillator::NaiveOscillator(double defaultFrequency, int defaultWaveform) {
    waveform = defaultWaveform;
    frequency.setTargetValue(defaultFrequency);
}

void NaiveOscillator::prepareToPlay(double sampleRate) {
    frequency.reset(sampleRate, 0.02);
    samplePeriod = 1.0 / sampleRate;
}

void NaiveOscillator::setFrequency(double newValue) {
    jassert(newValue > 0);
    frequency.setTargetValue(newValue);
}


void NaiveOscillator::setWaveform(int newValue) {
    waveform = newValue;
}

void NaiveOscillator::getNextAudioBlock(AudioBuffer<double>& buffer, const int numsamples) {
    const int numCh = buffer.getNumChannels();
    auto data = buffer.getArrayOfWritePointers();

    for (int smp = 0; smp < numsamples; ++smp) {
        const double sampleValue = getNextAudioSample();
        for (int ch = 0; ch < numCh; ++ch)
            data[ch][smp] = sampleValue;
    }
}

float NaiveOscillator::getNextAudioSample() {
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


/* ParameterModulation */
ParameterModulation::ParameterModulation(double defaultParameter, double defaultModAmount) {
    parameter.setCurrentAndTargetValue(defaultParameter);
    modAmount.setCurrentAndTargetValue(defaultModAmount);
}

void ParameterModulation::prepareToPlay(double sampleRate) {
    parameter.reset(sampleRate, 0.02);
    modAmount.reset(sampleRate, 0.02);
}

void ParameterModulation::setModAmount(const double newValue) {
    modAmount.setTargetValue(newValue);
}

void ParameterModulation::setParameter(const double newValue) {
    parameter.setTargetValue(newValue);
}

void ParameterModulation::processBlock(AudioBuffer<double>& buffer, const int numSamples) {
    auto data = buffer.getArrayOfWritePointers();
    const auto numCh = buffer.getNumChannels();

    // Scalo la modulazione tra 0 e 1
    for (int ch = 0; ch < numCh; ++ch) {
        FloatVectorOperations::add(data[ch], 1.0, numSamples);
        FloatVectorOperations::multiply(data[ch], 0.5, numSamples);
    }

    // Scalo la modulazione in accordo con mod amount
    modAmount.applyGain(buffer, numSamples);

    // Sommo modulazione e parametro
    if (parameter.isSmoothing()) {
        for (int smp = 0; smp < numSamples; ++smp)
            for (int ch = 0; ch < numCh; ++ch)
                data[ch][smp] += ch ? parameter.getCurrentValue() : parameter.getNextValue();
    } else {
        for (int ch = 0; ch < numCh; ++ch)
            FloatVectorOperations::add(data[ch], parameter.getCurrentValue(), numSamples);
    }
}



