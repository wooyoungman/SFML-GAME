#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "NPCs.h"

using namespace sf;

class HERO
{
private:
	int hit_time;
	Texture h;
	Sprite H;
public:
	bool moved;
	bool passed;
	HERO();
	void FirstPosition();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void update();
	void draw(RenderWindow& _window);
};