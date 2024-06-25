#pragma once
#include <JuceHeader.h>


namespace Parameters {

    // CONSTANTS
    static const float maxBitDepth = 24.0f;
    static const float minBitDepth = 2.0f;
    static const float modBitRange = 4.0f;
    static const float maxFreq = 60.0f;
    static const float minFreq = 0.05f;
    static const float minGain = -48.0f;
    static const float maxGain = 6.0f;

    // PARAM IDs
    static const String nameGainIn = "GIN";
    static const String nameGainOut = "GOUT";
    static const String nameDryWet = "DW";
    static const String nameFreqBC = "MFBC";
    static const String nameAmountBC = "ABC";
    static const String nameWaveformBC = "MWBC";
    static const String nameBitCrush = "BC";

    // PARAM DEFAULTS
    static const float defaultGain = 0.0f;
    static const float defaultDryWet = 0.5f;
    static const float defaultFreq = 1.0f;
    static const float defaultAmount = 0.0f;
    static const float defaultBitDepth = 24.0f;
    static const int defaultWaveform = 0;

    static AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
        std::vector<std::unique_ptr<RangedAudioParameter>> parameters;
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameGainIn, 1), "Gain IN", NormalisableRange<float>(minGain, maxGain, 0.1f, 3.0f), defaultGain));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameDryWet, 1), "Dry/Wet (%)", 0, 1, defaultDryWet));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameBitCrush, 1), "Bits", NormalisableRange<float>(minBitDepth, maxBitDepth - modBitRange, 0.001f, 0.4f), defaultBitDepth));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameFreqBC, 1), "LFO Frequency BitCrush (Hz)", NormalisableRange<float>(minFreq, maxFreq, 0.1f, 0.2f), defaultFreq));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameAmountBC, 1), "LFO Amount BitCrush (bits)", NormalisableRange<float>(0.0f, modBitRange, 0.01f, 1.0f), defaultAmount));
        parameters.push_back(std::make_unique<AudioParameterChoice>(ParameterID(nameWaveformBC, 1), "LFO Waveform BitCrush", StringArray{"Sinusoid","Triangular","Saw Up","Saw Down","Square"}, defaultWaveform));
        parameters.push_back(std::make_unique<AudioParameterFloat>(ParameterID(nameGainOut, 1), "Gain OUT", NormalisableRange<float>(minGain, maxGain, 0.1f, 3.0f), defaultGain));
       
        return { parameters.begin(), parameters.end() };
    }

    static void addListenerToAllParameters(AudioProcessorValueTreeState& valueTreeState, AudioProcessorValueTreeState::Listener* listener) {
        std::unique_ptr<XmlElement> xml(valueTreeState.copyState().createXml());

        for (auto* element : xml->getChildWithTagNameIterator("PARAM")) {
            const String& id = element->getStringAttribute("id");
            valueTreeState.addParameterListener(id, listener);
        }
    }
}
