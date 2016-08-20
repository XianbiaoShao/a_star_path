#ifndef INCLUDED_A_STAR
#define INCLUDED_A_STAR

#include <vector>

using namespace std;

#define NELEMENTS(array) sizeof(array) / sizeof(array[0])

#define MAP_X_NUM	15
#define MAP_Y_NUM	15

#define A_STAR_COST_UNIT	10
#define A_STAR_COST_MAX		10000


typedef struct {
	int cost;
} MAP_NODE;

class POSITION {
public:
	int x;
	int y;
	int f, g, h;
	int cost;
	int p_x, p_y;

	POSITION() : x(0), y(0), f(0), g(0), h(0), cost(0) {}
	POSITION(int xx, int yy) : x(xx), y(yy), f(0), g(0), h(0), cost(0) {}
	POSITION(int xx, int yy, int px, int py) : x(xx), y(yy), f(0), g(0), h(0), cost(0), p_x(px), p_y(py) {}
	void update_f() { f = g + h + cost; }
	void set_parent(POSITION &parent) { p_x = parent.x; p_y = parent.y; }
	bool valid() { return ((x >= 0) && (x < MAP_X_NUM) && (y >= 0) && (y < MAP_Y_NUM)); }
	bool same_pos(POSITION &rhs) { return ((x == rhs.x) && (y == rhs.y)); }
	POSITION operator+(POSITION &rhs);
};

vector<POSITION>::iterator position_in_vector(int x, int y, vector<POSITION> &path);
int a_star_path_finding(MAP_NODE map[MAP_X_NUM][MAP_Y_NUM], POSITION src, POSITION dst, vector<POSITION> &path);

#endif
