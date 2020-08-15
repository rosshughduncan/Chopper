/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Number of samples to play each clip for
#define grainLength 50

//==============================================================================
/**
*/
class Chopper0_0AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Chopper0_0AudioProcessor();
    ~Chopper0_0AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void setClipLevel(double input, short index);
    void setClip1Buffer(), setClip2Buffer(), setClip3Buffer(), loadBuffer(juce::AudioBuffer<float> *bufferToLoad);

private:
    juce::AudioBuffer<float> *audioBuffer1, *audioBuffer2, *audioBuffer3;
    double clipLevels[3], granulise(juce::AudioBuffer<float> *bufferToPlay, short index, int channel);
    juce::AudioFormatReader *formatReader;
    juce::AudioFormatManager formatManager;
    int numSamples, numChannels, counters[3];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chopper0_0AudioProcessor)
};
