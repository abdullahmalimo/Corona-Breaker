#include "Animation.h"

Animation::Animation(sf::Texture* texture, float switchTime)
{
	this->switchTime = switchTime;
	totalTime = 0.0f;
}

void Animation::Update(float deltaTime)
{
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
	}
}

Animation::~Animation()
{
}