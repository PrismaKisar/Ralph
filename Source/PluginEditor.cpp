#include "PluginProcessor.h"
#include "PluginEditor.h"

constexpr int ORANGE = 0xE0FFA600;
constexpr int LIGHT_GRAY = 0xC08E8A82;
constexpr int BG_GRAY = 0xC02F2E29;
constexpr int DARK_GRAY = 0xA020221E;

RalphAudioProcessorEditor::RalphAudioProcessorEditor (RalphAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 600);
    backgroundImage = juce::ImageFileFormat::loadFrom(BinaryData::texture_jpg, BinaryData::texture_jpgSize);
}

RalphAudioProcessorEditor::~RalphAudioProcessorEditor() {}

void RalphAudioProcessorEditor::paint (juce::Graphics& g) {
    g.drawImageWithin(backgroundImage, 0, 0, 800, 600, juce::RectanglePlacement::stretchToFit);
    
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
}

void RalphAudioProcessorEditor::resized() {}
