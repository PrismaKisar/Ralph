#include "TimedSlider.h"

TimedSlider::TimedSlider() : lastUpdateTimestamp(Time::currentTimeMillis()), creationTimestamp(Time::currentTimeMillis()), drawable(false) {
    startTimerHz(4);
}

TimedSlider::~TimedSlider() {
    stopTimer();
}

void TimedSlider::setValueWithTimeCheck(double newValue) {
    int64 currentTime = Time::currentTimeMillis();
    if (currentTime - creationTimestamp < 1000) {
        lastValidValue = newValue;
        return;
    }
    
    if (std::abs(newValue - lastValidValue) > 0.1) {
        lastValidValue = newValue;
        lastUpdateTimestamp = currentTime;
        drawable = true;
    }
    
    if (currentTime - lastUpdateTimestamp < 1000) {
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
