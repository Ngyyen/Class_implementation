#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include <iostream>
using namespace std;
class Screen
{
	friend ostream& print(ostream& os, const Screen& scr3);
	friend class Window;
public:
	using pos = std::string::size_type;
	Screen() = default;
	Screen(pos w, pos h, string s) : width(w), height(h), content(s) { }
	Screen(pos w, pos h, char c) : width(w), height(h), content(w* h, c) { }


	Screen& display() { do_display(); return *this; }
	const Screen& display() const { do_display(); return *this; }
	char get() const { return content[cursor]; }

	char get(pos wd, pos ht) const;
	Screen& move(pos wd, pos ht);
	inline Screen& set(char c);
	inline Screen& set(pos wd, pos ht, char c);

private:
	pos cursor = 0;
	pos width = 0, height = 0;
	string content = "";
	void do_display() const { cout << content; }
	void do_clear() { *this = Screen(); }
};
inline char Screen::get(pos wd, pos ht) const
{
	pos row = wd * width;
	return content[row + ht];
}
inline Screen& Screen::move(pos wd, pos ht)
{
	pos row = wd * width;
	cursor = row + ht;
	return *this;
}
Screen& Screen::set(char c)
{
	content[cursor] = c;
	return *this;
}
Screen& Screen::set(pos wd, pos ht, char c)
{
	content[wd * width + ht] = c;
	return *this;
}

ostream& print(ostream& os, const Screen& scr3)
{
	os << scr3.cursor << scr3.width << scr3.height << scr3.content;
	return os;
}
#endif