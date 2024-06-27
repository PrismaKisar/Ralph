#pragma once

#include <JuceHeader.h>
#include "DryWet.h"
#include "Oscillator.h"
#include "BitCrush.h"
#include "DownSample.h"
#include "ModulationControl.h"

class RalphAudioProcessor : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    RalphAudioProcessor();
    ~RalphAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return false; }

    const juce::String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 1; }
    void setCurrentProgram (int index) override {}
    const juce::String getProgramName (int index) override { return {}; }
    void changeProgramName (int index, const juce::String& newName) override {}

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    AudioProcessorValueTreeState parameters;
    
    SmoothedValue<float, ValueSmoothingTypes::Linear> GainIn;
    SmoothedValue<float, ValueSmoothingTypes::Linear> GainOut;
    DryWet drywetter;
    
    BitCrush bitCrush;
    Oscillator lfoBC;
    AudioBuffer<double> BCMod;
    ModulationControl BCModCtrl;
    
    DownSample downSample;
    Oscillator lfoDS;
    AudioBuffer<double> DSMod;
    ModulationControl DSModCtrl;
    
    void parameterChanged(const String& paramID, float newValue) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RalphAudioProcessor)
};

