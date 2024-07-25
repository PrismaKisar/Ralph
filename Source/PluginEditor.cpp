#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

constexpr int BG_GRAY = 0xFF2F2E29;
constexpr int DARK_GRAY = 0xFF20221E;

RalphComponent::RalphComponent(RalphAudioProcessor& p, AudioProcessorValueTreeState& vts)
: audioProcessor(p), parameters(vts), lookAndFeel(), lookAndFeelLessTick() {
    
    lookAndFeelLessTick.setNumTicks(6);

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
    zeroImage = juce::ImageFileFormat::loadFrom(BinaryData::zero_png, BinaryData::zero_pngSize);
    hundredImage = juce::ImageFileFormat::loadFrom(BinaryData::hundred_png, BinaryData::hundred_pngSize);
    pointOOneImage = juce::ImageFileFormat::loadFrom(BinaryData::pointOOne_png, BinaryData::pointOOne_pngSize);
    sixtyImage = juce::ImageFileFormat::loadFrom(BinaryData::sixty_png, BinaryData::sixty_pngSize);
    fourImage = juce::ImageFileFormat::loadFrom(BinaryData::four_png, BinaryData::four_pngSize);
    tenKImage = juce::ImageFileFormat::loadFrom(BinaryData::tenK_png, BinaryData::tenK_pngSize);
    twentyFourImage = juce::ImageFileFormat::loadFrom(BinaryData::twentyFour_png, BinaryData::twentyFour_pngSize);
    fiveHundredImage = juce::ImageFileFormat::loadFrom(BinaryData::fiveHundred_png, BinaryData::fiveHundred_pngSize);
    fourFourKImage = juce::ImageFileFormat::loadFrom(BinaryData::fourFourK_png, BinaryData::fourFourK_pngSize);
    triImage = juce::ImageFileFormat::loadFrom(BinaryData::tri_png, BinaryData::tri_pngSize);
    sinImage = juce::ImageFileFormat::loadFrom(BinaryData::sin_png, BinaryData::sin_pngSize);
    sawUpImage = juce::ImageFileFormat::loadFrom(BinaryData::sawUp_png, BinaryData::sawUp_pngSize);;
    sawDownImage = juce::ImageFileFormat::loadFrom(BinaryData::sawDown_png, BinaryData::sawDown_pngSize);;
    quadImage = juce::ImageFileFormat::loadFrom(BinaryData::quad_png, BinaryData::quad_pngSize);;
    shImage = juce::ImageFileFormat::loadFrom(BinaryData::sh_png, BinaryData::sh_pngSize);;


    // Setup sliders
    setupSlider(gainINSlider, Slider::RotaryVerticalDrag, 25 * SCALE_FACTOR, 500 * SCALE_FACTOR, 30 * SCALE_FACTOR, 30 * SCALE_FACTOR, lookAndFeel);
    setupSlider(gainOUTSlider, Slider::RotaryVerticalDrag, 745 * SCALE_FACTOR, 500 * SCALE_FACTOR, 30 * SCALE_FACTOR, 30 * SCALE_FACTOR, lookAndFeel);

    setupSlider(BitCrushSlider, Slider::LinearHorizontal, 140 * SCALE_FACTOR, 250 * SCALE_FACTOR, 200 * SCALE_FACTOR, 30 * SCALE_FACTOR, lookAndFeel);
    setupSlider(AmountBCSlider, Slider::RotaryVerticalDrag, 140 * SCALE_FACTOR, 340 * SCALE_FACTOR, 80 * SCALE_FACTOR, 80 * SCALE_FACTOR, lookAndFeel);
    setupSlider(FreqBCSlider, Slider::RotaryVerticalDrag, 270 * SCALE_FACTOR, 350 * SCALE_FACTOR, 60 * SCALE_FACTOR, 60 * SCALE_FACTOR, lookAndFeel);
    setupSlider(WaveformBCSlider, Slider::RotaryVerticalDrag, 150 * SCALE_FACTOR, 470 * SCALE_FACTOR, 60 * SCALE_FACTOR, 60 * SCALE_FACTOR, lookAndFeelLessTick);
    setupSlider(DryWetBCSlider, Slider::RotaryVerticalDrag, 260 * SCALE_FACTOR, 460 * SCALE_FACTOR, 80 * SCALE_FACTOR, 80 * SCALE_FACTOR, lookAndFeel);

    setupSlider(DownSampleSlider, Slider::LinearHorizontal, 460 * SCALE_FACTOR, 250 * SCALE_FACTOR, 200 * SCALE_FACTOR, 30 * SCALE_FACTOR, lookAndFeel);
    setupSlider(AmountDSSlider, Slider::RotaryVerticalDrag, 460 * SCALE_FACTOR, 340 * SCALE_FACTOR, 80 * SCALE_FACTOR, 80 * SCALE_FACTOR, lookAndFeel);
    setupSlider(FreqDSSlider, Slider::RotaryVerticalDrag, 590 * SCALE_FACTOR, 350 * SCALE_FACTOR, 60 * SCALE_FACTOR, 60 * SCALE_FACTOR, lookAndFeel);
    setupSlider(WaveformDSSlider, Slider::RotaryVerticalDrag, 470 * SCALE_FACTOR, 470 * SCALE_FACTOR, 60 * SCALE_FACTOR, 60 * SCALE_FACTOR, lookAndFeelLessTick);
    setupSlider(DryWetDSSlider, Slider::RotaryVerticalDrag, 580 * SCALE_FACTOR, 460 * SCALE_FACTOR, 80 * SCALE_FACTOR, 80 * SCALE_FACTOR, lookAndFeel);

    

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
    meterIN->setBounds(32 * SCALE_FACTOR, 122 * SCALE_FACTOR, 16 * SCALE_FACTOR, 366 * SCALE_FACTOR);
    meterIN->connectTo(audioProcessor.envelopeIN);

    meterOUT = std::make_unique<Meter>();
    addAndMakeVisible(meterOUT.get());
    meterOUT->setBounds(752 * SCALE_FACTOR, 122 * SCALE_FACTOR, 16 * SCALE_FACTOR, 366 * SCALE_FACTOR);
    meterOUT->connectTo(audioProcessor.envelopeOUT);
}

RalphComponent::~RalphComponent() {}

void RalphComponent::paint(juce::Graphics& g) {
    drawBackground(g);
    drawMacroSections(g);
    drawMeters(g);
    drawTexts(g);
    drawTextures(g);
    drawScrews(g);
    
    g.drawImageWithin(zeroImage, 270 * SCALE_FACTOR, 535 * SCALE_FACTOR, 7 * SCALE_FACTOR, 8 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(zeroImage, 590 * SCALE_FACTOR, 535 * SCALE_FACTOR, 7 * SCALE_FACTOR, 8 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(hundredImage, 320 * SCALE_FACTOR, 535 * SCALE_FACTOR, 15 * SCALE_FACTOR, 8 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(hundredImage, 640 * SCALE_FACTOR, 535 * SCALE_FACTOR, 15 * SCALE_FACTOR, 8 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(pointOOneImage, 270 * SCALE_FACTOR, 410 * SCALE_FACTOR, 17 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(pointOOneImage, 590 * SCALE_FACTOR, 410 * SCALE_FACTOR, 17 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(sixtyImage, 315 * SCALE_FACTOR, 410 * SCALE_FACTOR, 13 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(sixtyImage, 635 * SCALE_FACTOR, 410 * SCALE_FACTOR, 13 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(zeroImage, 147 * SCALE_FACTOR, 417 * SCALE_FACTOR, 9 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(zeroImage, 467 * SCALE_FACTOR, 417 * SCALE_FACTOR, 9 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(fourImage, 203 * SCALE_FACTOR, 417 * SCALE_FACTOR, 10 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(tenKImage, 520 * SCALE_FACTOR, 417 * SCALE_FACTOR, 18 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(fourImage, 155 * SCALE_FACTOR, 235 * SCALE_FACTOR, 10 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(twentyFourImage, 305 * SCALE_FACTOR, 235 * SCALE_FACTOR, 18 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(fiveHundredImage, 470 * SCALE_FACTOR, 235 * SCALE_FACTOR, 20 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(fourFourKImage, 620 * SCALE_FACTOR, 235 * SCALE_FACTOR, 27 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    
    g.setOpacity(0.7);
    g.drawImageWithin(triImage, 135 * SCALE_FACTOR, 493 * SCALE_FACTOR, 10 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(triImage, 455 * SCALE_FACTOR, 493 * SCALE_FACTOR, 10 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(sawUpImage, 155 * SCALE_FACTOR, 460 * SCALE_FACTOR, 12 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(sawUpImage, 475 * SCALE_FACTOR, 460 * SCALE_FACTOR, 12 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(sawDownImage, 193 * SCALE_FACTOR, 460 * SCALE_FACTOR, 12 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(sawDownImage, 513 * SCALE_FACTOR, 460 * SCALE_FACTOR, 12 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(quadImage, 215 * SCALE_FACTOR, 493 * SCALE_FACTOR, 10 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(quadImage, 535 * SCALE_FACTOR, 493 * SCALE_FACTOR, 10 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);

    g.setOpacity(0.6);
    g.drawImageWithin(sinImage, 150 * SCALE_FACTOR, 528 * SCALE_FACTOR, 17 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(sinImage, 470 * SCALE_FACTOR, 528 * SCALE_FACTOR, 17 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(shImage, 193 * SCALE_FACTOR, 528 * SCALE_FACTOR, 20 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(shImage, 513 * SCALE_FACTOR, 528 * SCALE_FACTOR, 20 * SCALE_FACTOR, 10 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
}
void RalphComponent::resized() {
    
}

void RalphComponent::setupSlider(Slider& slider, Slider::SliderStyle style, int x, int y, int w, int h, CustomLookAndFeel& lookAndFeel) {
    slider.setSliderStyle(style);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 80 * SCALE_FACTOR, 20 * SCALE_FACTOR);
    addAndMakeVisible(&slider);
    slider.setBounds(x, y, w, h);
    slider.setLookAndFeel(&lookAndFeel);
}

void RalphComponent::drawBackground(Graphics& g) {
    g.setColour(juce::Colour(BG_GRAY));
    g.fillAll();
}

void RalphComponent::drawMacroSections(Graphics& g) {
    Rectangle<float> bitCrushRectagle(100 * SCALE_FACTOR, 130 * SCALE_FACTOR, 280 * SCALE_FACTOR, 430 * SCALE_FACTOR);
    Rectangle<float> downSampleRectagle(420 * SCALE_FACTOR, 130 * SCALE_FACTOR, 280 * SCALE_FACTOR, 430 * SCALE_FACTOR);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(bitCrushRectagle, 10 * SCALE_FACTOR);
    g.fillRoundedRectangle(downSampleRectagle, 10 * SCALE_FACTOR);
}

void RalphComponent::drawMeters(Graphics& g) {
    Rectangle<float> gainINRectangle(30 * SCALE_FACTOR, 120 * SCALE_FACTOR, 20 * SCALE_FACTOR, 370 * SCALE_FACTOR);
    Rectangle<float> gainOUTRectangle(750 * SCALE_FACTOR, 120 * SCALE_FACTOR, 20 * SCALE_FACTOR, 370 * SCALE_FACTOR);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(gainINRectangle, 2 * SCALE_FACTOR);
    g.fillRoundedRectangle(gainOUTRectangle, 2 * SCALE_FACTOR);
}

void RalphComponent::drawTexts(Graphics& g) {
    Font font("times new roman", 16.0f * SCALE_FACTOR, Font::plain);
    g.setFont(font);
    g.setColour(Colours::white);
    g.drawText("IN", 20 * SCALE_FACTOR, 97 * SCALE_FACTOR, 40 * SCALE_FACTOR, 20 * SCALE_FACTOR, Justification::horizontallyCentred);
    g.drawText("OUT", 740 * SCALE_FACTOR, 97 * SCALE_FACTOR, 40 * SCALE_FACTOR, 20 * SCALE_FACTOR, Justification::horizontallyCentred);

    g.drawImageWithin(amountWrite, 143 * SCALE_FACTOR, 310 * SCALE_FACTOR, 70 * SCALE_FACTOR, 25 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(amountWrite, 463 * SCALE_FACTOR, 310 * SCALE_FACTOR, 70 * SCALE_FACTOR, 25 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(frequencyWrite, 262 * SCALE_FACTOR, 320 * SCALE_FACTOR, 70 * SCALE_FACTOR, 25 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(frequencyWrite, 582 * SCALE_FACTOR, 320 * SCALE_FACTOR, 70 * SCALE_FACTOR, 25 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(dryWetWrite, 270 * SCALE_FACTOR, 430 * SCALE_FACTOR, 60 * SCALE_FACTOR, 30 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(dryWetWrite, 590 * SCALE_FACTOR, 430 * SCALE_FACTOR, 60 * SCALE_FACTOR, 30 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(bitsWrite, 220 * SCALE_FACTOR, 275 * SCALE_FACTOR, 40 * SCALE_FACTOR, 20 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(hertzWrite, 530 * SCALE_FACTOR, 275 * SCALE_FACTOR, 50 * SCALE_FACTOR, 25 * SCALE_FACTOR, juce::RectanglePlacement::centred);

    g.drawImageWithin(ralphWrite, 130 * SCALE_FACTOR, 0 * SCALE_FACTOR, 280 * SCALE_FACTOR, 130 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(bitCrushWrite, 130 * SCALE_FACTOR, 150 * SCALE_FACTOR, 210 * SCALE_FACTOR, 60 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(downSampleWrite, 440 * SCALE_FACTOR, 150 * SCALE_FACTOR, 230 * SCALE_FACTOR, 70 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
}

void RalphComponent::drawTextures(Graphics& g) {
    g.setOpacity(0.12);
    g.drawImageWithin(backgroundTexture, 0 * SCALE_FACTOR, 0 * SCALE_FACTOR, 800 * SCALE_FACTOR, 600 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);

    g.setOpacity(1);
    g.drawImageWithin(glassTexture, 32 * SCALE_FACTOR, 122 * SCALE_FACTOR, 16 * SCALE_FACTOR, 366 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(glassTexture, 752 * SCALE_FACTOR, 122 * SCALE_FACTOR, 16 * SCALE_FACTOR, 366 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
}

void RalphComponent::drawScrews(Graphics& g) {
    g.setOpacity(1);
    g.drawImageWithin(screwImage, 10 * SCALE_FACTOR, 10 * SCALE_FACTOR, 17 * SCALE_FACTOR, 17 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775 * SCALE_FACTOR, 10 * SCALE_FACTOR, 17 * SCALE_FACTOR, 17 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775 * SCALE_FACTOR, 575 * SCALE_FACTOR, 17 * SCALE_FACTOR, 17 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 10 * SCALE_FACTOR, 575 * SCALE_FACTOR, 17 * SCALE_FACTOR, 17 * SCALE_FACTOR, juce::RectanglePlacement::stretchToFit);
}


WrappedRalphAudioProcessorEditor::WrappedRalphAudioProcessorEditor(RalphAudioProcessor& p, AudioProcessorValueTreeState& vts) :
AudioProcessorEditor(p), ralphComponent(p, vts), parameters(vts)
{
    addAndMakeVisible(ralphComponent);
    
    PropertiesFile::Options options;
    options.applicationName = ProjectInfo::projectName;
    options.commonToAllUsers = true;
    options.filenameSuffix = "settings";
    options.osxLibrarySubFolder = "Application Support";
    applicationProperties.setStorageParameters(options);
    
    if (auto* costrainer = getConstrainer()) {
        costrainer->setFixedAspectRatio(static_cast<double>(originalWidth) / static_cast<double>(originalHeight));
        costrainer->setSizeLimits(originalWidth / 4, originalHeight / 4, originalWidth * 2, originalHeight * 2);
    }
    
    auto sizeRatio{1.f};
    if (auto* properties = applicationProperties.getCommonSettings(true))
        sizeRatio = properties->getDoubleValue("sizeRatio", 1.0);
    
    setResizable(true, true);
    setSize(static_cast<float>(originalWidth * sizeRatio), static_cast<float>(originalHeight * sizeRatio));
}

void WrappedRalphAudioProcessorEditor::resized() {
    const auto scaleFactor = static_cast<float>(getWidth()) / originalWidth;
    if (auto* properties = applicationProperties.getCommonSettings(true))
        properties->setValue("sizeRatio", scaleFactor);

    ralphComponent.setTransform(AffineTransform::scale(scaleFactor));
    ralphComponent.setBounds(0, 0, originalWidth, originalHeight);
}

