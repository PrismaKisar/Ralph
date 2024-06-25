#pragma once
#include <JuceHeader.h>

class Oscillator {
public:
    Oscillator(double defaultFrequency = 1.0, int defaultWaveform = 0);
	~Oscillator() {}

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

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator)
};

