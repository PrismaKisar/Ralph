#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel() {
    knob = juce::ImageFileFormat::loadFrom(BinaryData::knob_png, BinaryData::knob_pngSize);
    knobBase = juce::ImageFileFormat::loadFrom(BinaryData::knobBase_png, BinaryData::knobBase_pngSize);
}

void CustomLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) {
    const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    
    g.saveState();
    g.addTransform(AffineTransform::translation(x + width * 0.5f, y + height * 0.5f));
    g.addTransform(AffineTransform::rotation(angle));

    float scaleFactor = jmin((float)width / knob.getWidth(), (float)height / knob.getHeight());

    g.addTransform(AffineTransform::scale(scaleFactor, scaleFactor));
    g.drawImageTransformed(knob, AffineTransform::translation(-knob.getWidth() * 0.5f, -knob.getHeight() * 0.5f));
    g.restoreState();
    
    g.drawImageWithin(knobBase, x, y, width, height, RectanglePlacement::stretchToFit);
}
