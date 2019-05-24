#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics & gfx);
	void DrawCell(const Location& loc, Color c);
	int GetGritWidth() const;
	int GetGritHeight() const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
	Graphics& gfx;
};