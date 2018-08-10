#pragma once
#include <vector>
#include "Timer.h"

class Animation
{
public:
	Animation();
	Timer animationTimer;
	int currentFrame;
	std::vector<int> frames;

	bool playingAnimation;
	bool playOnce;

	bool init(int speed, bool startPlayingAnimation = true);
	void addFrame(int frame);
	void update();
	void updateIndividualAnimation(bool firstFrame = true);
	void startIndividualAnimation();
	int getFrame();
	int getDefaultFrame();

	~Animation();
};

