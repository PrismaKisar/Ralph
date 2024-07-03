#include "Meter.h"

Meter::Meter() {
    alpha = exp(-1.0f / (FPS * RELEASE_TIME));
    startTimerHz(FPS);
}

void Meter::paint(Graphics &g) {
    auto W = getWidth();
    auto H = getHeight();

    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawRect(0, 0, W, H, 1);

    if (observedEnvelope != nullptr) {
        auto envelopeSnapshot = observedEnvelope->get();
        observedEnvelope->set(envelopeSnapshot * alpha);

        auto peak = Decibels::gainToDecibels(envelopeSnapshot);

        auto barHeight = jmap(peak, DB_FLOOR, 0.0f, 0.0f, H - 2.0f);
        barHeight = jlimit(0.0f, H - 2.0f, barHeight);

        auto topColour = peak >= 0.0f ? Colours::red : Colours::yellow;
        ColourGradient filler = ColourGradient(Colours::blueviolet, 0, H, topColour, 0, 0, false);
        filler.addColour(0.8f, Colours::lightblue);
        g.setGradientFill(filler);

        g.fillRect(1.0f, H - 1.0f - barHeight, W - 2.0f, barHeight);
    }
}

void Meter::connectTo(Atomic<float> &targetVariable) {
    observedEnvelope = &targetVariable;
}

void Meter::timerCallback() {
    repaint();
}
