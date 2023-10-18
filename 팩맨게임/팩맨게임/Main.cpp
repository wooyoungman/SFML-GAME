#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "DrawText.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostManager.h"
#include "ConvertSketch.h"
#include "DrawMap.h"
#include "MapCollision.h"

int main()
{
	// 게임을 클리어 했는가?
	bool game_won = 0;
	// 게임 레벨
	unsigned char level = 3;
	// 정해진 상수값이 아닌 게임 프레임 속도를 독립적으로 만드는 데 사용.
	unsigned lag = 0;
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	// 팩맨 게임을 위한 맵 스케치 o : 유령모드 콩 , 0123 : 유령 , P : 팩맨
	std::array<std::string, MAP_HEIGHT> map_sketch = {
		" ################### ",
		" #........#........# ",
		" #.##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #..#.....P.....#..# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};

	// 맵 선언
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

	// 처음 유령들의 위치
	std::array<Position, 4> ghost_positions;

	// 각종 이벤트
	sf::Event event;

	// 게임 창 크기 및 설정
	sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	GhostManager ghost_manager;

	Pacman pacman;

	// 랜덤 시드 생성
	srand(static_cast<unsigned>(time(0)));

	// 맵과 고스트의 초기 설정
	map = convert_sketch(map_sketch, ghost_positions, pacman);
	ghost_manager.reset(level, ghost_positions);

	// 현재 시간을 가져와 변수에 저장
	previous_time = std::chrono::steady_clock::now();

	while (1 == window.isOpen())
	{
		// 이 지점에서 lag 즉, 지연을 얼마나 할 것인가 계산합니다.
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += std::chrono::microseconds(delta_time);

		// (lag)지연이 최대 허용 프레임 지속 시간을 초과하는 동안
		while (FRAME_DURATION <= lag)
		{
			// 지연을 감소시킴.
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					// 게임 창 닫을 때
					window.close();
				}
				}
			}

			if (0 == game_won && 0 == pacman.get_dead())
			{
				game_won = 1;

				pacman.update(level, map);

				ghost_manager.update(level, map, pacman);

				// 맵의 모든 셀을 체크해줌.
				for (const std::array<Cell, MAP_HEIGHT>& column : map)
				{
					for (const Cell& cell : column)
					{
						if (Cell::Pellet == cell) // 작은 콩 하나라도 남아있다면
						{
							game_won = 0; // 아직 스테이지 클리어를 하지 못함.

							break;
						}
					}

					if (0 == game_won)
					{
						break;
					}
				}

				if (1 == game_won)
				{
					pacman.set_animation_timer(0);
				}
			}
			else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				game_won = 0;
				
				// 죽었을 시 level 0으로 게임 재시작
				if (1 == pacman.get_dead())
				{
					level = 0;
				}
				// 클리어 시 level + 1 로 다음 게임 시작
				else
				{
					// 각 승리 후에 우리는 공격 웨이브와 에너자이저의 지속 시간을 줄입니다.
					level++;
				}

				map = convert_sketch(map_sketch, ghost_positions, pacman);

				ghost_manager.reset(level, ghost_positions);

				pacman.reset();
			}

			// 최대 허용 프레임 지속 시간이 지연시간보다 클 때
			if (FRAME_DURATION > lag)
			{
				window.clear();

				if (0 == game_won && 0 == pacman.get_dead())
				{
					draw_map(map, window);

					ghost_manager.draw(GHOST_FLASH_START >= pacman.get_Invisible_timer(), window);

					draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Level: " + std::to_string(1 + level), window);
				}

				pacman.draw(game_won, window,map);

				if (1 == pacman.get_animation_over())
				{
					if (1 == game_won)
					{
						draw_text(1, 0, 0, "Next level!", window);
					}
					else
					{
						draw_text(1, 0, 0, "Game over", window);
					}
				}

				window.display();
			}
		}

	}
}