#include "HERO.h"

HERO::HERO()
{
	h.loadFromFile("¿Ã¡§¿Á.jpg");
	H.setTexture(h);
	H.scale(0.5, 0.5);
	moved = false;
	hit_time = 0;
}

void HERO::FirstPosition()
{
	H.setPosition(570, 700);
}

void HERO::moveLeft()
{
	if (H.getPosition().x <= 0.0f)
	{
		return;
	}
	H.move(-5.0f, 0.0f);
}
void HERO::moveRight()
{
	if (H.getPosition().x >= 1300.0f)
	{
		return;
	}
	H.move(5.0f, 0.0f);
}
void HERO::moveUp()
{
	if (H.getPosition().y >= 1000.0f)
	{
		return;
	}
	H.move(0.0f, -5.0f);
}
void HERO::moveDown()
{
	if (H.getPosition().y <= 0.0f)
	{
		return;
	}
	H.move(0.0f, 5.0f);
}

void HERO::update()
{
	Vector2f pos = H.getPosition();
	if (pos.y < 130.0f)
	{
		passed = true;
	}
}

void HERO::draw(RenderWindow& _window)
{
	if (passed == true)
	{
		return;
	}
	_window.draw(H);
}