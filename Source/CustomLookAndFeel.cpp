#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel() {
    knob = juce::ImageFileFormat::loadFrom(BinaryData::knob_png, BinaryData::knob_pngSize);
    knobBase = juce::ImageFileFormat::loadFrom(BinaryData::knobBase_png, BinaryData::knobBase_pngSize);
    littleKnob = juce::ImageFileFormat::loadFrom(BinaryData::littleKnob_png, BinaryData::littleKnob_pngSize);
    holeImage = juce::ImageFileFormat::loadFrom(BinaryData::hole_png, BinaryData::hole_pngSize);
}

void CustomLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height,
                                         float sliderPosProportional, float rotaryStartAngle,
                                         float rotaryEndAngle, Slider &slider) {
    const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    
    float radius = jmin(width, height) * 0.5f;
    float centreX = x + width * 0.5f;
    float centreY = y + height * 0.5f;
    const float tickLength = 3.0f;
    const float tickThickness = 2.0f;
    const Colour tickColor = Colours::grey;

    Path originalShape, tempShape;
    originalShape.addRectangle(tickThickness * -0.5f, -radius, tickThickness, tickLength);

    g.setColour(tickColor);
    for (int i = 0; i < numTicks; ++i) {
        tempShape = originalShape;
        float tickAngle = rotaryStartAngle + (i / (float)(numTicks - 1)) * (rotaryEndAngle - rotaryStartAngle);
        tempShape.applyTransform(AffineTransform::rotation(tickAngle).translated(centreX, centreY));
        g.fillPath(tempShape);
    }

    g.saveState();
    g.addTransform(AffineTransform::translation(x + width * 0.5f, y + height * 0.5f));
    g.addTransform(AffineTransform::rotation(angle));

    float scaleFactor = jmin((float)width / knob.getWidth(), (float)height / knob.getHeight()) * 0.8f;  // Scala l'immagine della knob

    g.addTransform(AffineTransform::scale(scaleFactor, scaleFactor));
    g.drawImageTransformed(knob, AffineTransform::translation(-knob.getWidth() * 0.5f, -knob.getHeight() * 0.5f));
    g.restoreState();

    g.drawImageWithin(knobBase, width * 0.1, height * 0.1, width - width * 0.2, height - height * 0.2, RectanglePlacement::stretchToFit);
}

void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle sliderStyle, Slider &slider) {
    
    g.setOpacity(0.5);
    g.drawImageWithin(holeImage, 18, 11, 158, 7, juce::RectanglePlacement::stretchToFit);
    
    maxSliderPos = 188;
    float proportion = (sliderPos - minSliderPos) / (maxSliderPos - minSliderPos);
    
    float knobX = x + proportion * width - 30 / 2;
    knobX = jmax((float)x, jmin(knobX, (float)(x + width - 30)));
    
    g.setColour(Colours::grey);
    float tickHeight = 3.0f;
    float extendedTickHeight = tickHeight * 2;
    float tickWidth = (width-20) / 20.0f;
    for (int i = 0; i < 20; ++i) {
        float tickX = (x + 10) + i * tickWidth;
        float currentTickHeight = (i == 0 || i == 19) ? extendedTickHeight : tickHeight;
        g.drawLine(tickX, 0, tickX, currentTickHeight, 2.0f);
    }

    g.setOpacity(1);
    g.drawImageWithin(littleKnob, (int)knobX, 0, 30, 30, RectanglePlacement::stretchToFit);
}





