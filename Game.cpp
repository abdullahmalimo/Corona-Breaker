#include "Game.h"

Game::Game(float width, float hight) {
	font.loadFromFile("Data/Avara.otf");
	//Play
	mainMenu[0].setFont(font);
	mainMenu[0].setString("Play");
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setCharacterSize(45);
	mainMenu[0].setOutlineThickness(7);
	mainMenu[0].setPosition(Vector2f(width / 2 - 90, hight / 2 - 120));
	//Scoreboard
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Scoreboard");
	mainMenu[1].setCharacterSize(45);
	mainMenu[1].setOutlineThickness(7);
	mainMenu[1].setPosition(Vector2f(width / 2 - 90, hight / 2-30));
	//About Us
	mainMenu[2].setFont(font);
	mainMenu[2].setString("About Us");
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setCharacterSize(45);
	mainMenu[2].setOutlineThickness(7);
	mainMenu[2].setPosition(Vector2f(width / 2 - 90, hight / 2 + 60));
	//Exit
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::White);
	mainMenu[3].setString("Exit");
	mainMenu[3].setCharacterSize(45);
	mainMenu[3].setOutlineThickness(7);
	mainMenu[3].setPosition(Vector2f(width / 2 - 90, hight / 2 + 150));
	mainMenuSelected = -1;
	//icons
	img1_texture.loadFromFile("Icons/image.png"); 
	img2_texture.loadFromFile("Icons/image 10.png");
	img3_texture.loadFromFile("Icons/image 15.png");
	img4_texture.loadFromFile("Icons/image 24.png"); 
	img5_texture.loadFromFile("Icons/image 262.png");
	img1_sprite.setTexture(img1_texture); 
	img2_sprite.setTexture(img2_texture); 
	img3_sprite.setTexture(img3_texture);
	img4_sprite.setTexture(img4_texture);
	img5_sprite.setTexture(img5_texture);
	img1_sprite.setPosition(142, 530);
	img2_sprite.setPosition(130, 255);
	img3_sprite.setPosition(130, 340); 
	img4_sprite.setPosition(350, 500);
	img5_sprite.setPosition(153, 440);
}
Game::~Game() {

}
void Game::change_color(int main_num)
{
	mainMenu[main_num].setFillColor(Color::Blue);
}

void Game::draw(RenderWindow& window) {
	Texture game_name_texture;
	game_name_texture.loadFromFile("Corona breaker name.png");
	Sprite game_name;
	game_name.setTexture(game_name_texture);
	game_name.setPosition(50, 40);
	//game_name.setScale(0.3f, 1);
	for (int i = 0; i < 4; i++) {
		window.draw(mainMenu[i]);
	}
	window.draw(game_name);
	window.draw(img1_sprite);
	window.draw(img2_sprite);
	window.draw(img3_sprite);
	window.draw(img4_sprite);
	window.draw(img5_sprite);
}
void Game::return_color(int window_num)
{
	for (int i = 0; i < max_main; i++)
	{
		if (i != window_num)
		{
			mainMenu[i].setFillColor(Color::White);
		}
	}
}
void Game::return_all_colors()
{
	for (int i = 0; i < max_main; i++)
	{
		mainMenu[i].setFillColor(Color::White);
	}
}
void Game::music() {
	m.openFromFile("Data/World's Most Beautiful & Powerful Music .wav");
	m.setVolume(100);
	m.play();

}
void Game::movedown() {
	if (mainMenuSelected + 1 <= max_main) {
		mainMenu[mainMenuSelected].setFillColor(Color::White);
		mainMenuSelected++;
		if (mainMenuSelected == 4) {
			mainMenuSelected = 0;
		}
		mainMenu[mainMenuSelected].setFillColor(Color::Blue);
		if (mainMenuSelected == 0)
		{
			RectangleShape Frame(Vector2f(150.0f, 90.0f));
			Frame.setPosition(250, 200);
			Frame.setOutlineColor(Color::Black);
			Frame.setOutlineThickness(3);
		}
		else if (mainMenuSelected == 2)
		{
			RectangleShape Frame(Vector2f(130.0f, 90.0f));
			Frame.setPosition(250, 400);
			Frame.setOutlineColor(Color::Black);
			Frame.setOutlineThickness(3);

		}
		else if (mainMenuSelected == 1)
		{
			RectangleShape Frame(Vector2f(310.0f, 90.0f));
			Frame.setPosition(250, 300);
			Frame.setOutlineColor(Color::Black);
			Frame.setOutlineThickness(3);
		}
	}
}
void Game::moveup() {
	if (mainMenuSelected - 1 >= -2) {
		mainMenu[mainMenuSelected].setFillColor(Color::White);
		mainMenuSelected--;
		if (mainMenuSelected <= -1) {
			mainMenuSelected = 2;
		}
		mainMenu[mainMenuSelected].setFillColor(Color::Blue);
		if (mainMenuSelected == 0)
		{
			RectangleShape Frame(Vector2f(150.0f, 90.0f));
			Frame.setPosition(250, 200);
			Frame.setOutlineColor(Color::Black);
			Frame.setOutlineThickness(3);
		}
		else if (mainMenuSelected == 2)
		{
			RectangleShape Frame(Vector2f(130.0f, 90.0f));
			Frame.setPosition(250, 400);
			Frame.setOutlineColor(Color::Black);
			Frame.setOutlineThickness(3);

		}
		else if (mainMenuSelected == 1)
		{
			RectangleShape Frame(Vector2f(310.0f, 90.0f));
			Frame.setPosition(250, 300);
			Frame.setOutlineColor(Color::Black);
			Frame.setOutlineThickness(3);
		}
	}
}