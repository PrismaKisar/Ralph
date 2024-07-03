#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public LookAndFeel_V4 {
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() {}

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

    void setNumTicks(int numTicks) { this->numTicks = numTicks; }

private:
    Image knob;
    Image knobBase;
    int numTicks = 10;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
