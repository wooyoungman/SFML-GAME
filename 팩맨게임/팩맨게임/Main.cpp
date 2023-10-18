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
	// ������ Ŭ���� �ߴ°�?
	bool game_won = 0;
	// ���� ����
	unsigned char level = 3;
	// ������ ������� �ƴ� ���� ������ �ӵ��� ���������� ����� �� ���.
	unsigned lag = 0;
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	// �Ѹ� ������ ���� �� ����ġ o : ���ɸ�� �� , 0123 : ���� , P : �Ѹ�
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

	// �� ����
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

	// ó�� ���ɵ��� ��ġ
	std::array<Position, 4> ghost_positions;

	// ���� �̺�Ʈ
	sf::Event event;

	// ���� â ũ�� �� ����
	sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	GhostManager ghost_manager;

	Pacman pacman;

	// ���� �õ� ����
	srand(static_cast<unsigned>(time(0)));

	// �ʰ� ��Ʈ�� �ʱ� ����
	map = convert_sketch(map_sketch, ghost_positions, pacman);
	ghost_manager.reset(level, ghost_positions);

	// ���� �ð��� ������ ������ ����
	previous_time = std::chrono::steady_clock::now();

	while (1 == window.isOpen())
	{
		// �� �������� lag ��, ������ �󸶳� �� ���ΰ� ����մϴ�.
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += std::chrono::microseconds(delta_time);

		// (lag)������ �ִ� ��� ������ ���� �ð��� �ʰ��ϴ� ����
		while (FRAME_DURATION <= lag)
		{
			// ������ ���ҽ�Ŵ.
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					// ���� â ���� ��
					window.close();
				}
				}
			}

			if (0 == game_won && 0 == pacman.get_dead())
			{
				game_won = 1;

				pacman.update(level, map);

				ghost_manager.update(level, map, pacman);

				// ���� ��� ���� üũ����.
				for (const std::array<Cell, MAP_HEIGHT>& column : map)
				{
					for (const Cell& cell : column)
					{
						if (Cell::Pellet == cell) // ���� �� �ϳ��� �����ִٸ�
						{
							game_won = 0; // ���� �������� Ŭ��� ���� ����.

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
				
				// �׾��� �� level 0���� ���� �����
				if (1 == pacman.get_dead())
				{
					level = 0;
				}
				// Ŭ���� �� level + 1 �� ���� ���� ����
				else
				{
					// �� �¸� �Ŀ� �츮�� ���� ���̺�� ������������ ���� �ð��� ���Դϴ�.
					level++;
				}

				map = convert_sketch(map_sketch, ghost_positions, pacman);

				ghost_manager.reset(level, ghost_positions);

				pacman.reset();
			}

			// �ִ� ��� ������ ���� �ð��� �����ð����� Ŭ ��
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