#pragma once
#include <JuceHeader.h>

namespace Parameters {

    // CONSTANTS
    constexpr float maxBitDepth = 24.0f;
    constexpr float minBitDepth = 4.0f;
    constexpr float modBitRange = 4.0f;
    constexpr float maxSR = 44100.0f;
    constexpr float minSR = 500.0f;
    constexpr float modSRRange = 10000.0;
    constexpr float maxFreq = 60.0f;
    constexpr float minFreq = 0.01f;
    constexpr float minGain = -48.0f;
    constexpr float maxGain = 6.0f;

    // PARAM IDs
    extern const juce::String nameGainIn;
    extern const juce::String nameGainOut;
    extern const juce::String nameDryWetBC;
    extern const juce::String nameFreqBC;
    extern const juce::String nameAmountBC;
    extern const juce::String nameWaveformBC;
    extern const juce::String nameBitCrush;
    extern const juce::String nameDryWetDS;
    extern const juce::String nameFreqDS;
    extern const juce::String nameAmountDS;
    extern const juce::String nameWaveformDS;
    extern const juce::String nameDownSample;

    // PARAM DEFAULTS
    constexpr float defaultGain = 0.0f;
    constexpr float defaultDryWet = 100.0f;
    constexpr float defaultFreq = 1.0f;
    constexpr float defaultAmount = 0.0f;
    constexpr float defaultSR = 44100.0f;
    constexpr float defaultBitDepth = 24.0f;
    constexpr int defaultWaveform = 0;

    // Helper function to create float parameters
    std::unique_ptr<juce::RangedAudioParameter> createFloatParameter(const juce::String& id, const juce::String& name, float minValue, float maxValue, float defaultValue, float step = 0.1f, float skew = 1.0f);

    // Helper function to create choice parameters
    std::unique_ptr<juce::RangedAudioParameter> createChoiceParameter(const juce::String& id, const juce::String& name, const juce::StringArray& choices, int defaultChoice);

    // Create parameter layout
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    // Add listeners to all parameters
    void addListenerToAllParameters(juce::AudioProcessorValueTreeState& valueTreeState, juce::AudioProcessorValueTreeState::Listener* listener);
}
