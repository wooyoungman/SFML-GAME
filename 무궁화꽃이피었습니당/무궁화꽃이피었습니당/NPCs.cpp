#include "NPC.h"
#include "NPCs.h"
NPCs::NPCs()
{
	t.loadFromFile("±Ö¿ÀÀÏ³².jpg");
	pp.setTexture(t);
	pp.scale(1, 1);
	s.loadFromFile("magnum.wav");
	m.setBuffer(s);
}

void NPCs::moveperson(RenderWindow& _window, int num)
{
	auto& e1 = npcs.at(num);
	if (e1.killed == true)
	{
		return;
	}
	if (period == 10)
	{
		if (num >= 0 && num <= 15)
		{
			e1.pp.move(0, -2.0f);
			e1.move = true;
		}
		period = 0;
	}
	period++;
}

void NPCs::update()
{
	for (auto& _e : npcs)
	{
		_e.update();
	}
}

void NPCs::FirstPosition()
{
	int a = 1;
	for (int i = 0; i <= 19; i++)
	{
		if ((i >= 2 && i <= 9) || (i >= 12 && i <= 19))
		{
			NPC _new(-50 + (i - 2) * 60, 530 - ((rand() % 5) * 15 * a), (rand() % 9) * 0.1 + 1.4, t, pp,s,m);
			npcs.push_back(_new);
		}
		a = a * -1;
	}
}

void NPCs::draw(RenderWindow& _window)
{
	for (auto& _e : npcs)
	{
		_e.draw(_window);
	}
}