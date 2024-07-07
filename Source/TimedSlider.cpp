#include "TimedSlider.h"

TimedSlider::TimedSlider() {
    startTimerHz(FPS);
}

void TimedSlider::timerCallback() {
}

void TimedSlider::setValueWithTimeCheck(double newValue) {
    int64 currentTime = Time::currentTimeMillis();
    if (std::abs(newValue - lastValidValue) > 0.0001 || currentTime - lastUpdateTimestamp > 2500) {
        lastValidValue = newValue;
        lastUpdateTimestamp = currentTime;
        setValue(newValue);
        drawable = true;
    } else {
        drawable = false;
    }
}

bool TimedSlider::isDrawable() {
    return drawable;
}

