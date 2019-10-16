/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayModule.h"

//==============================================================================
/**
*/
class InitialDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    InitialDelayAudioProcessor();
    ~InitialDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
    float smoothParameterChange(float& currentValue, float& previousValue);

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState& getValueTreeState();
    
    AudioProcessorValueTreeState mState;
    
    void updateFilter();
    
    void updateFeedbackParameter();
    void updateMixParameter();
    void updateDelayTimeParameter();
    

private:
    
    float currentSampleRate;
    int lastSampleRate = 0;
    
    AudioParameterFloat* cutoff;
    AudioParameterFloat* resonance;
    
    float*cuttoffParameter = nullptr;
    float*resParameter = nullptr;
    
    DelayModule delayModule = DelayModule(&writePosition);
    AudioBuffer<float> delayBuffer, dryBuffer;
    
    float* mixParameter = 0;
    float* delayParameter = 0;
    float* feedbackParameter = 0;
    
    LinearSmoothedValue<float> delayTimeSmoothed;
    
    float oldFeedback = 0;
    
    int writePosition = 0;
    
    UndoManager mUndoManager;
    
    Random random;
    
    dsp::ProcessorDuplicator<dsp::IIR::Filter <float>, dsp::IIR::Coefficients<float>> lowPassFilter;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InitialDelayAudioProcessor)
};
