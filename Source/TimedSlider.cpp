#include "TimedSlider.h"

TimedSlider::TimedSlider() : drawable(false) {
    startTimerHz(4);
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
    } if (currentTime - lastUpdateTimestamp < 1000) {
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
