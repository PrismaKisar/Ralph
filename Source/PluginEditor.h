#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"


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
    
    Image backgroundImage;
    Image ralphWrite;
    Image bitCrushWrite;
    Image downSampleWrite;
    Image screwImage;
        
    //Slider gainINSlider;
    //Slider gainOUTSlider;
    /*
    Slider DryWetBCSlider;
    Slider FreqBCSlider;
    Slider AmountBCSlider;
    Slider WaveformBCSlider;
    Slider BitCrushSlider;
    Slider DryWetDSSlider;
    Slider FreqDSSlider;
    Slider AmountDSSlider;
    Slider WaveformDSSlider;
    Slider DownSampleSlider;
     */
    
    //std::unique_ptr<SliderAttachment> gainINAttachment;
    //std::unique_ptr<SliderAttachment> gainOUTAttachment;
    /*
    std::unique_ptr<SliderAttachment> DryWetBCAttachment;
    std::unique_ptr<SliderAttachment> FreqBCAttachment;
    std::unique_ptr<SliderAttachment> AmountBCAttachment;
    std::unique_ptr<SliderAttachment> WaveformBCAttachment;
    std::unique_ptr<SliderAttachment> BitCrushAttachment;
    std::unique_ptr<SliderAttachment> DryWetDSAttachment;
    std::unique_ptr<SliderAttachment> FreqDSAttachment;
    std::unique_ptr<SliderAttachment> AmountDSAttachment;
    std::unique_ptr<SliderAttachment> WaveformDSAttachment;
    std::unique_ptr<SliderAttachment> DownSampleAttachment;
     */
    
    //void setupRotarySlider(Slider& slider, int x, int y, int w, int h);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RalphAudioProcessorEditor)
};
