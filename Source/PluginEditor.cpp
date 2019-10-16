/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

AnimatedComponent::AnimatedComponent() {
	currentIndex = 0;
	currentImage = images[currentIndex];
	Timer::startTimer(94);
}

void AnimatedComponent::timerCallback()
{
	DBG("in timer callback");
	rotateImage();
	repaint();
}


void AnimatedComponent::paint(juce::Graphics &g)
	{
		//DBG(currentIndex);
		g.drawImageAt(currentImage,0,0);
	}

void AnimatedComponent::rotateImage() {
	
	if (currentIndex < 7) {
		currentIndex++;
		currentImage = images[currentIndex];
	}
	else if (currentIndex >= 7){//8
		currentIndex = 0;
		currentImage = images[currentIndex];
	}
	DBG(currentIndex);
}

//==============================================================================
InitialDelayAudioProcessorEditor::InitialDelayAudioProcessorEditor (InitialDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setOpaque(true);
    setSize (530, 418);
   
	//Dial Implimentation

	addAndMakeVisible(Comp);
    //filterCutoffDial.addListener(this);
    addAndMakeVisible(filterCutoffDial);
    
	filterCutoffDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterCutoffDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	filterCutoffDial.setSize(90, 90);
	

	filterResDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	filterResDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	filterResDial.setSize(55, 55);
	

	//filterResDial.addListener(this);
    addAndMakeVisible(filterResDial);
    
	filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "cutoff", filterCutoffDial);
    filterResValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "resonance", filterResDial);
    
    //addAndMakeVisible(filterCutoffLabel);
    // filterCutoffLabel.setText("Cutoff Freq", dontSendNotification);
    mixLabel.attachToComponent(&filterCutoffDial, false);
    
    addAndMakeVisible(filterResLabel);
    //filterResLabel.setText("Q", dontSendNotification);
    filterResLabel.attachToComponent(&filterResDial, false);
       
    delayTimeDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    delayTimeDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    delayTimeDial.setNumDecimalPlacesToDisplay(0);
    delayTimeDial.setSize(80, 80);
    delayTimeDial.setTextValueSuffix("ms");
    
	//delayTimeDial.addListener(this);
    addAndMakeVisible(delayTimeDial);
    
    delayMixDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    delayMixDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    delayMixDial.setSize(80, 80);
	//delayMixDial.addListener(this);
    addAndMakeVisible(delayMixDial);
    
    delayFeedbackDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    delayFeedbackDial.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    delayFeedbackDial.setNumDecimalPlacesToDisplay(0);
    delayFeedbackDial.setSize(80, 80);
    delayFeedbackDial.setTextValueSuffix("ms");
    
	//delayFeedbackDial.addListener(this);
	addAndMakeVisible(delayFeedbackDial);

	//Skinning the Dials by connecting them to classes established in the PluginEditor.h 
	filterCutoffDial.setLookAndFeel(&otherLookAndFeel4);
	filterResDial.setLookAndFeel(&otherLookAndFeel3);
    delayMixDial.setLookAndFeel(&otherLookAndFeel);
    delayFeedbackDial.setLookAndFeel(&otherLookAndFeel);
	delayTimeDial.setLookAndFeel(&otherLookAndFeel2);
   
	delayTimeValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "delayTime", delayTimeDial);
    delayMixValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "mix", delayMixDial);
    delayFeedbackValue = new AudioProcessorValueTreeState::SliderAttachment (processor.mState, "feedback", delayFeedbackDial);


}

InitialDelayAudioProcessorEditor::~InitialDelayAudioProcessorEditor()
{
}

//==============================================================================
void InitialDelayAudioProcessorEditor::paint (Graphics& g)
{
	//AnimationOne = ImageCache::getFromMemory(BinaryData::InitialD_png, BinaryData::InitialD_pngSize);
	//g.drawImageAt(AnimationOne, 0, 0);
}

void InitialDelayAudioProcessorEditor::resized()
{
	//Placement of dials on canvis 
	filterCutoffDial.setBounds(45, getHeight() - 114, 80, 80);
	filterResDial.setBounds(135, getHeight() - 112, 80, 80);
    
	delayTimeDial.setBounds(217, getHeight() - 107, 80, 80);
    delayFeedbackDial.setBounds(315, getHeight()- 107, 80, 80);
	delayMixDial.setBounds(410, getHeight() - 107, 80, 80);
	
	Comp.setBounds(getLocalBounds());
}

