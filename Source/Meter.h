#pragma once

#include <JuceHeader.h>

#define FPS 30
#define RELEASE_TIME 0.25f
#define DB_FLOOR -48.0f

class Meter : public Component, public Timer {
public:
    Meter();
	~Meter() {}

    void paint(Graphics& g) override;
    void connectTo(Atomic<float>& targetVariable);
	
private:
	float alpha = 0.0f;
	Atomic<float>* observedEnvelope = nullptr;
    
    void timerCallback() override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Meter)
};
