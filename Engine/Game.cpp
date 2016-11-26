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
#include "mathVect.h"
#include <string>
Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
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
	mathVect<float> test1(std::vector<float> {1, 5, 4}, vertical);
	mathVect<float> test2(std::vector<float> { 8.0f, -4.0f, 17.5f }, horizontal);

	mathVect<float> result = test1 + test2;
	mathVect<float> result2 = test1 - test2;
	float testMult = test1*test2;
	std::wstring title = L"TestTitle";
	wnd.ShowMessageBox(title, std::to_wstring(test1.Length()));
	wnd.ShowMessageBox(title, std::to_wstring(test2.Length()));
	wnd.ShowMessageBox(title, std::to_wstring(testMult));
}

void Game::ComposeFrame()
{
}
