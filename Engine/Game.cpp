/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snake(loc),
	respawnGoalX(0, 39),
	respawnGoalY(0, 29),
	goal(Location{ respawnGoalX(rng), respawnGoalY(rng) })
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameOver && gameStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RIGHT) && move.x != -1)
		{
			turn = 1;
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT) && move.x != 1)
		{
			turn = 2;
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN) && move.y != -1)
		{
			turn = 3;
		}
		else if (wnd.kbd.KeyIsPressed(VK_UP) && move.y != 1)
		{
			turn = 4;
		}

		if (moveDelay > 0)
		{
			--moveDelay;
		}
		else
		{
			if (turn == 0)
			{ }
			else if (turn == 1)
			{
				move = { 1,0 };
				turn = 0;
			}
			else if (turn == 2)
			{
				move = { -1,0 };
				turn = 0;
			}
			else if (turn == 3)
			{
				move = { 0,1 };
				turn = 0;
			}
			else if (turn == 4)
			{
				move = { 0,-1 };
				turn = 0;
			}
			if (wnd.kbd.KeyIsPressed(VK_SPACE) || snake.GoalEating(goal.GetLoc()))
			{
				bool goalOnBody = true;
				snake.Grow();
				while (goalOnBody)
				{
					goal.Respawn(Location{ respawnGoalX(rng), respawnGoalY(rng) });
					goalOnBody = snake.GoalOnBody(goal.GetLoc());
				}
			}
			snake.MoveBy(move);
			gameOver = (snake.Collision() || snake.ClampScreen(brd));
			moveDelay = moveDelayMax;
		}
	}
	else if (!gameStarted && wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		gameStarted = true;
	}
}

void Game::ComposeFrame()
{
	/*std::uniform_int_distribution<int> colorDist(0, 255);
	for (int y = 0; y < brd.GetGritHeight(); y++)
	{
		for (int x = 0; x < brd.GetGritWidth(); x++)
		{
			Location loc = { x, y };
			Color c(colorDist(rng), colorDist(rng), colorDist(rng));
			brd.DrawCell(loc, c);
		}
	}*/

	if (!gameOver && gameStarted)
	{
		goal.Draw(brd);
		snake.Draw(brd);
	}
	else if (gameOver)
	{
		sc.DrawGameOver(350, 250, gfx);
	}
	else if (!gameStarted)
	{
		sc.DrawTitle(300, 200, gfx);
	}
}
