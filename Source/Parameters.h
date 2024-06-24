#pragma once
#include <JuceHeader.h>


namespace Parameters
{
	// CONSTANTS
	static const double maxDelayTime = 5.1;

	// PARAM IDs
	static const String nameDryWet = "DW";
    static const String nameFreqDS = "MFDS";
    static const String nameFreqBC = "MFBC";
    static const String nameWaveformDS = "MWDS";
    static const String nameWaveformBC = "MWBC";
    static const String nameDownSample = "DS";
    static const String nameBitCrush = "BC";

	// PARAM DEFAULTS
	static const float defaultDryWet = 0.5f;
    static const float defaultFreq = 1.0f;
    static const float defaultAmount = 0.0f;
    static const float defaultSampleRate = 44100.0f;
    static const float defaultBitDepth = 24.0f;
    static const int defaultWaveform = 0;

	static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
	{
		std::vector<std::unique_ptr<RangedAudioParameter>> parameters;
		parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameDryWet, 1), "Dry/Wet (%)", 0, 1, defaultDryWet));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameDownSample, 1), "Sample Rate", NormalisableRange<float>(400.0f, 44100.0f, 1, 0.4f), defaultFreq));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameBitCrush, 1), "Bits", NormalisableRange<float>(1.0f, 24.0f, 0.001, 0.4f), defaultFreq));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameFreqDS, 1), "LFO Frequency DownSampling (Hz)", NormalisableRange<float>(0.01f, 60.0f, 0.01, 0.2f), defaultFreq));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameFreqBC, 1), "LFO Frequency BitCrush (Hz)", NormalisableRange<float>(0.01f, 60.0f, 0.01, 0.2f), defaultFreq));
        parameters.push_back(std::make_unique<AudioParameterChoice>(ParameterID(nameWaveformDS, 1), "LFO Waveform DownSampling", StringArray{"Sinusoid","Triangular","Saw Up","Saw Down","Square"}, defaultWaveform));
        parameters.push_back(std::make_unique<AudioParameterChoice>(ParameterID(nameWaveformBC, 1), "LFO Waveform BitCrush", StringArray{"Sinusoid","Triangular","Saw Up","Saw Down","Square"}, defaultWaveform));
       
		return { parameters.begin(), parameters.end() };
	}

	static void addListenerToAllParameters(AudioProcessorValueTreeState& valueTreeState, AudioProcessorValueTreeState::Listener* listener)
	{
		std::unique_ptr<XmlElement> xml(valueTreeState.copyState().createXml());

		for (auto* element : xml->getChildWithTagNameIterator("PARAM"))
		{
			const String& id = element->getStringAttribute("id");
			valueTreeState.addParameterListener(id, listener);
		}
	}
}
