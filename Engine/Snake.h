#pragma once

#include"Board.h"
#include"Goal.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody();
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		bool collision(const Segment& body);
		bool ClampScreen(const Board& brd) const;
		bool GoalEating(const Location& goal) const;
		bool GoalOnBody(const Location& goal) const;
	private:
		Location loc;
		Color c;
	};

public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	bool Collision();
	bool ClampScreen(const Board& brd) const;
	bool GoalEating(const Location& goal) const;
	bool GoalOnBody(const Location& goal) const;

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 1000;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};
