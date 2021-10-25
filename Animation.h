#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	//functions here
	Animation(sf::Texture* texture, float switchTime);
	~Animation();

	void Update(float deltaTime);

private:

	float totalTime;
	float switchTime;
};