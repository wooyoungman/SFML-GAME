#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <stdlib.h>
#include<Windows.h>
#include<vector>
using namespace std;
using namespace sf;

// 랜덤으로 생성되는 숫자들을 벡터넣기위해 만듦
vector <int> savenum;

// save_num이라는 함수를 만들어 벡터 savenum에 저장
void save_num(int a)
{
	savenum.push_back(a);
}

int main()
{
	int length = 0; // 각 단계별 벡터에 있는 랜덤 숫자들의 개수를 판단하기 위한 변수
	int level = 1; // 각 단계별 레벨을 나타내기위한 변수
	int flag = 0; // 각 단계별 랜덤 버튼을 생성하고 난 후 순서대로 잘 눌렀는지 판단하기 위한 변수
	bool isgamestart = false; // 게임 시작을 위한 클릭을 하였는지 판단

	cout << "프로그램이 시작되었습니다." << endl;

	//이미지 파일 설정을 위한 텍스쳐 및 스프라이트 선언
	Texture color_off, color_on;
	Sprite sprite_off, sprite_on;

	//이미지 파일 읽기
	color_on.loadFromFile("colors_on.png");
	color_off.loadFromFile("colors_off.png");
	//Sprite 셋팅
	sprite_on.setTexture(color_on);
	sprite_off.setTexture(color_off);
	//소리 설정
	SoundBuffer S;
	Sound W;
	S.loadFromFile("필통버튼.wav");
	W.setBuffer(S); 
	//화면 크기, 캡션 이름 설정
	cout << "How many buttons you use?" << endl;
	int num = 0; // 4~10개 중 사용할 버튼의 수를 입력받을 숫자 선언
	cin >> num;
	int xlength = 1000 - 100 * (10 - num); // 버튼의 개수만큼 가로 길이를 정할 변수 선언
	random_device randp;
	uniform_int_distribution <int>dist(1, num); // 1부터 입력받은 버튼의 수인 num까지의 범위 중 무작위 정수형 숫자 생성
	RenderWindow app(VideoMode(xlength, 100), "Hello Simon"); // 가로 xlength 세로 100 의 크기인 박스 생성
	sprite_on.setTextureRect(IntRect(0, 0, xlength, 100)); // 가로 xlength 세로 100 의 크기인 버튼들의 텍스쳐 생성
	//초당 60 프레임 설정
	app.setFramerateLimit(60);
	//SFML 메인 루프 - 윈도우가 닫힐때 까지 반복        
	while (app.isOpen())
	{
		// 게임 창에 버튼들을 그려주고 난 후 보여줍니다. Sleep 함수를 통해 200ms 동안 딜레이를 걸어줍니다.
		app.draw(sprite_on);
		app.display();
		Sleep(200);
		if (isgamestart == true) // 게임이 시작되었다면 -> 즉 마우스 버튼을 1회 클릭하였다면
		{
			if (flag == 0)
			{
				int xrandn = dist(randp); // 1~num까지 무작위 정수형 숫자 1개를 xrandn에 입력
				save_num(xrandn * 100 - 100); // savenum벡터에 입력받은 무작위 숫자의 버튼의 x좌표 시작값을 넣어줍니다.
				for (auto p : savenum)
				{
					// savenum벡터에 무작위 숫자가 입력된 후 눌러야 하는 버튼을 나타내주며 동시에 소리를 출력합니다.
					// Sleep 함수를 통해 눌러야 하는 버튼을 보여준 후 다시 원래대로 돌아오는 과정을 자연스럽게 만들어줍니다.
					// 이 때, 단계가 올라갈 수록 Sleep 함수 인자값을 30씩 낮추어 깜빡이는 속도를 빠르게 하여 난이도를 높입니다.
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
				// flag == 0 을 통해 위 과정을 수행하였따면 flag를 1로 바꿔줍니다.
				flag = 1;
			}
		}
		Event event;
		//이벤트 처리
		while (app.pollEvent(event)) {
			//프로그램  이벤트 처리
			switch (event.type)
			{
			case Event::Closed:
			{
				app.close();
				cout << "프로그램이 종료되었습니다." << endl;
			}
			// 마우스 버튼이 눌렸을 때
			case Event::MouseButtonPressed:
			{
				// 게임이 시작되었다면
				if (isgamestart == true)
				{
					// 마우스 좌클릭 시
					if (event.key.code == Mouse::Left)
					{
						// 랜덤으로 눌러야할 버튼의 생성과 출력이 완료가 되었다면
						if (flag == 1)
						{
							// 마우스 좌클릭 시 좌표값을 불러옵니다.
							Vector2i pos = Mouse::getPosition(app);
							// 불러온 x좌표값이 내가 눌러야할 버튼의 사이에 포함이 된다면
							// 즉 내가 올바르게 버튼을 눌렀다면
							if (pos.x >= savenum.at(length) && pos.x <= savenum.at(length) + 100)
							{
								// 다시 한 번 올바르게 누른 버튼을 검은색으로 깜빡이게 만들어줍니다.
								// 또한 소리 출력과 Sleep 함수를 통해 자연스럽게 만들어줍니다.
								// 이 과정을 했다면 length를 +1 해줍니다.
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
								// 틀린 버틀을 눌렀으면 종료합니다.
								app.close();
								cout << "실패! 게임을 종료합니다." << endl;
							}
							if (length == level)
							{
								// legnth를 올바르게 버튼을 누를 때 마다 +1씩 해주어
								// 현재 level, 즉 올바르게 눌러야할 버튼의 개수와 같아진다면
								// 현재 단계를 통과했다는 출력문과 level을 +1 해주고 length와 flag를 0으로 초기화해
								// 새로운 다음 단계를 위한 준비를 합니다.
								cout << level << "단계 통과!" << endl;
								level++;
								length = 0;
								flag = 0;
							}

						}

					}
				}
				else
				{
					// 맨 처음 마우스 버튼이 눌렸을 때 isgamestart를 true로 설정해주어 게임을 시작합니다.
					isgamestart = true;
					cout << "게임을 시작합니다!" << endl;
				}
			}
			default:break;
			}
			}
	}
	return 0;
}
