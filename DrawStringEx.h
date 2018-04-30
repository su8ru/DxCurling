#pragma once
#include <vector>
#include <regex>
#include <DxLib.h>

inline unsigned int convert_dex(const std::string& str) {
	std::string s(str, 1, 6);
	s = "0x" + s;
	return (stoi(s, nullptr, 16));
}

template <typename ... Args>
void DrawFormatStringToHandleEx(int x, int y, unsigned int Color, int FontHandle, const TCHAR *FormatString, Args const & ... args) {
	unsigned int cr = Color;
	std::vector<std::string> vec; //splited string
	static TCHAR str_c[65536]; //<-65536: Maximum number of string

	sprintf_s(str_c, 65536, FormatString, args...);
	std::string str_s = str_c; //string to split
	std::regex re{ R"((\[(([\da-f]{6})|-)\])|\n)" }; // separater
	auto ite = std::sregex_token_iterator(str_s.begin(), str_s.end(), re, { -1,0 });
	auto end = std::sregex_token_iterator();

	while (ite != end) {
		vec.push_back(*ite++);
	}

	int _x = x, _y = y;
	for (const auto &i : vec) {
		if (std::regex_match(i, re) == true) {
			if (i == "[-]") {
				cr = Color;
				continue;
			}
			else if (i == "\n") {
				_x = x;
				_y += GetFontLineSpaceToHandle(FontHandle);
			}
			else {
				cr = convert_dex(i);
				continue;
			}
		}

		DrawFormatStringToHandle(_x, _y, cr, FontHandle, i.c_str());
		_x += GetDrawFormatStringWidthToHandle(FontHandle, i.c_str());
	}
}