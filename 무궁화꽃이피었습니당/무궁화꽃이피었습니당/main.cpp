#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include"HERO.h"
#include"NPC.h"
#include"NPCs.h"
#include<random>
using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1200, 800), "무궁화게임");
	window.setFramerateLimit(60);

	Font font;
	if (!font.loadFromFile("arial.ttf"))
	{

	}

	HERO hero;
	NPCs npcs;

	Text time_remain;
	time_remain.setFont(font);
	time_remain.setFillColor(Color::Black);
	time_remain.setPosition(0.0f,0.0f);
	time_remain.setCharacterSize(30);

	Text text;
	text.setFont(font);
	text.setFillColor(Color::Red);
	text.setPosition(200.0f, 0.0f);
	text.setCharacterSize(30);

	float cur_time = 60.0f;

	Texture scope;
	Sprite pscope;
	scope.loadFromFile("줌.jpg");
	pscope.setTexture(scope);
	pscope.setColor(sf::Color(255, 255, 255, 128));
	pscope.scale(0.8, 1);

	Texture bg;
	Sprite pbg;
	bg.loadFromFile("off1.jpg");
	pbg.setTexture(bg);
	pbg.scale(1, 1);

	Texture bg1;
	Sprite pbg1;
	bg1.loadFromFile("on1.jpg");
	pbg1.setTexture(bg1);
	pbg1.scale(1, 1);

	SoundBuffer s;
	SoundBuffer s1;
	Sound w;
	Sound w1;
	s.loadFromFile("bgm.wav");
	w.setBuffer(s);
	w.setVolume(60);
	s1.loadFromFile("doll.wav");
	w1.setBuffer(s1);

	Clock clock;
	Clock ai_timer;

	float speed = 1;
	int stage = 0;
	int level = 0;
	int c_count = 0;
	float m_count = 0;
	float delay1 = 2;
	float d_count = 0;
	float f_count = 0;
	float b_count = 0;
	int m_flag = 0;
	int f_flag = 0;
	int K_flag = 0;
	int o_flag = 0;
	int s_flag = 0;
	int num = 0;

	while (window.isOpen())
	{
		time_remain.setString("Remain_ Time : ");
		text.setString(to_string(cur_time));
		if (s_flag == 0)
		{
			stage++;
			w1.stop();
			w.play();
			npcs.FirstPosition();
			hero.FirstPosition();
			c_count = 0;
			m_count = 0;
			delay1 = 2;
			d_count = 0;
			f_count = 0;
			b_count = 0;
			m_flag = 0;
			f_flag = 0;
			K_flag = 0;
			o_flag = 0;
			num = 0;
			level = 0;
			cur_time = 60.0f;
			s_flag = 1;
			cout << "현재 단계 : " << stage << endl;
		}

		float time = clock.getElapsedTime().asSeconds();
		float time1 = clock.getElapsedTime().asSeconds();
		clock.restart();

		f_count += time;
		if (f_count >= 2.0f)
		{
			cur_time -= time;
			if (f_flag == 0)
			{
				f_flag = 1;
				m_flag = 1;
				w1.play();
				cout << "시작 ! 무궁화 꽃이 피었습니다~" << endl;
				c_count++;
			}
		}

		if (f_count >= 6 && m_flag == 0)
		{
			m_count += time;
		}

		if (m_count > delay1)
		{
			c_count++;
			if ((c_count) % 3 == 0)
			{
				level += 2;
			}
			speed = 1 + level * 0.1 + stage * 0.2;
			cout << " 무궁화 꽃이 피었습니다~" << endl;
			m_count = 0;
			m_flag = 1;
			w1.setPitch(speed);
			w1.play();
			K_flag = 0;
		}
		
		if (m_flag == 1)
		{
			d_count += time;
		}
		if (d_count >= 4.7 / speed)
		{
			num = rand() % 16;
			d_count = 0;
			m_flag = 0;
			K_flag = 1;
			o_flag = 0;
		}

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Left) == true)
				{
					if (f_flag == 1)
					{
						hero.moveLeft();
						if (m_flag == 0)
						{
							hero.moved = true;
						}
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) == true)
				{
					if (f_flag == 1)
					{
						hero.moveRight();
						if (m_flag == 0)
						{
							hero.moved = true;
						}
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) == true)
				{
					if (f_flag == 1)
					{
						hero.moveUp();
						if (m_flag == 0)
						{
							hero.moved = true;
						}
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) == true)
				{
					if (f_flag == 1)
					{
						hero.moveDown();
						if (m_flag == 0)
						{
							hero.moved = true;
						}
					}
				}
				break;
			default:
				break;
			}
		}
		
		if (m_flag == 0)
		{
			if (K_flag == 1)
			{
				auto& e1 = npcs.npcs.at(num);
				window.draw(pscope);
				pbg.setColor(sf::Color(255, 255, 255, 64));
				window.draw(pbg);
				npcs.moveperson(window,num);
			}
			else
			{
				window.draw(pbg);
			}
		}
		else
		{
			if (npcs.npcs.at(num).move == 1)
			{
				npcs.npcs.at(num).killed = 1;
			}
			npcs.update();
			window.draw(pbg1);
		}
		hero.update();
		hero.draw(window);
		npcs.draw(window);
		window.draw(time_remain);
		window.draw(text);
		if (hero.passed == true)
		{
			hero.passed = false;
			s_flag = 0;
			npcs.npcs.clear();
			npcs.npcs.shrink_to_fit();
		}

		if (cur_time <= 0 || hero.moved == true)
		{
			cout << "게임오버 !" << endl;
			window.close();
		}
		window.display();
	}
	return 0;

}