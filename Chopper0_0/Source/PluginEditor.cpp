/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Chopper0_0AudioProcessorEditor::Chopper0_0AudioProcessorEditor (Chopper0_0AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // Draw buttons
    thisWidth = this->getWidth() - 10;
    btnLoadClip1.setBounds(10, 10, thisWidth, 40);
    btnLoadClip2.setBounds(10, 50, thisWidth, 40);
    btnLoadClip3.setBounds(10, 100, thisWidth, 40);
    
    // Draw sliders
    slLevelClip1.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slLevelClip2.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slLevelClip3.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slLevelClip1.setSkewFactor(2.0);
    slLevelClip2.setSkewFactor(2.0);
    slLevelClip3.setSkewFactor(2.0);
    slLevelClip1.setRange(0.0, 1.0);
    slLevelClip2.setRange(0.0, 1.0);
    slLevelClip3.setRange(0.0, 1.0);
    
    // Set initial level to -10 dB (no logarithmic values used yet)
    initialLevel = pow(10.0, -0.5);
    slLevelClip1.setValue(initialLevel);
    slLevelClip2.setValue(initialLevel);
    slLevelClip3.setValue(initialLevel);
    
    
    // Button click event handlers
    btnLoadClip1.onClick = [this] {
        audioProcessor.setClip1Buffer();
    };
    btnLoadClip2.onClick = [this] {
        audioProcessor.setClip2Buffer();
    };
    btnLoadClip3.onClick = [this] {
        audioProcessor.setClip3Buffer();
    };
    
    // Slider value change event handlers
    slLevelClip1.onValueChange = [this] {
        audioProcessor.setClipLevel(slLevelClip1.getValue(), 0);
    };
    slLevelClip2.onValueChange = [this] {
        audioProcessor.setClipLevel(slLevelClip2.getValue(), 1);
    };
    slLevelClip3.onValueChange = [this] {
        audioProcessor.setClipLevel(slLevelClip3.getValue(), 2);
    };
    
    slLevelClip1.setBounds(10, 160, thisWidth, 20);
    slLevelClip2.setBounds(10, 190, thisWidth, 20);
    slLevelClip3.setBounds(10, 220, thisWidth, 20);
    
    addAndMakeVisible(btnLoadClip1);
    addAndMakeVisible(btnLoadClip2);
    addAndMakeVisible(btnLoadClip3);
    addAndMakeVisible(slLevelClip1);
    addAndMakeVisible(slLevelClip2);
    addAndMakeVisible(slLevelClip3);
}

Chopper0_0AudioProcessorEditor::~Chopper0_0AudioProcessorEditor()
{
}

//==============================================================================
void Chopper0_0AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Chopper0_0AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


