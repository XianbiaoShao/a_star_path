#include "a_star.h"

#include <algorithm>

using namespace std;

typedef struct {
	POSITION pos;
	int g_cost;
} SIBLING_INFO;

SIBLING_INFO siblings[] = {
	{ POSITION( 0, -1),  A_STAR_COST_UNIT },
	{ POSITION(-1,  0),  A_STAR_COST_UNIT },
	{ POSITION( 0,  1),  A_STAR_COST_UNIT },
	{ POSITION( 1,  0),  A_STAR_COST_UNIT },
};

POSITION POSITION::operator+(POSITION &rhs)
{
	return POSITION(x + rhs.x, y + rhs.y);
}

bool compare_pos(const POSITION &first, const POSITION &second)
{
	return first.f < second.f;
}

vector<POSITION>::iterator position_in_vector(int x, int y, vector<POSITION> &path)
{
	for (vector<POSITION>::iterator iter = path.begin(); iter != path.end(); ++iter)
		if ((iter->x == x) && (iter->y == y))
			return iter;

	return path.end();
}

int block_distance(const POSITION &first, const POSITION &second)
{
	return (abs(first.x - second.x) + abs(first.y - second.y));
}

int a_star_path_finding(MAP_NODE map[MAP_X_NUM][MAP_Y_NUM], POSITION src, POSITION dst, vector<POSITION> &path)
{
	POSITION cur, pos;
	vector<POSITION> open_list, close_list;

	src.cost = dst.cost = 0;

	src.g = 0;
	src.h = block_distance(src, dst);
	src.update_f();
	open_list.push_back(src);
	
	while (1) {
		if (open_list.empty())
			return 1;

		sort(open_list.begin(), open_list.end(), compare_pos);
		cur = open_list[0];
		open_list.erase(open_list.begin());
		close_list.push_back(cur);

		if (cur.same_pos(dst)) {
			pos = cur;
			path.push_back(pos);
			while (1) {
				vector<POSITION>::iterator iter = position_in_vector(pos.p_x, pos.p_y, close_list);
				if (iter == close_list.end())
					return 1;

				pos = *iter;
				path.push_back(pos);
				if (pos.same_pos(src))
					break;
			}
			
			return 0;
		}

		for (int i = 0; i < NELEMENTS(siblings); i++)
		{
			pos = cur + siblings[i].pos;
			if (!pos.valid())
				continue;

			if (map[pos.x][pos.y].cost >= A_STAR_COST_MAX || (close_list.end() != position_in_vector(pos.x, pos.y, close_list)))
				continue;

			vector<POSITION>::iterator iter = position_in_vector(pos.x, pos.y, open_list);
			if (iter == open_list.end()) {
				pos.set_parent(cur);
				pos.g = cur.g + siblings[i].g_cost;
				pos.h = block_distance(pos, dst);
				pos.cost = map[pos.x][pos.y].cost;
				pos.update_f();
				open_list.push_back(pos);
			} else {
				if ((cur.g + siblings[i].g_cost) < pos.g) {
					pos.set_parent(cur);
					pos.g = cur.g + siblings[i].g_cost;
					pos.update_f();
				}
			}
		}
	}
	
	return 1;
}

