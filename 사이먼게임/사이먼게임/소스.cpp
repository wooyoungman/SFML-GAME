#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <stdlib.h>
#include<Windows.h>
#include<vector>
using namespace std;
using namespace sf;

// �������� �����Ǵ� ���ڵ��� ���ͳֱ����� ����
vector <int> savenum;

// save_num�̶�� �Լ��� ����� ���� savenum�� ����
void save_num(int a)
{
	savenum.push_back(a);
}

int main()
{
	int length = 0; // �� �ܰ躰 ���Ϳ� �ִ� ���� ���ڵ��� ������ �Ǵ��ϱ� ���� ����
	int level = 1; // �� �ܰ躰 ������ ��Ÿ�������� ����
	int flag = 0; // �� �ܰ躰 ���� ��ư�� �����ϰ� �� �� ������� �� �������� �Ǵ��ϱ� ���� ����
	bool isgamestart = false; // ���� ������ ���� Ŭ���� �Ͽ����� �Ǵ�

	cout << "���α׷��� ���۵Ǿ����ϴ�." << endl;

	//�̹��� ���� ������ ���� �ؽ��� �� ��������Ʈ ����
	Texture color_off, color_on;
	Sprite sprite_off, sprite_on;

	//�̹��� ���� �б�
	color_on.loadFromFile("colors_on.png");
	color_off.loadFromFile("colors_off.png");
	//Sprite ����
	sprite_on.setTexture(color_on);
	sprite_off.setTexture(color_off);
	//�Ҹ� ����
	SoundBuffer S;
	Sound W;
	S.loadFromFile("�����ư.wav");
	W.setBuffer(S); 
	//ȭ�� ũ��, ĸ�� �̸� ����
	cout << "How many buttons you use?" << endl;
	int num = 0; // 4~10�� �� ����� ��ư�� ���� �Է¹��� ���� ����
	cin >> num;
	int xlength = 1000 - 100 * (10 - num); // ��ư�� ������ŭ ���� ���̸� ���� ���� ����
	random_device randp;
	uniform_int_distribution <int>dist(1, num); // 1���� �Է¹��� ��ư�� ���� num������ ���� �� ������ ������ ���� ����
	RenderWindow app(VideoMode(xlength, 100), "Hello Simon"); // ���� xlength ���� 100 �� ũ���� �ڽ� ����
	sprite_on.setTextureRect(IntRect(0, 0, xlength, 100)); // ���� xlength ���� 100 �� ũ���� ��ư���� �ؽ��� ����
	//�ʴ� 60 ������ ����
	app.setFramerateLimit(60);
	//SFML ���� ���� - �����찡 ������ ���� �ݺ�        
	while (app.isOpen())
	{
		// ���� â�� ��ư���� �׷��ְ� �� �� �����ݴϴ�. Sleep �Լ��� ���� 200ms ���� �����̸� �ɾ��ݴϴ�.
		app.draw(sprite_on);
		app.display();
		Sleep(200);
		if (isgamestart == true) // ������ ���۵Ǿ��ٸ� -> �� ���콺 ��ư�� 1ȸ Ŭ���Ͽ��ٸ�
		{
			if (flag == 0)
			{
				int xrandn = dist(randp); // 1~num���� ������ ������ ���� 1���� xrandn�� �Է�
				save_num(xrandn * 100 - 100); // savenum���Ϳ� �Է¹��� ������ ������ ��ư�� x��ǥ ���۰��� �־��ݴϴ�.
				for (auto p : savenum)
				{
					// savenum���Ϳ� ������ ���ڰ� �Էµ� �� ������ �ϴ� ��ư�� ��Ÿ���ָ� ���ÿ� �Ҹ��� ����մϴ�.
					// Sleep �Լ��� ���� ������ �ϴ� ��ư�� ������ �� �ٽ� ������� ���ƿ��� ������ �ڿ������� ������ݴϴ�.
					// �� ��, �ܰ谡 �ö� ���� Sleep �Լ� ���ڰ��� 30�� ���߾� �����̴� �ӵ��� ������ �Ͽ� ���̵��� ���Դϴ�.
					app.draw(sprite_on);
					sprite_off.setPosition(p, 0);
					app.draw(sprite_off);
					app.display();
					W.play();
					Sleep(300 - 30 * level);
					app.draw(sprite_on);
					app.display();
					Sleep(300 - 30 * level);
				}
				// flag == 0 �� ���� �� ������ �����Ͽ����� flag�� 1�� �ٲ��ݴϴ�.
				flag = 1;
			}
		}
		Event event;
		//�̺�Ʈ ó��
		while (app.pollEvent(event)) {
			//���α׷�  �̺�Ʈ ó��
			switch (event.type)
			{
			case Event::Closed:
			{
				app.close();
				cout << "���α׷��� ����Ǿ����ϴ�." << endl;
			}
			// ���콺 ��ư�� ������ ��
			case Event::MouseButtonPressed:
			{
				// ������ ���۵Ǿ��ٸ�
				if (isgamestart == true)
				{
					// ���콺 ��Ŭ�� ��
					if (event.key.code == Mouse::Left)
					{
						// �������� �������� ��ư�� ������ ����� �Ϸᰡ �Ǿ��ٸ�
						if (flag == 1)
						{
							// ���콺 ��Ŭ�� �� ��ǥ���� �ҷ��ɴϴ�.
							Vector2i pos = Mouse::getPosition(app);
							// �ҷ��� x��ǥ���� ���� �������� ��ư�� ���̿� ������ �ȴٸ�
							// �� ���� �ùٸ��� ��ư�� �����ٸ�
							if (pos.x >= savenum.at(length) && pos.x <= savenum.at(length) + 100)
							{
								// �ٽ� �� �� �ùٸ��� ���� ��ư�� ���������� �����̰� ������ݴϴ�.
								// ���� �Ҹ� ��°� Sleep �Լ��� ���� �ڿ������� ������ݴϴ�.
								// �� ������ �ߴٸ� length�� +1 ���ݴϴ�.
								app.draw(sprite_on);
								sprite_off.setPosition(savenum.at(length), 0);
								app.draw(sprite_off);
								app.display();
								W.play();
								Sleep(200);
								app.draw(sprite_on);
								app.display();
								Sleep(200);
								length++;
							}
							else
							{
								// Ʋ�� ��Ʋ�� �������� �����մϴ�.
								app.close();
								cout << "����! ������ �����մϴ�." << endl;
							}
							if (length == level)
							{
								// legnth�� �ùٸ��� ��ư�� ���� �� ���� +1�� ���־�
								// ���� level, �� �ùٸ��� �������� ��ư�� ������ �������ٸ�
								// ���� �ܰ踦 ����ߴٴ� ��¹��� level�� +1 ���ְ� length�� flag�� 0���� �ʱ�ȭ��
								// ���ο� ���� �ܰ踦 ���� �غ� �մϴ�.
								cout << level << "�ܰ� ���!" << endl;
								level++;
								length = 0;
								flag = 0;
							}

						}

					}
				}
				else
				{
					// �� ó�� ���콺 ��ư�� ������ �� isgamestart�� true�� �������־� ������ �����մϴ�.
					isgamestart = true;
					cout << "������ �����մϴ�!" << endl;
				}
			}
			default:break;
			}
			}
	}
	return 0;
}
