#pragma once
#include <vector>
#include <random>
#include "NPC.h"

using namespace std;
using namespace sf;

class NPCs
{
private:
	int period;
	Texture t, t1, t2;
	Sprite pp, d;
	SoundBuffer s;
	Sound m;
public:
	vector<NPC>npcs;
	NPCs();
	void clear();
	void FirstPosition();
	void update();
	void moveperson(RenderWindow& _window, int num);
	void draw(RenderWindow& _window);
};