#include "Goal.h"

Goal::Goal(const Location& in_loc)
{
	loc = in_loc;
}

void Goal::Respawn(const Location& res_loc)
{
	loc = res_loc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

Location Goal::GetLoc() const
{
	return loc;
}
