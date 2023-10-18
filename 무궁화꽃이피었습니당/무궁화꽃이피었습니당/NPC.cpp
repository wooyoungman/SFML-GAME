#include "NPC.h"
#include "NPCs.h"
NPC::NPC(float _x, float _y, float _speed, Texture& _a, Sprite& _b,SoundBuffer& _c,Sound& _d)
{
	x = _x;
	y = _y;
	speed = _speed;
	t = _a;
	pp = _b;
	pp.setPosition(_x, _y);
	c = _c;
	d = _d;
}

void NPC::update()
{
	if (killed == true)
	{
		if (dead_on == false)
		{
			d.play();
			Vector2f pos = pp.getPosition();
			t.loadFromFile("총맞은오일남.jpg");
			pp.setPosition(pos.x, pos.y);
			pp.setTexture(t);
			pp.scale(1, 1);
			dead_on = true;
		}
		return;
	}
	else
	{
		Vector2f pos = pp.getPosition();
		if (pos.y < 130.0f)
		{
			passed = true;
		}
		pp.move(x_dir * speed, -0.2f * speed);
		cnt++;
		cnt1++;
		if (cnt % 20 == 0)
		{
			x_dir = x_dir * -1;
		}
		if (cnt1 % 15 == 0)
		{
			x_dir = x_dir * -1;
		}
	}
}

void NPC::draw(RenderWindow& _window)
{
	if (passed == true)
	{
		return;
	}
	_window.draw(pp);
}