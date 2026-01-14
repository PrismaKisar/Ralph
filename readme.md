# Ralph

Bit-crusher & Downsampler VST plugin developed with JUCE framework.

> University project — LIM, University of Milan

## Features

- **Bit-crushing** with adjustable bit depth
- **Downsampling** with integer sample rate factors
- **LFO modulation** for both effects (waveform, amount, frequency)
- **Dry/Wet** mix per effect
- **Input/Output** gain controls
- Mono and Stereo support

## Usage

| Section | Controls |
|---------|----------|
| Input/Output | Gain knobs (left/right) |
| Bit Crush | Main control + modulation params |
| Downsample | Main control + modulation params |
| Mix | Independent dry/wet per effect |

**Note:** Downsampling uses discrete integer factors only.

## Build

**Requirements:**
- [JUCE Framework](https://juce.com/)
- Xcode (macOS) or Visual Studio 2022 (Windows)

```bash
# Open Ralph.jucer in Projucer, then export and build
```

## Project Structure

```
Source/
├── DSP/
│   ├── Crushing/    # BitCrush, DownSample
│   ├── LFO/         # Oscillator, ModulationControl
│   └── Processor/   # PluginProcessor, Parameters
└── GUI/
    ├── Editor/      # PluginEditor, TimedSlider
    ├── Metering/    # Meter
    └── LookAndFeel/ # CustomLookAndFeel
```

## License

Free for personal and academic use. Not for commercial distribution.

## Contact

Alessandro Sarchi — [alessandro.sarchi02@gmail.com](mailto:alessandro.sarchi02@gmail.com)  
[LIM — University of Milan](https://www.lim.di.unimi.it)
