/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"



//==============================================================================
/**
*/
class AnimatedComponent : public Component, public Timer
{
	public:
		void paint(Graphics& g) override;
		void rotateImage();
		Image A1 = ImageCache::getFromMemory(BinaryData::InitialDAnimation1_png, BinaryData::InitialDAnimation1_pngSize);
		Image A2 = ImageCache::getFromMemory(BinaryData::InitialDAnimation2_png, BinaryData::InitialDAnimation2_pngSize);
		Image A3 = ImageCache::getFromMemory(BinaryData::InitialDAnimation3_png, BinaryData::InitialDAnimation3_pngSize);
		Image A4 = ImageCache::getFromMemory(BinaryData::InitialDAnimation4_png, BinaryData::InitialDAnimation4_pngSize);
		Image A5 = ImageCache::getFromMemory(BinaryData::InitialDAnimation5_png, BinaryData::InitialDAnimation5_pngSize);
		Image A6 = ImageCache::getFromMemory(BinaryData::InitialDAnimation6_png, BinaryData::InitialDAnimation6_pngSize);
		Image A7 = ImageCache::getFromMemory(BinaryData::InitialDAnimation7_png, BinaryData::InitialDAnimation7_pngSize);
		Image A8 = ImageCache::getFromMemory(BinaryData::InitialDAnimation8_png, BinaryData::InitialDAnimation8_pngSize);
		Image images[8] = {A1, A2, A3, A4, A5, A6, A7, A8};
		
		int currentIndex;
		Image currentImage;

		AnimatedComponent();
		//~AnimatedComponent();

		void timerCallback() override;
		
	
};


class OtherLookAndFeel : public LookAndFeel_V4
{
public:
	//This Inserts the image from the binary bank into the class
	Image img1 = ImageCache::getFromMemory(BinaryData::CyberKnob_png, BinaryData::CyberKnob_pngSize);

    void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
	{
		if (img1.isValid())
		{
			const double rotation = (slider.getValue()
				- slider.getMinimum())
				/ (slider.getMaximum()
					- slider.getMinimum());

			const int frames = img1.getHeight() / img1.getWidth();
			const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
			const float radius = jmin(width / 2.0f, height / 2.0f);
			const float centerX = x + width * 0.5f;
			const float centerY = y + height * 0.5f;
			const float rx = centerX - radius - 1.0f;
			const float ry = centerY - radius;

			g.drawImage(img1,
				(int)rx,
				(int)ry,
				2 * (int)radius,
				2 * (int)radius,
				0,
				frameId*img1.getWidth(),
				img1.getWidth(),
				img1.getWidth());
		}
    }
    
};

class OtherLookAndFeel2 : public LookAndFeel_V4
{
public:
	Image img1 = ImageCache::getFromMemory(BinaryData::CyberKnobTime_png, BinaryData::CyberKnobTime_pngSize);

    void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
	{
		if (img1.isValid())
		{
			const double rotation = (slider.getValue()
				- slider.getMinimum())
				/ (slider.getMaximum()
					- slider.getMinimum());

			const int frames = img1.getHeight() / img1.getWidth();
			const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
			const float radius = jmin(width / 2.0f, height / 2.0f);
			const float centerX = x + width * 0.5f;
			const float centerY = y + height * 0.5f;
			const float rx = centerX - radius - 1.0f;
			const float ry = centerY - radius;

			g.drawImage(img1,
				(int)rx,
				(int)ry,
				2 * (int)radius,
				2 * (int)radius,
				0,
				frameId*img1.getWidth(),
				img1.getWidth(),
				img1.getWidth());
		}
    }
    
};

class OtherLookAndFeel3 : public LookAndFeel_V4
{
public:
	Image img1 = ImageCache::getFromMemory(BinaryData::Turbo_png, BinaryData::Turbo_pngSize);

    void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
	{
		if (img1.isValid())
		{
			const double rotation = (slider.getValue()
				- slider.getMinimum())
				/ (slider.getMaximum()
					- slider.getMinimum());

			const int frames = img1.getHeight() / img1.getWidth();
			const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
			const float radius = jmin(width / 2.0f, height / 2.0f);
			const float centerX = x + width * 0.5f;
			const float centerY = y + height * 0.5f;
			const float rx = centerX - radius - 1.0f;
			const float ry = centerY - radius;

			g.drawImage(img1,
				(int)rx,
				(int)ry,
				2 * (int)radius,
				2 * (int)radius,
				0,
				frameId*img1.getWidth(),
				img1.getWidth(),
				img1.getWidth());
		}
    }
    
};

class OtherLookAndFeel4 : public LookAndFeel_V4
{
public:
	Image img1 = ImageCache::getFromMemory(BinaryData::CyberDrive_png, BinaryData::CyberDrive_pngSize);

	void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override
	{
		if (img1.isValid())
		{
			const double rotation = (slider.getValue()
				- slider.getMinimum())
				/ (slider.getMaximum()
					- slider.getMinimum());

			const int frames = img1.getHeight() / img1.getWidth();
			const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
			const float radius = jmin(width / 2.0f, height / 2.0f);
			const float centerX = x + width * 0.5f;
			const float centerY = y + height * 0.5f;
			const float rx = centerX - radius - 1.0f;
			const float ry = centerY - radius;

			g.drawImage(img1,
				(int)rx,
				(int)ry,
				2 * (int)radius,
				2 * (int)radius,
				0,
				frameId*img1.getWidth(),
				img1.getWidth(),
				img1.getWidth());
		}
	}

};
class InitialDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    InitialDelayAudioProcessorEditor (InitialDelayAudioProcessor&);
    ~InitialDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	
private:
	AnimatedComponent Comp;

	
    OtherLookAndFeel otherLookAndFeel;
    OtherLookAndFeel2 otherLookAndFeel2;
    OtherLookAndFeel3 otherLookAndFeel3;
	OtherLookAndFeel4 otherLookAndFeel4;

    Slider filterCutoffDial;
    Slider filterResDial;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterResValue;
    
    Label filterCutoffLabel;
    Label filterResLabel;
    
    Slider delayTimeDial;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayTimeValue;
    Label delayTimeLabel;
    
    Slider mixSlider;
    Label mixLabel;
    
    Slider delayMixDial;
    Slider delayFeedbackDial;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayMixValue;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayFeedbackValue;
    
    Label delayMixLabel;
    Label delayFeedbackLabel;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    InitialDelayAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InitialDelayAudioProcessorEditor)
};
