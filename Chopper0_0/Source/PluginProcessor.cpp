/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Chopper0_0AudioProcessor::Chopper0_0AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Set each buffer to contain a single 0 sample
    audioBuffer1->addSample(0, 0, 0.0);
    audioBuffer1->addSample(1, 0, 0.0);
    audioBuffer2->addSample(0, 0, 0.0);
    audioBuffer2->addSample(1, 0, 0.0);
    audioBuffer3->addSample(0, 0, 0.0);
    audioBuffer3->addSample(1, 0, 0.0);
    
    // Set counters to 0
    counters[0] = 0;
    counters[1] = 0;
    counters[2] = 0;
}

Chopper0_0AudioProcessor::~Chopper0_0AudioProcessor()
{
    delete audioBuffer1;
    delete audioBuffer2;
    delete audioBuffer3;
    delete formatReader;
}

//==============================================================================
const juce::String Chopper0_0AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Chopper0_0AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Chopper0_0AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Chopper0_0AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Chopper0_0AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Chopper0_0AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Chopper0_0AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Chopper0_0AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Chopper0_0AudioProcessor::getProgramName (int index)
{
    return {};
}

void Chopper0_0AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Chopper0_0AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Chopper0_0AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Chopper0_0AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Chopper0_0AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        *channelData += granulise(audioBuffer1, 0, channel);
        *channelData += granulise(audioBuffer2, 0, channel);
        *channelData += granulise(audioBuffer3, 0, channel);
    }
}

//==============================================================================
bool Chopper0_0AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Chopper0_0AudioProcessor::createEditor()
{
    return new Chopper0_0AudioProcessorEditor (*this);
}

//==============================================================================
void Chopper0_0AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Chopper0_0AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Chopper0_0AudioProcessor();
}

void Chopper0_0AudioProcessor::setClipLevel(double input, short index)
{
    clipLevels[index] = input;
}

void Chopper0_0AudioProcessor::setClip1Buffer()
{
    loadBuffer(audioBuffer1);
}

void Chopper0_0AudioProcessor::setClip2Buffer()
{
    loadBuffer(audioBuffer2);
}

void Chopper0_0AudioProcessor::setClip3Buffer()
{
    loadBuffer(audioBuffer3);
}

void Chopper0_0AudioProcessor::loadBuffer(juce::AudioBuffer<float> *bufferToLoad)
{
    // Open file
    juce::FileChooser chooser("Select WAV/AIFF file to load from");
    if (chooser.browseForFileToOpen()) {
        juce::File file = chooser.getResult();
        juce::FileInputStream *fileInputStream = new juce::FileInputStream(file);
        if (fileInputStream->openedOk()) {
            // Load audio
            formatReader = formatManager.createReaderFor(file);
            numSamples = juce::roundToInt(formatReader->lengthInSamples);
            numChannels = formatReader->numChannels;
            bufferToLoad->setSize(numChannels, numSamples);
            formatReader->read(bufferToLoad, 0, numSamples, 0, false, false);
        }
    }
}

double Chopper0_0AudioProcessor::granulise(juce::AudioBuffer<float> *bufferToPlay, short index, int channel)
{
    
}
