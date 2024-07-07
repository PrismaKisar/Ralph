#pragma once

#include <JuceHeader.h>

class TimedSlider : public Slider, private Timer {
public:
    TimedSlider();
    ~TimedSlider() override;

    void setValueWithTimeCheck(double newValue);
    bool isDrawable() const;

private:
    void timerCallback() override;

    double lastValidValue = 0.0;
    int64 lastUpdateTimestamp = 0;
    bool drawable = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TimedSlider)
};
