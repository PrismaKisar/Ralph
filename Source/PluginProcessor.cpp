#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"


RalphAudioProcessor::RalphAudioProcessor() :
    parameters(*this, nullptr, "PARAMS", Parameters::createParameterLayout()),
    drywetter(Parameters::defaultDryWet),
    bitCrush(),
    lfoBC(Parameters::defaultFreq, Parameters::defaultWaveform),
    BCModulation(Parameters::defaultBitDepth, Parameters::defaultAmount)
{
    Parameters::addListenerToAllParameters(parameters, this);
}

RalphAudioProcessor::~RalphAudioProcessor() {}

void RalphAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    drywetter.prepareToPlay(sampleRate, samplesPerBlock);
    lfoBC.prepareToPlay(sampleRate);
    modulation.setSize(2, samplesPerBlock);
    BCModulation.prepareToPlay(sampleRate);
}

void RalphAudioProcessor::releaseResources() {
    drywetter.releaseResources();
    modulation.setSize(0, 0);
}

void RalphAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    const auto numSamples = buffer.getNumSamples();
    
    lfoBC.getNextAudioBlock(modulation, numSamples);
    BCModulation.processBlock(modulation, numSamples);
    
    drywetter.copyDrySignal(buffer);
    bitCrush.processBlock(buffer, modulation);
    drywetter.mixDrySignal(buffer);
}

void RalphAudioProcessor::parameterChanged(const String& paramID, float newValue) {
    if (paramID == Parameters::nameDryWet) drywetter.setDWRatio(newValue);
    if (paramID == Parameters::nameFreqBC) lfoBC.setFrequency(newValue);
    if (paramID == Parameters::nameAmountBC) BCModulation.setModAmount(newValue);
    if (paramID == Parameters::nameWaveformBC) lfoBC.setWaveform(roundToInt(newValue));
    if (paramID == Parameters::nameBitCrush) BCModulation.setParameter(newValue);
}


juce::AudioProcessorEditor* RalphAudioProcessor::createEditor() {
    return new RalphAudioProcessorEditor(*this);
}

void RalphAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void RalphAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
        if (xmlState.get() != nullptr)
            if (xmlState->hasTagName(parameters.state.getType()))
                parameters.replaceState(ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new RalphAudioProcessor();
}
