#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		++nSegments;
		segments[nSegments - 1].InitBody();
	}
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::Collision()
{
	bool collided = false;
	for (int i = 1; i < nSegments; ++i)
	{
		if (segments[0].collision(segments[i]))
		{
			collided = true;
		}
	}
	return collided;
}

bool Snake::ClampScreen(const Board& brd) const
{
	return segments[0].ClampScreen(brd);
}

bool Snake::GoalEating(const Location& goal) const
{
	return segments[0].GoalEating(goal);
}

bool Snake::GoalOnBody(const Location & goal) const
{
	bool check = false;
	for (int i = 0; i < nSegments; ++i)
	{
		check = (segments[i].GoalOnBody(goal) || check);
	}
	return check;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

bool Snake::Segment::collision(const Segment& body)
{
	return (loc.x == body.loc.x && loc.y == body.loc.y);
}

bool Snake::Segment::ClampScreen(const Board& brd) const
{
	return (loc.x < 0 || loc.x >= brd.GetGritWidth() ||
		loc.y < 0 || loc.y >= brd.GetGritHeight());
}

bool Snake::Segment::GoalEating(const Location& goal) const
{
	return (loc.x == goal.x && loc.y == goal.y);
}

bool Snake::Segment::GoalOnBody(const Location & goal) const
{
	return (loc.x == goal.x && loc.y == goal.y);
}
