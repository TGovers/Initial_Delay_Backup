/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InitialDelayAudioProcessor::InitialDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), mState(*this, &mUndoManager, "Summative", {
         std::make_unique<AudioParameterFloat>("mix", "Mix", 0.0f, 1.0f, 0.5f),
         std::make_unique<AudioParameterFloat>("delayTime", "Delay Time", 0.0f, 2000.0f, 1000.0f),
         std::make_unique<AudioParameterFloat>("feedback", "Feedback", 0, 1.0, 0.5),
         std::make_unique<AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 600.0f),
         std::make_unique<AudioParameterFloat>("resonance", "Resonance", 1.0f, 5.0f, 1.0f)
     }), lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))

#endif
{
    
    mixParameter = mState.getRawParameterValue("mix");
    delayParameter = mState.getRawParameterValue("delayTime");
    feedbackParameter = mState.getRawParameterValue("feedback");
    
}

InitialDelayAudioProcessor::~InitialDelayAudioProcessor()
{
}

//==============================================================================
const String InitialDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool InitialDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool InitialDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool InitialDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double InitialDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int InitialDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int InitialDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void InitialDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String InitialDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void InitialDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void InitialDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    lastSampleRate = sampleRate;
    currentSampleRate = sampleRate;
    
    const int numberInputChannels = getTotalNumInputChannels();
    
    const int delayBufferSize = 2.0f * (sampleRate * samplesPerBlock);
    
    delayBuffer.setSize(numberInputChannels, delayBufferSize);
    dryBuffer.setSize(numberInputChannels, samplesPerBlock);
    
    delayBuffer.clear();
    dryBuffer.clear();
    
    delayModule.initialise(sampleRate, samplesPerBlock, delayBufferSize);
    
    delayTimeSmoothed.reset(sampleRate, 0.0001);
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
    
}

void InitialDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool InitialDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void InitialDelayAudioProcessor::updateFilter()
{
    float freq = *mState.getRawParameterValue("cutoff");
    float res = *mState.getRawParameterValue("resonance");
    
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(currentSampleRate, freq, res);
}

void InitialDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
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
 
    
    if(dryBuffer.getNumSamples() != buffer.getNumSamples())
    {
        
        const int delayBufferSize = 2.0f * (getSampleRate() + buffer.getNumSamples());
        
        delayBuffer.setSize(totalNumInputChannels, delayBufferSize);
        dryBuffer.setSize(totalNumInputChannels, buffer.getNumSamples());
        
        delayBuffer.clear();
        dryBuffer.clear();
        
        delayModule.initialise(getSampleRate(), buffer.getNumSamples(), delayBufferSize);
        
    }
    
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = delayBuffer.getNumSamples();
    
    //float delayTime = *delayParameter;
    float feedback = *feedbackParameter;
    float mix = *mixParameter;
    
    //delayTime = delayTimeSmoothed.getNextValue();
    //delayTimeSmoothed.setTargetValue(delayTime);
    
    //delayTimeSmoothed.setTargetValue(*delayParameter);
    //delayTimeSmoothed.setTargetValue(mState.getParameter("delayTime")->getValue());
    //delayTime = delayTimeSmoothed.getNextValue();
    
    delayTimeSmoothed.setValue(*mState.getRawParameterValue("delayTime"));
    
    const float delayTime = delayTimeSmoothed.getNextValue();
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        
        delayModule.fillDryBuffer(channel, buffer, dryBuffer);
        delayModule.fillDelayBuffer(channel, buffer, delayBuffer);
        
        delayModule.initialDelayEffect(channel, buffer, delayBuffer, delayTime);
        delayModule.mixBuffers(channel, buffer, dryBuffer, /**mixParameter*/ mix);
        delayModule.feedbackDelay(channel, buffer, delayBuffer, oldFeedback, feedback);
        
   //     delayTimeSmoothed.setTargetValue(*delayParameter);
        //delayTimeSmoothed.setTargetValue(mState.getParameter("delayTime")->getValue());
    //    delayTime = delayTimeSmoothed.getNextValue();
        
        oldFeedback = feedback;

       
    }
    
    writePosition += bufferLength;
    writePosition %= delayBufferLength;
    
    
    dsp::AudioBlock<float> block (buffer);
    updateFilter();
    lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));
    
}

float InitialDelayAudioProcessor::smoothParameterChange(float& currentValue, float& previousValue)
{
    
    currentValue = previousValue + ((currentValue - previousValue) * 0.01);
    return currentValue;
    
}

/*
void SeperatedDelayTestAudioProcessor::updateMixParameter()
{
    
   float mix = *mState.getRawParameterValue("mix");
    
}

void SeperatedDelayTestAudioProcessor::updateFeedbackParameter()
{
    
    float feedback = *mState.getRawParameterValue("feedback");
    
}

void SeperatedDelayTestAudioProcessor::updateDelayTimeParameter()
{
    
    float delayTime = *mState.getRawParameterValue("delayTime");
    
}
*/

//==============================================================================
bool InitialDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* InitialDelayAudioProcessor::createEditor()
{
    return new InitialDelayAudioProcessorEditor (*this);
}

//==============================================================================
void InitialDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    MemoryOutputStream stream(destData, false);
    mState.state.writeToStream(stream);
    
}

void InitialDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        mState.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new InitialDelayAudioProcessor();
}
