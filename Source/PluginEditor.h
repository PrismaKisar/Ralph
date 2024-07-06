#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"
#include "Meter.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class RalphAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    RalphAudioProcessorEditor(RalphAudioProcessor&, AudioProcessorValueTreeState&);
    ~RalphAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    RalphAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& parameters;

    CustomLookAndFeel lookAndFeel, lookAndFeelLessTick;

    std::unique_ptr<Meter> meterIN, meterOUT;

    // Image assets
    Image backgroundTexture, glassTexture, screwImage;
    Image ralphWrite, bitCrushWrite, downSampleWrite;
    Image bitsWrite, hertzWrite, frequencyWrite, amountWrite, dryWetWrite, waveformWrite;

    // Sliders
    Slider gainINSlider, gainOUTSlider;
    Slider BitCrushSlider, AmountBCSlider, FreqBCSlider, DryWetBCSlider, WaveformBCSlider;
    Slider DownSampleSlider, DryWetDSSlider, FreqDSSlider, AmountDSSlider, WaveformDSSlider;

    // Slider attachments
    std::unique_ptr<SliderAttachment> gainINAttachment, gainOUTAttachment;
    std::unique_ptr<SliderAttachment> BitCrushAttachment, AmountBCAttachment, FreqBCAttachment, DryWetBCAttachment, WaveformBCAttachment;
    std::unique_ptr<SliderAttachment> DownSampleAttachment, DryWetDSAttachment, FreqDSAttachment, AmountDSAttachment, WaveformDSAttachment;

    // Helper functions for setting up sliders
    void setupSlider(Slider& slider, Slider::SliderStyle style, int x, int y, int w, int h, CustomLookAndFeel& lookAndFeel);

    // Helper functions for drawing elements
    void drawBackground(Graphics& g);
    void drawMacroSections(Graphics& g);
    void drawMeters(Graphics& g);
    void drawTexts(Graphics& g);
    void drawTextures(Graphics& g);
    void drawScrews(Graphics& g);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RalphAudioProcessorEditor)
};
