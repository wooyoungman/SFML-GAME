//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//#include <random>
//#include <stdlib.h>
//#include <Windows.h>
//#include <vector>
//using namespace std;
//using namespace sf;
//
//vector <int> savenum;
//
//void save_num(int a)
//{
//	savenum.push_back(a);
//}
//
//int main()
//{
//	int length = 0;
//	int level = 0;
//	int flag = 0;
//	bool isgamestart = false;
//
//	cout << "프로그램이 시작되었습니다." << endl;
//
//	Texture color_off, color_on;
//	Sprite sprite_off, sprite_on;
//
//	color_on.loadFromFile("colors_on.png");
//	color_off.loadFromFile("colors_off.png");
//
//	sprite_on.setTexture(color_on);
//	sprite_off.setTexture(color_off);
//
//	SoundBuffer S;
//	Sound W;
//	S.loadFromFile("필통버튼.wav");
//	W.setBuffer(S);
//
//	cout << "How many buttons you use?" << endl;
//	int num = 0;
//	cin >> num;
//	int xlength = 1000 - 100 * (10 - num);
//	random_device randp;
//	uniform_int_distribution <int>dist(1, num);
//	RenderWindow app(VideoMode(xlength, 100), "Hello Simon");
//	sprite_on.setTextureRect(IntRect(0, 0, xlength, 100));
//
//	app.setFramerateLimit(60);
//
//	while (app.isOpen())
//	{
//		app.draw(sprite_on);
//		app.display();
//		Sleep(200);
//		if (isgamestart == true)
//		{
//			if (flag == 0)
//			{
//				int xrandn = dist(randp);
//				save_num(xrandn * 100 - 100);
//				for (auto p : savenum)
//				{
//					app.draw(sprite_on);
//					sprite_off.setPosition(p, 0);
//					app.draw(sprite_off);
//					app.display();
//					W.play();
//					Sleep(300 - 30 * level);
//					app.draw(sprite_on);
//					app.display();
//					Sleep(300 - 30 * level);
//				}
//				flag = 1;
//			}
//		}
//
//		Event event;
//		while (app.pollEvent(event))
//		{
//			switch (event.type)
//			{
//			case Event::Closed:
//			{
//				app.close();
//				cout << "프로그램이 종료되었습니다." << endl;
//			}
//			case Event::MouseButtonPressed:
//			{
//				if (isgamestart == true)
//				{
//					if (event.key.code == Mouse::Left)
//					{
//						if (flag == 1)
//						{
//							Vector2i pos = Mouse::getPosition(app);
//							if (pos.x >= savenum.at(length) && pos.x <= savenum.at(length) + 100)
//							{
//								app.draw(sprite_on);
//								sprite_off.setPosition(savenum.at(length), 0);
//								app.draw(sprite_off);
//								app.display();
//								W.play();
//								Sleep(200);
//								app.draw(sprite_on);
//								app.display();
//								Sleep(200);
//								length++;
//							}
//							else
//							{
//								app.close();
//								cout << "실패! 게임을 종료합니다." << endl;
//							}
//							if (length == level)
//							{
//								cout << level << "단계 통과!" << endl;
//								level++;
//								length = 0;
//								flag = 0;
//							}
//						}
//					}
//				}
//				else
//				{
//					isgamestart = true;
//					cout << "게임을 시작합니다!" << endl;
//				}
//			}
//			default:break;
//			}
//		}
//	}
//	return 0;
//}