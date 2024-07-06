#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

constexpr int BG_GRAY = 0xFF2F2E29;
constexpr int DARK_GRAY = 0xFF20221E;

RalphAudioProcessorEditor::RalphAudioProcessorEditor(RalphAudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor(&p), audioProcessor(p), parameters(vts), lookAndFeel(), lookAndFeelLessTick() {
    setSize(800, 600);

    // Load images
    backgroundTexture = juce::ImageFileFormat::loadFrom(BinaryData::texture_jpg, BinaryData::texture_jpgSize);
    glassTexture = juce::ImageFileFormat::loadFrom(BinaryData::glass_png, BinaryData::glass_pngSize);
    screwImage = juce::ImageFileFormat::loadFrom(BinaryData::screw_png, BinaryData::screw_pngSize);
    ralphWrite = juce::ImageFileFormat::loadFrom(BinaryData::ralph_png, BinaryData::ralph_pngSize);
    bitCrushWrite = juce::ImageFileFormat::loadFrom(BinaryData::bitCrush_png, BinaryData::bitCrush_pngSize);
    downSampleWrite = juce::ImageFileFormat::loadFrom(BinaryData::downSample_png, BinaryData::downSample_pngSize);
    amountWrite = juce::ImageFileFormat::loadFrom(BinaryData::amount_png, BinaryData::amount_pngSize);
    dryWetWrite = juce::ImageFileFormat::loadFrom(BinaryData::dryWet_png, BinaryData::dryWet_pngSize);
    frequencyWrite = juce::ImageFileFormat::loadFrom(BinaryData::frequency_png, BinaryData::frequency_pngSize);
    bitsWrite = juce::ImageFileFormat::loadFrom(BinaryData::bits_png, BinaryData::bits_pngSize);
    hertzWrite = juce::ImageFileFormat::loadFrom(BinaryData::hertz_png, BinaryData::hertz_pngSize);

    // Setup sliders
    setupSlider(gainINSlider, Slider::RotaryVerticalDrag, 25, 500, 30, 30, lookAndFeel);
    setupSlider(gainOUTSlider, Slider::RotaryVerticalDrag, 745, 500, 30, 30, lookAndFeel);

    setupSlider(BitCrushSlider, Slider::LinearHorizontal, 140, 250, 200, 30, lookAndFeel);
    setupSlider(AmountBCSlider, Slider::RotaryVerticalDrag, 140, 340, 80, 80, lookAndFeel);
    setupSlider(FreqBCSlider, Slider::RotaryVerticalDrag, 270, 350, 60, 60, lookAndFeel);
    setupSlider(WaveformBCSlider, Slider::RotaryVerticalDrag, 150, 470, 60, 60, lookAndFeelLessTick);
    setupSlider(DryWetBCSlider, Slider::RotaryVerticalDrag, 260, 460, 80, 80, lookAndFeel);

    setupSlider(DownSampleSlider, Slider::LinearHorizontal, 460, 250, 200, 30, lookAndFeel);
    setupSlider(AmountDSSlider, Slider::RotaryVerticalDrag, 460, 340, 80, 80, lookAndFeel);
    setupSlider(FreqDSSlider, Slider::RotaryVerticalDrag, 590, 350, 60, 60, lookAndFeel);
    setupSlider(WaveformDSSlider, Slider::RotaryVerticalDrag, 470, 470, 60, 60, lookAndFeelLessTick);
    setupSlider(DryWetDSSlider, Slider::RotaryVerticalDrag, 580, 460, 80, 80, lookAndFeel);

    // Attach sliders
    gainINAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameGainIn, gainINSlider);
    gainOUTAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameGainOut, gainOUTSlider);

    BitCrushAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameBitCrush, BitCrushSlider);
    AmountBCAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameAmountBC, AmountBCSlider);
    FreqBCAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameFreqBC, FreqBCSlider);
    DryWetBCAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameDryWetBC, DryWetBCSlider);
    WaveformBCAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameWaveformBC, WaveformBCSlider);

    DownSampleAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameDownSample, DownSampleSlider);
    DryWetDSAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameDryWetDS, DryWetDSSlider);
    FreqDSAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameFreqDS, FreqDSSlider);
    AmountDSAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameAmountDS, AmountDSSlider);
    WaveformDSAttachment = std::make_unique<SliderAttachment>(parameters, Parameters::nameWaveformDS, WaveformDSSlider);

    // Setup meters
    meterIN = std::make_unique<Meter>();
    addAndMakeVisible(meterIN.get());
    meterIN->setBounds(32, 122, 16, 366);
    meterIN->connectTo(audioProcessor.envelopeIN);

    meterOUT = std::make_unique<Meter>();
    addAndMakeVisible(meterOUT.get());
    meterOUT->setBounds(752, 122, 16, 366);
    meterOUT->connectTo(audioProcessor.envelopeOUT);
}

RalphAudioProcessorEditor::~RalphAudioProcessorEditor() {}

void RalphAudioProcessorEditor::paint(juce::Graphics& g) {
    drawBackground(g);
    drawMacroSections(g);
    drawMeters(g);
    drawTexts(g);
    drawTextures(g);
    drawScrews(g);
}

void RalphAudioProcessorEditor::resized() {}

void RalphAudioProcessorEditor::setupSlider(Slider& slider, Slider::SliderStyle style, int x, int y, int w, int h, CustomLookAndFeel& lookAndFeel) {
    slider.setSliderStyle(style);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(&slider);
    slider.setBounds(x, y, w, h);
    slider.setLookAndFeel(&lookAndFeel);
}

void RalphAudioProcessorEditor::drawBackground(Graphics& g) {
    g.setColour(juce::Colour(BG_GRAY));
    g.fillAll();
}

void RalphAudioProcessorEditor::drawMacroSections(Graphics& g) {
    Rectangle<float> bitCrushRectagle(100, 130, 280, 430);
    Rectangle<float> downSampleRectagle(420, 130, 280, 430);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(bitCrushRectagle, 10);
    g.fillRoundedRectangle(downSampleRectagle, 10);
}

void RalphAudioProcessorEditor::drawMeters(Graphics& g) {
    Rectangle<float> gainINRectangle(30, 120, 20, 370);
    Rectangle<float> gainOUTRectangle(750, 120, 20, 370);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(gainINRectangle, 2);
    g.fillRoundedRectangle(gainOUTRectangle, 2);
}

void RalphAudioProcessorEditor::drawTexts(Graphics& g) {
    Font font("times new roman", 16.0f, Font::plain);
    g.setFont(font);
    g.setColour(Colours::white);
    g.drawText("IN", 20, 97, 40, 20, Justification::horizontallyCentred);
    g.drawText("OUT", 740, 97, 40, 20, Justification::horizontallyCentred);

    g.drawImageWithin(amountWrite, 143, 310, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(amountWrite, 463, 310, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(frequencyWrite, 262, 320, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(frequencyWrite, 582, 320, 70, 25, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(dryWetWrite, 270, 430, 60, 30, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(dryWetWrite, 590, 430, 60, 30, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(bitsWrite, 220, 275, 40, 20, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(hertzWrite, 530, 275, 50, 25, juce::RectanglePlacement::centred);

    g.drawImageWithin(ralphWrite, 130, 0, 280, 130, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(bitCrushWrite, 130, 150, 210, 60, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(downSampleWrite, 440, 150, 230, 70, juce::RectanglePlacement::stretchToFit);
}

void RalphAudioProcessorEditor::drawTextures(Graphics& g) {
    g.setOpacity(0.35);
    g.drawImageWithin(backgroundTexture, 0, 0, 800, 600, juce::RectanglePlacement::stretchToFit);

    g.setOpacity(1);
    g.drawImageWithin(glassTexture, 32, 122, 16, 366, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(glassTexture, 752, 122, 16, 366, juce::RectanglePlacement::stretchToFit);
}

void RalphAudioProcessorEditor::drawScrews(Graphics& g) {
    g.setOpacity(1);
    g.drawImageWithin(screwImage, 10, 10, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775, 10, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775, 575, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 10, 575, 17, 17, juce::RectanglePlacement::stretchToFit);
}
