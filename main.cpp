#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "a_star.h"

using namespace std;



int a_star_test(MAP_NODE g_map[MAP_X_NUM][MAP_Y_NUM], POSITION &src, POSITION &dst)
{
	int err;
	vector<POSITION> path;

	err = a_star_path_finding(g_map, src, dst, path);
	if (err)
	{
		return err;
	}

	cout << endl;
	for (int x = 0; x < MAP_X_NUM; x++)
	{
		for (int y = 0; y < MAP_Y_NUM; y++)
		{
			if ((x == src.x) && (y == src.y))
				cout << "S ";
			else if ((x == dst.x) && (y == dst.y))
				cout << "D ";
			else if (path.end() != position_in_vector(x, y, path))
				if (g_map[x][y].cost > 0)
					cout << "~ ";
				else
					cout << "@ ";
			else if (g_map[x][y].cost == 0)
				cout << ". ";
			else if (g_map[x][y].cost < A_STAR_COST_MAX)
				cout << "/ ";
			else
				cout << "# ";
		}
		cout << endl;
	}

	cout << endl;
	return 0;
}

int a_start_test_map(char *map)
{
	int x = 0;
	char buffer[MAP_Y_NUM + 2];
	MAP_NODE g_map[MAP_X_NUM][MAP_Y_NUM];
	
	FILE* file = fopen(map, "r");
    if (!file)
    {
        cout << "Error opening file";
		return 1;
    }
	
	memset(g_map, 0, sizeof(g_map));

	int src_x, src_y;
	int dst_x, dst_y;
	
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		if (fgets(buffer, MAP_Y_NUM + 2, file)) {
			string row(buffer);
			for (int y = 0; y < MAP_Y_NUM; y++) {
				if (row[y] == '#') {
					g_map[x][y].cost = A_STAR_COST_MAX;
				} else if (row[y] == '/') {
					g_map[x][y].cost = A_STAR_COST_UNIT * 2;
				} else if (row[y] == 'S') {
					src_x = x;
					src_y = y;
				} else if (row[y] == 'D') {
					dst_x = x;
					dst_y = y;
				}
			}
			x++;
		} else {
			break;
		}
	}

	a_star_test(g_map, POSITION(src_x, src_y), POSITION(dst_x, dst_y));

	fclose(file);
	return 0;
}

int main(int argc, char *argv[])
{
	char *maps[] = {
		"map.txt",
		"map1.txt",
		"map2.txt",
		"map3.txt",
	};

	for (int i = 0; i < NELEMENTS(maps); i++)
		a_start_test_map(maps[i]);

	return 0;
}

