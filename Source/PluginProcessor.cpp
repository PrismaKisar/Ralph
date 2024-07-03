#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

RalphAudioProcessor::RalphAudioProcessor() :
    parameters(*this, nullptr, "PARAMS", Parameters::createParameterLayout()),
    bitCrush(),
    lfoBC(Parameters::defaultFreq, Parameters::defaultWaveform),
    BCModCtrl(Parameters::defaultBitDepth, Parameters::defaultAmount),
    downSample(),
    lfoDS(Parameters::defaultFreq, Parameters::defaultWaveform),
    DSModCtrl(Parameters::defaultBitDepth, Parameters::defaultAmount)
{
    GainIn.setCurrentAndTargetValue(1.0f);
    GainOut.setCurrentAndTargetValue(1.0f);
    Parameters::addListenerToAllParameters(parameters, this);
}

RalphAudioProcessor::~RalphAudioProcessor() {}

void RalphAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    auto numCh = jmax(getTotalNumOutputChannels(), getTotalNumInputChannels());
    dsp::ProcessSpec spec {sampleRate, (uint32)samplesPerBlock, (uint32)numCh};
    bitCrush.prepare(spec);
    GainIn.reset(sampleRate, 0.02);
    GainOut.reset(sampleRate, 0.02);
    downSample.prepareToPlay(sampleRate, samplesPerBlock, spec);
    lfoBC.prepareToPlay(sampleRate);
    BCMod.setSize(2, samplesPerBlock);
    BCModCtrl.prepareToPlay(sampleRate);
    lfoDS.prepareToPlay(sampleRate);
    DSMod.setSize(2, samplesPerBlock);
    DSModCtrl.prepareToPlay(sampleRate);
}

void RalphAudioProcessor::releaseResources() {
    BCMod.setSize(0, 0);
    downSample.releaseResources();
    DSMod.setSize(0, 0);
}

void RalphAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    const auto numSamples = buffer.getNumSamples();
    
    GainIn.applyGain(buffer, numSamples);
    envelopeIN.set(jmax(envelopeIN.get(), buffer.getMagnitude(0, numSamples)));

    lfoDS.getNextAudioBlock(DSMod, numSamples);
    DSModCtrl.processBlock(DSMod, numSamples);
    lfoBC.getNextAudioBlock(BCMod, numSamples);
    BCModCtrl.processBlock(BCMod, numSamples);
    
    bitCrush.processBlock(buffer, BCMod);
    downSample.processBlock(buffer, DSMod);
    
    GainOut.applyGain(buffer, numSamples);
    envelopeOUT.set(jmax(envelopeOUT.get(), buffer.getMagnitude(0, numSamples)));

}

void RalphAudioProcessor::parameterChanged(const String& paramID, float newValue) {
    if (paramID == Parameters::nameDryWetDS) downSample.setDryWet(newValue * 0.01);
    if (paramID == Parameters::nameFreqDS) lfoDS.setFrequency(newValue);
    if (paramID == Parameters::nameWaveformDS) lfoDS.setWaveform(roundToInt(newValue));
    if (paramID == Parameters::nameAmountDS) DSModCtrl.setModAmount(newValue);
    if (paramID == Parameters::nameDownSample) DSModCtrl.setParameter(newValue);
    if (paramID == Parameters::nameDryWetBC) bitCrush.setDryWet(newValue * 0.01);
    if (paramID == Parameters::nameFreqBC) lfoBC.setFrequency(newValue);
    if (paramID == Parameters::nameWaveformBC) lfoBC.setWaveform(roundToInt(newValue));
    if (paramID == Parameters::nameAmountBC) BCModCtrl.setModAmount(newValue);
    if (paramID == Parameters::nameBitCrush) BCModCtrl.setParameter(newValue);
    if (paramID == Parameters::nameGainIn) GainIn.setTargetValue(Decibels::decibelsToGain(newValue));
    if (paramID == Parameters::nameGainOut) GainOut.setTargetValue(Decibels::decibelsToGain(newValue));
}


juce::AudioProcessorEditor* RalphAudioProcessor::createEditor() {
    return new RalphAudioProcessorEditor(*this, parameters);
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
