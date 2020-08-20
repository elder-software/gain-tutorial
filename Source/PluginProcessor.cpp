/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTutorial1AudioProcessor::GainTutorial1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    initialiseParameters();
}

void GainTutorial1AudioProcessor::initialiseParameters()
{
    reverbWetLevel = 0.9;
    mReverbParameters.dryLevel = 0.2;
    mReverbParameters.wetLevel = reverbWetLevel;
    mReverbParameters.roomSize = 0.9;
    mReverbParameters.damping = 0.1;
    mReverb.setParameters(mReverbParameters);
}

GainTutorial1AudioProcessor::~GainTutorial1AudioProcessor()
{
}

//==============================================================================
const String GainTutorial1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainTutorial1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainTutorial1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainTutorial1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainTutorial1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainTutorial1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainTutorial1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainTutorial1AudioProcessor::setCurrentProgram (int index)
{
}

const String GainTutorial1AudioProcessor::getProgramName (int index)
{
    return {};
}

void GainTutorial1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GainTutorial1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mReverb.setSampleRate(sampleRate);
    mReverb.setParameters(mReverbParameters);
}

void GainTutorial1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainTutorial1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void GainTutorial1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //rawVolume = 0.015;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    mReverb.setParameters(mReverbParameters);
    
    const auto numChannels = jmin (totalNumInputChannels, totalNumOutputChannels);
    
    if (numChannels == 1) {
        mReverb.processMono(buffer.getWritePointer(0), buffer.getNumSamples());
    } else if (numChannels == 2) {
        mReverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
    }
    

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        float* channelData = buffer.getWritePointer (channel);
//
//        mReverb.processMono(channelData, buffer.getNumSamples());
//
//
//        // ..do something to the data...
//    }
}

//==============================================================================
bool GainTutorial1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainTutorial1AudioProcessor::createEditor()
{
    return new GainTutorial1AudioProcessorEditor (*this);
}

//==============================================================================
void GainTutorial1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GainTutorial1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainTutorial1AudioProcessor();
}
