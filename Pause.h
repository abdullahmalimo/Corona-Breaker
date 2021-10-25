#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#define max_main 3
using namespace sf;
using namespace std;
using namespace Style;
class Pause
{
public:
	Pause(float width, float hight);
	void draw(RenderWindow& window);
	void music();
	void change_color(int window_num);
	void return_color(int window_num);
	void return_all_colors();
	int mainMenuPressed() {
		return mainMenuSelected;
	}
	~Pause();

private:
	RectangleShape frame[max_main];
	int mainMenuSelected;
	Font font;
	Text mainMenu[max_main];
	Texture text;
	Music m;
	Texture img1_texture, img2_texture, img3_texture, img4_texture;
	Sprite img1_sprite, img2_sprite, img3_sprite, img4_sprite;
};