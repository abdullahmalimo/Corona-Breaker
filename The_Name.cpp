#include "The_Name.h"
The_Name::The_Name(float width, float hight)
{
	font.loadFromFile("Data/Avara.otf");
	//You are in the top Five
	_text[0].setFont(font);
	_text[0].setString("You are from the top Five");
	_text[0].setCharacterSize(30);
	_text[0].setFillColor(Color(29, 173, 47));
	_text[0].setOutlineThickness(5);
	_text[0].setPosition(width / 2 - 200, hight / 2 - 110);
	//Pleas Enter your name
	_text[1].setFont(font);
	_text[1].setString("Please, Enter your name : ");
	_text[1].setCharacterSize(30);
	_text[1].setFillColor(Color(29, 173, 47));
	_text[1].setOutlineThickness(5);
	_text[1].setPosition(width / 2 - 200, hight / 2 - 60);
	img1_texture.loadFromFile("Icons/image 30.png"); img2_texture.loadFromFile("Icons/image 26.png"); img3_texture.loadFromFile("Icons/image 9.png"); 
	img1_sprite.setTexture(img1_texture); img2_sprite.setTexture(img2_texture); img3_sprite.setTexture(img3_texture); 
	img1_sprite.setPosition(425,530); img2_sprite.setPosition(10, 530); img3_sprite.setPosition(30,400);
}
void The_Name::draw(RenderWindow& window)
{
	RectangleShape rectangle(Vector2f(500, 100));
	rectangle.setFillColor(Color::White);
	rectangle.setPosition(100, 400);
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(Color::Black);
	Texture text;
	text.loadFromFile("Data/Congratulations.png");
	Sprite m;
	m.setScale(0.5f, 0.5f);
	m.setTexture(text);
	m.setPosition(80,70);
	for (int i = 0; i < 2; i++) {
		window.draw(_text[i]);
	}
	window.draw(m);
	window.draw(img1_sprite);
	window.draw(img2_sprite);
	window.draw(img3_sprite);
	window.draw(rectangle);
}
The_Name::~The_Name() {

}