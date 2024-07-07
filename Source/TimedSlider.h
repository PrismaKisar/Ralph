#pragma once

#include <JuceHeader.h>

#define FPS 4

class TimedSlider : public Slider, Timer {
public:
    TimedSlider();
    ~TimedSlider() {}

    void setValueWithTimeCheck(double newValue);
    bool isDrawable();

private:
    void timerCallback() override;

    double lastValidValue = 0.0;
    int64 lastUpdateTimestamp = 0;
    bool drawable = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimedSlider)
};

