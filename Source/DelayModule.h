/*
  ==============================================================================

    DelayModule.h
    Created: 3 Oct 2019 5:15:17pm
    Author:  Taylor Govers

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class DelayModule
{
public:
    
    DelayModule(int* writePositionHost);
    
    void initialise(int sampleRate, int sourceBufferLength, int delayBufferLength);
    
    void fillDryBuffer(int channel, AudioBuffer<float> &sourceBuffer, AudioBuffer<float> &dryBuffer);
    
    void fillDelayBuffer(int channel, AudioBuffer<float> &sourceBuffer, AudioBuffer<float> &delayBuffer);
    
    void initialDelayEffect(int channel, AudioBuffer<float> &sourceBuffer, AudioBuffer<float> &delayBuffer, float delayTime);
    
    void feedbackDelay(int channel, AudioBuffer<float> &sourceBuffer, AudioBuffer<float> &delayBuffer, float oldFeedback, float feedback);
    
    void reverseDelayBuffer(int channel, AudioBuffer<float> &reverseBuffer, AudioBuffer<float> &delayBuffer);
    
    void mixBuffers(int channel, AudioBuffer<float> &sourceBuffer, AudioBuffer<float> &dryBuffer, float mixParameter);
    
    void smoothParameterChangeFloat(float& currentValue, float& previousValue);
    
    void smoothParameterChangeInt(int& currentValue, int& previousValue);
    
private:
    
    int *writePosition;
    int lastSampleRate;
    
    int sourceBufferSize;
    int delayBufferSize;
    
    int previousDelayTimeSamples = 0;
    float previousMixValue = 0;
};
