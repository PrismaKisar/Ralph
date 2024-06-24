#pragma once
#include <JuceHeader.h>

class NaiveOscillator {
public:
    NaiveOscillator(double defaultFrequency = 1.0, int defaultWaveform = 0);
	~NaiveOscillator() {}

    void prepareToPlay(double sampleRate);
    void setFrequency(double newValue);
    void setWaveform(int newValue);
    void getNextAudioBlock(AudioBuffer<double>& buffer, const int numsamples);
    float getNextAudioSample();
		
private:
	int waveform;
	SmoothedValue<double, ValueSmoothingTypes::Multiplicative> frequency;

	double currentPhase;
	double phaseIncrement;
	double samplePeriod;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NaiveOscillator)
};


class ParameterModulation {
public:
    ParameterModulation(const double defaultParameter = 0.0, const double defaultModAmount = 0.0);
	~ParameterModulation() {}

    void prepareToPlay(double sampleRate);
    void setModAmount(const double newValue);
    void setParameter(const double newValue);
    void processBlock(AudioBuffer<double>& buffer, const int numSamples);

private:
	SmoothedValue<double, ValueSmoothingTypes::Linear> parameter;
	SmoothedValue<double, ValueSmoothingTypes::Linear> modAmount;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterModulation)
};
