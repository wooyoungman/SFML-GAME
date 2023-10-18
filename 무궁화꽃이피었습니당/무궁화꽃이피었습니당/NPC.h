#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;

class NPC
{
private:
	int cnt = 0;
	int cnt1 = 0;
	bool dead_on = false;
public:
	Texture t, t1;
	Sprite pp, dead;
	SoundBuffer c;
	Sound d;
	float x;
	float y;
	float speed;
	int x_dir = 1;
	bool killed = false;
	bool passed = false;
	bool move = false;
	NPC(float _x, float _y, float _speed, Texture& _a, Sprite& _b,SoundBuffer& _c,Sound& _d);
	void update();
	void draw(RenderWindow& _window);
};