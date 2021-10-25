#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
using namespace sf;
using namespace std;
using namespace Style;

#define num 2
class The_Name
{
public:
	The_Name(float width, float hight);
	void draw(RenderWindow& window);
	~The_Name();

private:
	RectangleShape rectangle;
	Font font;
	Text _text[num];
	Texture text;
	Texture img1_texture, img2_texture, img3_texture;
	Sprite img1_sprite, img2_sprite, img3_sprite;
};