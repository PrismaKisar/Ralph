#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "Meter.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class RalphAudioProcessorEditor  : public juce::AudioProcessorEditor {
public:
    RalphAudioProcessorEditor (RalphAudioProcessor&, AudioProcessorValueTreeState&);
    ~RalphAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    RalphAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& parameters;
    CustomLookAndFeel lookAndFeel, lookAndFeelLessTick;
    
    std::unique_ptr<Meter> meterIN;
    std::unique_ptr<Meter> meterOUT;
    
    Image backgroundTexture;
    Image glassTexture;

    Image screwImage;
    
    Image ralphWrite;
    Image bitCrushWrite;
    Image downSampleWrite;
    Image bitsWrite;
    Image hertzWrite;
    Image frequencyWrite;
    Image amountWrite;
    Image dryWetWrite;
    Image waveformWrite;
        
    Slider gainINSlider;
    Slider gainOUTSlider;
    
    Slider BitCrushSlider;
    Slider AmountBCSlider;
    Slider FreqBCSlider;
    Slider DryWetBCSlider;
    Slider WaveformBCSlider;
    
    Slider DownSampleSlider;
    Slider DryWetDSSlider;
    Slider FreqDSSlider;
    Slider AmountDSSlider;
    Slider WaveformDSSlider;
    
    std::unique_ptr<SliderAttachment> gainINAttachment;
    std::unique_ptr<SliderAttachment> gainOUTAttachment;
    
    std::unique_ptr<SliderAttachment> BitCrushAttachment;
    std::unique_ptr<SliderAttachment> AmountBCAttachment;
    std::unique_ptr<SliderAttachment> FreqBCAttachment;
    std::unique_ptr<SliderAttachment> DryWetBCAttachment;
    std::unique_ptr<SliderAttachment> WaveformBCAttachment;
    
    std::unique_ptr<SliderAttachment> DownSampleAttachment;
    std::unique_ptr<SliderAttachment> DryWetDSAttachment;
    std::unique_ptr<SliderAttachment> FreqDSAttachment;
    std::unique_ptr<SliderAttachment> AmountDSAttachment;
    std::unique_ptr<SliderAttachment> WaveformDSAttachment;
    
    void setupRotarySlider(Slider& slider, int x, int y, int w, int h);
    void setupHorizontalSlider(Slider& slider, int x, int y, int w, int h);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RalphAudioProcessorEditor)
};
