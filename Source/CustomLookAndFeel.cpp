#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel() {
    littleKnob = juce::ImageFileFormat::loadFrom(BinaryData::littleKnob_png, BinaryData::littleKnob_pngSize);
    holeImage = juce::ImageFileFormat::loadFrom(BinaryData::hole_png, BinaryData::hole_pngSize);
    knobWithoutPointer = juce::ImageFileFormat::loadFrom(BinaryData::knobWithoutPointer_png, BinaryData::knobWithoutPointer_pngSize);
    pointer = juce::ImageFileFormat::loadFrom(BinaryData::pointer_png, BinaryData::pointer_pngSize);

}

void CustomLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) {
    
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
    
    const float scaleFactor = 0.8f;

    const int reducedWidth = static_cast<int>(width * scaleFactor);
    const int reducedHeight = static_cast<int>(height * scaleFactor);

    const int offsetX = x + (width - reducedWidth) / 2;
    const int offsetY = y + (height - reducedHeight) / 2;

    g.drawImageWithin(knobWithoutPointer, offsetX, offsetY, reducedWidth, reducedHeight, juce::RectanglePlacement::centred);

    const double rotation = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    const float pointerScaleRelativeToKnob = 0.28f;
    const int pointerWidth = static_cast<int>(reducedWidth * pointerScaleRelativeToKnob);
    const int pointerHeight = static_cast<int>(reducedHeight * pointerScaleRelativeToKnob);
    
    const float reducedRadius = reducedWidth * 0.35f;

    g.saveState();
    g.addTransform(juce::AffineTransform::translation(offsetX + reducedWidth / 2, offsetY + reducedHeight / 2));
    g.addTransform(juce::AffineTransform::rotation(rotation));
    g.drawImageWithin(pointer, -pointerWidth / 2, -reducedRadius, pointerWidth, pointerHeight, juce::RectanglePlacement::centred);
    g.restoreState();
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
