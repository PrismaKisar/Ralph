#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr int ORANGE = 0xFFFFA600;
constexpr int LIGHT_GRAY = 0xFF8E8A82;
constexpr int BG_GRAY = 0xFF2F2E29;
constexpr int DARK_GRAY = 0xFF20221E;

RalphAudioProcessorEditor::RalphAudioProcessorEditor (RalphAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 600);
    backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::texture_jpg, BinaryData::texture_jpgSize);
    ralphWrite = juce::ImageFileFormat::loadFrom(BinaryData::ralph_png, BinaryData::ralph_pngSize);
    bitCrushWrite = juce::ImageFileFormat::loadFrom(BinaryData::bitCrush_png, BinaryData::bitCrush_pngSize);
    downSampleWrite = juce::ImageFileFormat::loadFrom(BinaryData::downSample_png, BinaryData::downSample_pngSize);
    screwImage = juce::ImageFileFormat::loadFrom(BinaryData::screw_png, BinaryData::screw_pngSize);
}

RalphAudioProcessorEditor::~RalphAudioProcessorEditor() {}

void RalphAudioProcessorEditor::paint (juce::Graphics& g) {
    
    g.setColour(juce::Colour(BG_GRAY));
    g.fillAll();


    Rectangle<float> bitCrushRectagle(100, 150, 280, 400);
    Rectangle<float> downSampleRectagle(420, 150, 280, 400);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(bitCrushRectagle, 10);
    g.fillRoundedRectangle(downSampleRectagle, 10);


    Rectangle<float> gainINRectangle(30, 120, 20, 370);
    Rectangle<float> gainOUTRectangle(750, 120, 20, 370);
    g.setColour(juce::Colour(DARK_GRAY));
    g.fillRoundedRectangle(gainINRectangle, 2);
    g.fillRoundedRectangle(gainOUTRectangle, 2);
    
    

    
    
    Font font("times new roman", 16.0f, Font::plain);
    g.setFont(font);
    g.setColour(Colours::white);
    g.drawText("IN", 20, 97, 40, 20, Justification::horizontallyCentred);
    g.drawText("OUT", 740, 97, 40, 20, Justification::horizontallyCentred);

    
    g.setOpacity(0.35);
    g.drawImageWithin(backgroundImage, 0, 0, 800, 600, juce::RectanglePlacement::stretchToFit);
    
    
    g.setOpacity(1);
    g.drawImageWithin(screwImage, 10, 10, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775, 10, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 775, 575, 17, 17, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(screwImage, 10, 575, 17, 17, juce::RectanglePlacement::stretchToFit);
    
    
    g.drawImageWithin(ralphWrite, 130, 10, 280, 130, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(bitCrushWrite, 130, 170, 210, 60, juce::RectanglePlacement::stretchToFit);
    g.drawImageWithin(downSampleWrite, 450, 170, 210, 60, juce::RectanglePlacement::stretchToFit);
}

void RalphAudioProcessorEditor::resized() {}
