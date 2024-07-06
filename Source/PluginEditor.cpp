#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

constexpr int BG_GRAY = 0xFF2F2E29;
constexpr int DARK_GRAY = 0xFF20221E;

RalphAudioProcessorEditor::RalphAudioProcessorEditor (RalphAudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor(&p), audioProcessor(p), parameters(vts), lookAndFeel()
{
    setSize (800, 600);
    
    backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::texture_jpg, BinaryData::texture_jpgSize);
    ralphWrite = juce::ImageFileFormat::loadFrom(BinaryData::ralph_png, BinaryData::ralph_pngSize);
    bitCrushWrite = juce::ImageFileFormat::loadFrom(BinaryData::bitCrush_png, BinaryData::bitCrush_pngSize);
    downSampleWrite = juce::ImageFileFormat::loadFrom(BinaryData::downSample_png, BinaryData::downSample_pngSize);
    screwImage = juce::ImageFileFormat::loadFrom(BinaryData::screw_png, BinaryData::screw_pngSize);
    amountWrite = juce::ImageFileFormat::loadFrom(BinaryData::amount_png, BinaryData::amount_pngSize);
    dryWetWrite = juce::ImageFileFormat::loadFrom(BinaryData::dryWet_png, BinaryData::dryWet_pngSize);
    frequencyWrite = juce::ImageFileFormat::loadFrom(BinaryData::frequency_png, BinaryData::frequency_pngSize);
    waveformWrite = juce::ImageFileFormat::loadFrom(BinaryData::waveform_png, BinaryData::waveform_pngSize);
    glassTexture = juce::ImageFileFormat::loadFrom(BinaryData::glass_png, BinaryData::glass_pngSize);

    setupRotarySlider(gainINSlider, 25, 500, 30, 30);
    setupRotarySlider(gainOUTSlider, 745, 500, 30, 30);

    setupHorizontalSlider(BitCrushSlider, 140, 250, 200, 30);
    setupRotarySlider(AmountBCSlider, 140, 320, 80, 80);
    setupRotarySlider(FreqBCSlider, 270, 330, 60, 60);
    setupRotarySlider(WaveformBCSlider, 150, 450, 60, 60);
    setupRotarySlider(DryWetBCSlider, 260, 440, 80, 80);
    
    setupHorizontalSlider(DownSampleSlider, 460, 250, 200, 30);
    setupRotarySlider(AmountDSSlider, 460, 320, 80, 80);
    setupRotarySlider(FreqDSSlider, 590, 330, 60, 60);
    setupRotarySlider(WaveformDSSlider, 470, 450, 60, 60);
    setupRotarySlider(DryWetDSSlider, 580, 440, 80, 80);
    
    
    gainINAttachment.reset(new SliderAttachment(parameters, Parameters::nameGainIn, gainINSlider));
    gainOUTAttachment.reset(new SliderAttachment(parameters, Parameters::nameGainOut, gainOUTSlider));
    
    BitCrushAttachment.reset(new SliderAttachment(parameters, Parameters::nameBitCrush, BitCrushSlider));
    AmountBCAttachment.reset(new SliderAttachment(parameters, Parameters::nameAmountBC, AmountBCSlider));
    FreqBCAttachment.reset(new SliderAttachment(parameters, Parameters::nameFreqBC, FreqBCSlider));
    DryWetBCAttachment.reset(new SliderAttachment(parameters, Parameters::nameDryWetBC, DryWetBCSlider));
    WaveformBCAttachment.reset(new SliderAttachment(parameters, Parameters::nameWaveformBC, WaveformBCSlider));
    
    DownSampleAttachment.reset(new SliderAttachment(parameters, Parameters::nameDownSample, DownSampleSlider));
    DryWetDSAttachment.reset(new SliderAttachment(parameters, Parameters::nameDryWetDS, DryWetDSSlider));
    FreqDSAttachment.reset(new SliderAttachment(parameters, Parameters::nameFreqDS, FreqDSSlider));
    AmountDSAttachment.reset(new SliderAttachment(parameters, Parameters::nameAmountDS, AmountDSSlider));
    WaveformDSAttachment.reset(new SliderAttachment(parameters, Parameters::nameWaveformDS, WaveformDSSlider));
    
    lookAndFeelLessTick.setNumTicks(6);
    WaveformBCSlider.setLookAndFeel(&lookAndFeelLessTick);
    WaveformDSSlider.setLookAndFeel(&lookAndFeelLessTick);
    
    meterIN.reset(new Meter());
    addAndMakeVisible(meterIN.get());
    meterIN->setBounds(32, 122, 16, 366);
    meterIN->connectTo(audioProcessor.envelopeIN);
    
    meterOUT.reset(new Meter());
    addAndMakeVisible(meterOUT.get());
    meterOUT->setBounds(752, 122, 16, 366);
    meterOUT->connectTo(audioProcessor.envelopeOUT);
}

RalphAudioProcessorEditor::~RalphAudioProcessorEditor() {}

void RalphAudioProcessorEditor::paint (juce::Graphics& g) {
    
    // background
    g.setColour(juce::Colour(BG_GRAY));
    g.fillAll();

    // macro-section
    Rectangle<float> bitCrushRectagle(100, 130, 280, 430);
    Rectangle<float> downSampleRectagle(420, 130, 280, 430);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(bitCrushRectagle, 10);
    g.fillRoundedRectangle(downSampleRectagle, 10);

    // IN - OUT metering
    Rectangle<float> gainINRectangle(30, 120, 20, 370);
    Rectangle<float> gainOUTRectangle(750, 120, 20, 370);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(gainINRectangle, 2);
    g.fillRoundedRectangle(gainOUTRectangle, 2);
    
    // IN - OUT text
    Font font("times new roman", 16.0f, Font::plain);
    g.setFont(font);
    g.setColour(Colours::white);
    g.drawText("IN", 20, 97, 40, 20, Justification::horizontallyCentred);
    g.drawText("OUT", 740, 97, 40, 20, Justification::horizontallyCentred);
    
    // small texts
    g.drawImageWithin(amountWrite, 143, 397, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(amountWrite, 463, 397, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(frequencyWrite, 262, 388, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(frequencyWrite, 582, 388, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(waveformWrite, 143, 505, 70, 35, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(waveformWrite, 463, 505, 70, 35, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(dryWetWrite, 265, 520, 70, 35, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(dryWetWrite, 585, 520, 70, 35, juce::RectanglePlacement::stretchToFit);

    // background texture
    g.setOpacity(0.35);
    g.drawImageWithin(backgroundImage, 0, 0, 800, 600, juce::RectanglePlacement::stretchToFit);
    
    // screws
    g.setOpacity(1);
    g.drawImageWithin(screwImage, 10, 10, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775, 10, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775, 575, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 10, 575, 17, 17, juce::RectanglePlacement::stretchToFit);
    
    // big texts
    g.drawImageWithin(ralphWrite, 130, 0, 280, 130, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(bitCrushWrite, 130, 150, 210, 60, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(downSampleWrite, 440, 150, 230, 70, juce::RectanglePlacement::stretchToFit);
    
    // glass
    g.drawImageWithin(glassTexture, 32, 122, 16, 366, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(glassTexture, 752, 122, 16, 366, juce::RectanglePlacement::stretchToFit);
    
    
    
}

void RalphAudioProcessorEditor::resized() {}


void RalphAudioProcessorEditor::setupRotarySlider(Slider& slider, int x, int y, int w, int h) {
    slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(&slider);
    slider.setBounds(x, y, w, h);
    slider.setLookAndFeel(&lookAndFeel);
}

void RalphAudioProcessorEditor::setupHorizontalSlider(Slider& slider, int x, int y, int w, int h) {
    slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(&slider);
    slider.setBounds(x, y, w, h);
    slider.setLookAndFeel(&lookAndFeel);
}

