#include <array>
#include <cmath>

#include "Global.h"
#include "MapCollision.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	bool output = 0;

	float cell_x = i_x / static_cast<float>(CELL_SIZE);
	float cell_y = i_y / static_cast<float>(CELL_SIZE);

	for (unsigned char a = 0; a < 4; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
		case 0:
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(floor(cell_y));
			break;
		}
		case 1:
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(floor(cell_y));
			break;
		}
		case 2:
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(ceil(cell_y));
			break;
		}
		case 3:
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(ceil(cell_y));
		}
		}
		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{
			if (0 == i_collect_pellets)
			{
				if (Cell::Wall == i_map[x][y])
				{
					output = 1;
				}
				else if (0 == i_use_door && Cell::Door == i_map[x][y])
				{
					output = 1;
				}
			}
			else
			{
				if (Cell::Invisible == i_map[x][y])
				{
					output = 1;
					i_map[x][y] = Cell::Empty;
					PlaySound(TEXT("secosmic_lo.wav"), 0, SND_FILENAME | SND_ASYNC);
				}
				else if (Cell::Pellet == i_map[x][y])
				{
					i_map[x][y] = Cell::Empty;
				}
			}
		}
	}
	return output;
}