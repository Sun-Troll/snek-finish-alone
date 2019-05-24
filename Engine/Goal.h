#pragma once

#include "Board.h"

class Goal
{
public:
	Goal(const Location& in_loc);
	void Respawn(const Location& res_loc);
	void Draw(Board& brd) const;
	Location GetLoc() const;
private:
	Location loc;
	Color c = Colors::Cyan;
};