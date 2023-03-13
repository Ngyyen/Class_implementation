#ifndef WINDOW_H
#define WINDOW_H
#include <vector>
#include "Screen.h"
using namespace std;
class Window
{
public:
	using screen_index = vector<Screen>::size_type;
	inline Window& clear(screen_index i);

	vector<Screen> man_hinh = { Screen(4,4,'x') };
};
Window& Window::clear(screen_index i)
{
	(man_hinh[i]).do_clear();
	return *this;
}
#endif