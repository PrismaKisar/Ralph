#include "TimedSlider.h"

TimedSlider::TimedSlider() {
    startTimerHz(2);
}

TimedSlider::~TimedSlider() {
    stopTimer();
}

void TimedSlider::setValueWithTimeCheck(double newValue) {
    int64 currentTime = Time::currentTimeMillis();
    if (std::abs(newValue - lastValidValue) > 0.1) {
        lastValidValue = newValue;
        lastUpdateTimestamp = currentTime;
        drawable = true;
    } else if (currentTime - lastUpdateTimestamp < 1000) {
        drawable = true;
    } else {
        drawable = false;
    }
}

bool TimedSlider::isDrawable() const {
    return drawable;
}

void TimedSlider::timerCallback() {
    repaint();
}
