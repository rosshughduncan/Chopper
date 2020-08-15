/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Chopper0_0AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Chopper0_0AudioProcessorEditor (Chopper0_0AudioProcessor&);
    ~Chopper0_0AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Chopper0_0AudioProcessor& audioProcessor;
    
    // Visual components
    juce::TextButton btnLoadClip1, btnLoadClip2, btnLoadClip3;
    juce::Slider slLevelClip1, slLevelClip2, slLevelClip3;
    int thisWidth;
    double initialLevel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Chopper0_0AudioProcessorEditor)
};

