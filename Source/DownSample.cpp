#include "DownSample.h"

DownSample::DownSample(double defaultMaxSR, double defaultSR) {
    SR.setTargetValue(defaultSR);
    maxSR = defaultSR;
}

void DownSample::processBlock(juce::AudioBuffer<float>& buffer) {
    
}

void DownSample::setSR(float newValue) {
    SR.setTargetValue(newValue);
}
