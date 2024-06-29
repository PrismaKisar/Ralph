#include "Filters.h"


StereoFilter::StereoFilter(double defaultFrequency) : frequency(defaultFrequency) {
    for (int f = 0; f < MAX_NUM_CH; ++f)
        tptFilters.add(new dsp::FirstOrderTPTFilter<float>());
    for(int f = tptFilters.size(); --f >= 0;)
        tptFilters.getUnchecked(f)->setType(juce::dsp::FirstOrderTPTFilterType::lowpass);
}

void StereoFilter::prepareToPlay(double sampleRate) {
    this->sampleRate = sampleRate;
    reset();
}

void StereoFilter::processBlock(AudioBuffer<float>& buffer, const int numSamples) {
    dsp::AudioBlock<float> block(buffer);
    
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        dsp::AudioBlock<float> chBlock = block.getSingleChannelBlock(ch);
        dsp::ProcessContextReplacing<float> context(chBlock);
        tptFilters.getUnchecked(ch)->process(context);
    }
}

void StereoFilter::setFrequency(const double newValue) {
    frequency = jmin(newValue, sampleRate * 0.499);
    for (int f = 0; f < tptFilters.size(); ++f)
            tptFilters.getUnchecked(f)->setCutoffFrequency(frequency);
}

void StereoFilter::reset() {
    for(int f = tptFilters.size(); --f >= 0;)
        tptFilters.getUnchecked(f)->reset();
}
