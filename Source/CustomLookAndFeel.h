#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public LookAndFeel_V4 {
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel() {}

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle sliderStyle, Slider& slider) override;
    void setNumTicks(int numTicks) { this->numTicks = numTicks; }

private:
    Image knob;
    Image knobBase;
    Image littleKnob;
    Image holeImage;

    int numTicks = 15;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};
