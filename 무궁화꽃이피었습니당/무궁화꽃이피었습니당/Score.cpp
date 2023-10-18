#include "Score.h"

Score::Score()
{
	score = 100;
}
void Score::upScore()
{
	score += 1;
}
void Score::downScore()
{
	score -= 50;
}
int Score::update()
{
	return score;
}