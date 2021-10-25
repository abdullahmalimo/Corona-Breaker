#include "Pause.h"
Pause::Pause(float width, float hight) {
	font.loadFromFile("Data/Avara.otf");
	//Continue
	mainMenu[0].setFont(font);
	mainMenu[0].setString("Continue");
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setCharacterSize(50);
	mainMenu[0].setOutlineThickness(7);
	mainMenu[0].setPosition(Vector2f(width / 2 - 110, hight / 2 - 150));
	//Main Menu
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Main Menu");
	mainMenu[1].setCharacterSize(50);
	mainMenu[1].setOutlineThickness(7);
	mainMenu[1].setPosition(Vector2f(width / 2 - 130, hight / 2));
	//Exit
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(50);
	mainMenu[2].setOutlineThickness(7);
	mainMenu[2].setPosition(Vector2f(width / 2 - 50, hight / 2 + 150));
	mainMenuSelected = -1;
	img1_texture.loadFromFile("Icons/image.png"); 
	img2_texture.loadFromFile("Icons/image 10.png");
	img3_texture.loadFromFile("Icons/image 11.png");
	img4_texture.loadFromFile("Icons/image 32.png");
	img1_sprite.setTexture(img1_texture);
	img2_sprite.setTexture(img2_texture);
	img3_sprite.setTexture(img3_texture);
	img4_sprite.setTexture(img4_texture);
	img1_sprite.setPosition(125, 490);
	img2_sprite.setPosition(75, 190); 
	img3_sprite.setPosition(20, 320); 
	img4_sprite.setPosition(370, 500);
}
Pause::~Pause() {

}
void Pause::change_color(int main_num)
{
	mainMenu[main_num].setFillColor(Color::Blue);
}
void Pause::draw(RenderWindow& window) {
	Texture game_name_texture;
	game_name_texture.loadFromFile("Data/paused.png");
	Sprite game_name;
	game_name.setTexture(game_name_texture);
	game_name.setScale(0.7f, 0.7f);
	game_name.setPosition(40, 10);
	for (int i = 0; i < 3; i++) {
		window.draw(mainMenu[i]);
	}
	window.draw(game_name);
	window.draw(img1_sprite);
	window.draw(img2_sprite);
	window.draw(img3_sprite);
	window.draw(img4_sprite);
}
void Pause::return_color(int window_num)
{
	for (int i = 0; i < max_main; i++)
	{
		if (i != window_num)
		{
			mainMenu[i].setFillColor(Color::White);
		}
	}
}
void Pause::return_all_colors()
{
	for (int i = 0; i < max_main; i++)
	{
		mainMenu[i].setFillColor(Color::White);
	}
}
void Pause::music() {
	m.openFromFile("Data/World's Most Beautiful & Powerful Music .wav");
	m.setVolume(100);
	m.play();

}