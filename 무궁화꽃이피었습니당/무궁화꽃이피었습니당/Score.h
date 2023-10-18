#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Score
{
private:
	int score;
public:
	Score();
	void upScore();
	void downScore();
	int update();
};
